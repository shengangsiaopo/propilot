// This file is part of MatrixPilot.
//
//    http://code.google.com/p/gentlenav/
//
// Copyright 2009-2011 MatrixPilot Team
// See the AUTHORS.TXT file for a list of authors of MatrixPilot.
//
// MatrixPilot is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// MatrixPilot is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with MatrixPilot.  If not, see <http://www.gnu.org/licenses/>.


#include "libDCM_internal.h"

#define DR_PERIOD (int)((40/GPS_RATE)+4 )

#define DR_TIMESTEP 0.025
#define MAX16 (4.0*RMAX)
#define DR_TAU 2.5

#define ACCEL2DELTAV ((DR_TIMESTEP*GRAVITYM*MAX16)/GRAVITY)
#define VELOCITY2LOCATION (DR_TIMESTEP*.01*MAX16*16.0)
//	The factor of 16 is so that the gain is more precise.
//	There is a subsequent right shift by 4 to cancel the multiply by 16.

#define DR_FILTER_GAIN (int) (DR_TIMESTEP*MAX16/DR_TAU)

extern fractional accelEarth[] ;

int dead_reckon_clock = DR_PERIOD ;

//      velocity, as estimated by the IMU
union longww IMPORTANTz IMUvelocityx ;
union longww IMPORTANTz IMUvelocityy ;
union longww IMPORTANTz IMUvelocityz ;

//      location, as estimated by the IMU
union longww IMPORTANTz IMUlocationx ;
union longww IMPORTANTz IMUlocationy ;
union longww IMPORTANTz IMUlocationz ;

//	GPSlocation - IMUlocation
fractional IMPORTANTz locationErrorEarth[3];
//	GPSvelocity - IMUvelocity
fractional IMPORTANTz velocityErrorEarth[3];

extern int errorYawground[] ;

void dead_reckon(void)
{
	if ( dcm_flags._.dead_reckon_enable == 1 )  // wait for startup of GPS
	{
		//	integrate the accelerometers to update IMU velocity
		IMUvelocityx.WW += __builtin_mulss( ((int)(ACCEL2DELTAV)) ,  accelEarth[0] ) ;
		IMUvelocityy.WW += __builtin_mulss( ((int)(ACCEL2DELTAV)) ,  accelEarth[1] ) ;
		IMUvelocityz.WW += __builtin_mulss( ((int)(ACCEL2DELTAV)) ,  accelEarth[2] ) ;

		//	integrate IMU velocity to update the IMU location	
		IMUlocationx.WW += ( __builtin_mulss( ((int)(VELOCITY2LOCATION)) ,  IMUvelocityx._.W1 )>>4 ) ;
		IMUlocationy.WW += ( __builtin_mulss( ((int)(VELOCITY2LOCATION)) ,  IMUvelocityy._.W1 )>>4 ) ;
		IMUlocationz.WW += ( __builtin_mulss( ((int)(VELOCITY2LOCATION)) ,  IMUvelocityz._.W1 )>>4 ) ;

		if ( dead_reckon_clock > 0 )
		//	apply drift adjustments only while valid GPS data is in force.
		//  This is done with a countdown clock that gets reset each time new data comes in.
		{
			dead_reckon_clock -- ;

			IMUvelocityx.WW += __builtin_mulss( DR_FILTER_GAIN ,  velocityErrorEarth[0] ) ;
			IMUvelocityy.WW += __builtin_mulss( DR_FILTER_GAIN ,  velocityErrorEarth[1] ) ;
			IMUvelocityz.WW += __builtin_mulss( DR_FILTER_GAIN ,  velocityErrorEarth[2] ) ;
	
			IMUlocationx.WW += __builtin_mulss( DR_FILTER_GAIN ,  locationErrorEarth[0] ) ;
			IMUlocationy.WW += __builtin_mulss( DR_FILTER_GAIN ,  locationErrorEarth[1] ) ;
			IMUlocationz.WW += __builtin_mulss( DR_FILTER_GAIN ,  locationErrorEarth[2] ) ;
		}
		else  // GPS has gotten disconnected
		{
			errorYawground[0] = errorYawground[1] = errorYawground[2] = 0 ; // turn off yaw drift
			dcm_flags._.gps_history_valid = 0 ; // restart GPS history variables
		}
	
		if ( gps_nav_valid() && ( dcm_flags._.reckon_req == 1 ) )
		{
			//	compute error indications and restart the dead reckoning clock to apply them
			dcm_flags._.reckon_req = 0 ;
			dead_reckon_clock = DR_PERIOD ;
			locationErrorEarth[0] = GPSlocation.x - IMUlocationx._.W1 ;
			locationErrorEarth[1] = GPSlocation.y - IMUlocationy._.W1 ;
			locationErrorEarth[2] = GPSlocation.z - IMUlocationz._.W1 ;
			velocityErrorEarth[0] = GPSvelocity.x - IMUvelocityx._.W1 ;
			velocityErrorEarth[1] = GPSvelocity.y - IMUvelocityy._.W1 ;
			velocityErrorEarth[2] = GPSvelocity.z - IMUvelocityz._.W1 ;
		}
	}
	else
	{
		IMUvelocityx.WW = 0 ;
		IMUvelocityy.WW = 0 ;
		IMUvelocityz.WW = 0 ;
	
		IMUlocationx.WW = 0 ;
		IMUlocationy.WW = 0 ;
		IMUlocationz.WW = 0 ;
	}
	return ;
}


