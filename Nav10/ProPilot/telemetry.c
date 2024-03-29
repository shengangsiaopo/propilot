// This file is part of MatrixPilot.
//
//    http://code.google.com/p/gentlenav/
//
// Copyright 2009, 2010 MatrixPilot Team
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

#include "options.h"
#include "../libUDB/libUDB_defines.h"
#if (SERIAL_OUTPUT_FORMAT != SERIAL_MAVLINK) // All MAVLink telemetry code is in MAVLink.c

#include "defines.h"

#include "../libDCM/libDCM_internal.h" // Needed for access to internal DCM values

#define _ADDED_C_LIB 1 // Needed to get vsnprintf()
#include <stdio.h>
#include <stdarg.h>

#if ( GPS_TYPE == GPS_DEBUG )
#undef SERIAL_OUTPUT_FORMAT
#define SERIAL_OUTPUT_FORMAT SERIAL_NONE
#endif

union intbb voltage_milis = {0} ;
union intbb voltage_temp ;
extern volatile int trap_flags __attribute__ ((persistent));
extern volatile long trap_source __attribute__ ((persistent));

void sio_newMsg(unsigned char);
void sio_voltage_low( unsigned char inchar ) ;
void sio_voltage_high( unsigned char inchar ) ;

void sio_fp_data( unsigned char inchar ) ;
void sio_fp_checksum( unsigned char inchar ) ;
char fp_high_byte;
unsigned char fp_checksum;

void (* sio_parse ) ( unsigned char inchar ) = &sio_newMsg ;

unsigned char FAR_BUF serial_buffer[SERIAL_BUFFER_SIZE] = {0} ;
int sb_index = 0 ;
int end_index = 0 ;

void init_serial()
{
#if ( SERIAL_OUTPUT_FORMAT == SERIAL_OSD_REMZIBI )
	dcm_flags._.nmea_passthrough = 1;
#endif
	
	udb_serial_set_rate(SERIAL_OUTPUT_BAUD) ;
//	udb_serial_set_rate(38400) ;
//	udb_serial_set_rate(57600) ;
//	udb_serial_set_rate(115200) ;
//	udb_serial_set_rate(230400) ;
//	udb_serial_set_rate(500000) ;
//	udb_serial_set_rate(1000000) ; // yes, it really will work at this rate
	return ;
}


////////////////////////////////////////////////////////////////////////////////
// 
// Receive Serial Commands
//
#if ( GPS_TYPE == GPS_DEBUG )
void udb_serial_callback_received_char(char rxchar)
{
	udb_gps_send_char( rxchar ) ; // send to gps
	return ;
}
#else
void udb_serial_callback_received_char(char rxchar)
{
	(* sio_parse) ( rxchar ) ; // parse the input byte
	return ;
}
#endif

void sio_newMsg( unsigned char inchar )
{
	if ( inchar == 'V' )
	{
		sio_parse = &sio_voltage_high ;
	}
#if ( FLIGHT_PLAN_TYPE == FP_LOGO )
	else if ( inchar == 'L' )
#else
	else if ( inchar == 'W' )
#endif
	{
		fp_high_byte = -1 ; // -1 means we don't have the high byte yet (0-15 means we do)
		fp_checksum = 0 ;
		sio_parse = &sio_fp_data ;
		flightplan_live_begin() ;
	}
	else
	{
		// error ?
	}
	return ;
}


void sio_voltage_high( unsigned char inchar )
{
	voltage_temp.BB = 0 ; // initialize our temp variable
	voltage_temp._.B1 = inchar ;
	sio_parse = &sio_voltage_low ;
	return ;
}


void sio_voltage_low( unsigned char inchar )
{
	voltage_temp._.B0 = inchar ;
	voltage_temp.BB = voltage_temp.BB * 2 ; // convert to voltage
	voltage_milis.BB = voltage_temp.BB ;
	sio_parse = &sio_newMsg ;
	return ;
}


char hex_char_val(unsigned char inchar)
{
	if (inchar >= '0' && inchar <= '9')
	{
		return (inchar - '0') ;
	}
	else if (inchar >= 'A' && inchar <= 'F')
	{
		return (inchar - 'A' + 10) ;
	}
	return -1 ;
}


// For UDB Logo instructions, bytes should be passed in using the following format
// (Below, an X represents a hex digit 0-F.  Mulit-digit values are MSB first.)
// L			begin remote Logo command
// XX	byte:	command
// XX	byte:	subcommand
// X	0-1:	do fly
// X	0-1:	use param
// XXXX	word:	argument
// *			done with command data
// XX	byte:	checksum should equal the sum of the 10 bytes before the *, mod 256
//
// For example: "L0201000005*E8" runs:
// the DO command(02) for subroutine 01 with fly and param off(00) and an argument of 0005


// For classic Waypoints, bytes should be passed in using the following format
// (Below, an X represents a hex digit 0-F.  Mulit-digit values are MSB first.)
// W				begin remote Waypoint command
// XXXXXXXX	long:	waypoint X value
// XXXXXXXX	long:	waypoint Y value
// XXXX		word:	waypoint Z value
// XXXX		word:	flags
// XXXXXXXX	long:	cam view X value
// XXXXXXXX	long:	cam view Y value
// XXXX		word:	cam view Z value
// *				done with command data
// XX		byte:	checksum should equal the sum of the 44 bytes before the *, mod 256
//
// For example: "W0000006400000032000F0200000000000000000000*67" represents:
// the waypoint { {100, 50, 15}, F_INVERTED, {0, 0, 0} }
//

void sio_fp_data( unsigned char inchar )
{
	if (inchar == '*')
	{
		fp_high_byte = -1 ;
		sio_parse = &sio_fp_checksum ;
	}
	else
	{
		char hexVal = hex_char_val(inchar) ;
		if (hexVal == -1)
		{
			sio_parse = &sio_newMsg ;
			return ;
		}
		else if (fp_high_byte == -1)
		{
			fp_high_byte = hexVal * 16 ;
		}
		else
		{
			flightplan_live_received_byte(fp_high_byte + hexVal) ;
			fp_high_byte = -1 ;
		}
		fp_checksum += inchar ;
	}
	return ;
}


void sio_fp_checksum( unsigned char inchar )
{
	char hexVal = hex_char_val(inchar) ;
	if (hexVal == -1)
	{
		sio_parse = &sio_newMsg ;
	}
	else if (fp_high_byte == -1)
	{
		fp_high_byte = hexVal * 16 ;
	}
	else
	{
		unsigned char v = fp_high_byte + hexVal ;
		if (v == fp_checksum)
		{
			flightplan_live_commit() ;
		}
		sio_parse = &sio_newMsg ;
	}
	return ;
}


////////////////////////////////////////////////////////////////////////////////
// 
// Output Serial Data
//

// add this text to the output buffer
void serial_output( char* format, ... )
{
	va_list arglist ;
	
	va_start(arglist, format) ;
	
	int start_index = end_index ;
	int remaining = SERIAL_BUFFER_SIZE - start_index ;
	
	if (remaining > 1)
	{
		int wrote = vsnprintf( (char*)(&serial_buffer[start_index]), (size_t)remaining, format, arglist) ;
		end_index = start_index + wrote;
	}
	
	if (sb_index == 0)
	{
#if (BOARD_TYPE == ASPG_BOARD)
		udb_serial_send_packet( (unsigned char*)(&serial_buffer[0]), end_index );
		sb_index = 0 ;
		end_index = 0 ;
#else
		udb_serial_start_sending();
#endif
	}
	
	va_end(arglist);
	
	return ;
}


int udb_serial_callback_get_char_to_send(void)
{
	char txchar = serial_buffer[ sb_index++ ] ;
	
	if ( txchar )
	{
		return txchar ;
	}
	else
	{
		sb_index = 0 ;
		end_index = 0 ;
	}
	
	return -1;
}


#if ( SERIAL_OUTPUT_FORMAT == SERIAL_DEBUG )

void serial_output_8hz( void )
{
	serial_output("lat: %li, long: %li, alt: %li\r\nrmat: %i, %i, %i, %i, %i, %i, %i, %i, %i\r\n" ,
		lat_gps.WW , long_gps.WW , alt_sl_gps.WW ,
		rmat[0] , rmat[1] , rmat[2] ,
		rmat[3] , rmat[4] , rmat[5] ,
		rmat[6] , rmat[7] , rmat[8]  ) ;
	return ;
}


#elif ( SERIAL_OUTPUT_FORMAT == SERIAL_ARDUSTATION )

int skip = 0 ;

extern int desiredHeight, waypointIndex ;

void serial_output_8hz( void )
{
	unsigned int mode ;
	struct relative2D matrix_accum ;
	union longbbbb accum ;
	int desired_dir_deg ;  // desired_dir converted to a bearing (0-360)
	
	long earth_pitch ;		// pitch in binary angles ( 0-255 is 360 degreres)
	long earth_roll ;		// roll of the plane with respect to earth frame
	//long earth_yaw ;		// yaw with respect to earth frame
	
	accum.WW  = ( desired_dir * BYTECIR_TO_DEGREE ) + 32768 ;
	desired_dir_deg  = accum._.W1 - 90 ; // "Convert UAV DevBoad Earth" to Compass Bearing
	if ( desired_dir_deg < 0 ) desired_dir_deg += 360 ; 

	if (flags._.GPS_steering == 0 && flags._.pitch_feedback == 0)
		mode = 1 ;
	else if (flags._.GPS_steering == 0 && flags._.pitch_feedback == 1)
		mode = 2 ;
	else if (flags._.GPS_steering == 1 && flags._.pitch_feedback == 1 && udb_flags._.radio_on == 1)
		mode = 3 ;
	else if (flags._.GPS_steering == 1 && flags._.pitch_feedback == 1 && udb_flags._.radio_on == 0)
		mode = 0 ;
	else
		mode = 99 ; // Unknown
	
	//  Roll
	//  Earth Frame of Reference
	matrix_accum.x = rmat[8] ;
	matrix_accum.y = rmat[6] ;
	earth_roll = rect_to_polar(&matrix_accum) ;					// binary angle (0 - 256 = 360 degrees)
	earth_roll = (-earth_roll * BYTECIR_TO_DEGREE) >> 16 ;		// switch polarity, convert to -180 - 180 degrees
	
	//  Pitch
	//  Earth Frame of Reference
	//  Note that we are using the matrix_accum.x
	//  left over from previous rect_to_polar in this calculation.
	//  so this Pitch calculation must follow the Roll calculation
	matrix_accum.y = rmat[7] ;
	earth_pitch = rect_to_polar(&matrix_accum) ;				// binary angle (0 - 256 = 360 degrees)
	earth_pitch = (-earth_pitch * BYTECIR_TO_DEGREE) >> 16 ;	// switch polarity, convert to -180 - 180 degrees
	
	// Yaw
	// Earth Frame of Reference
	// Ardustation does not use yaw in degrees
	// matrix_accum.x = rmat[4] ;
	// matrix_accum.y = rmat[1] ;
	// earth_yaw = rect_to_polar(&matrix_accum) ;				// binary angle (0 - 256 = 360 degrees)
	// earth_yaw = (earth_yaw * BYTECIR_TO_DEGREE) >> 16 ;		// switch polarity, convert to -180 - 180 degrees
	
	
	// The Ardupilot GroundStation protocol is mostly documented here:
	//    http://diydrones.com/profiles/blogs/ardupilot-telemetry-protocol
	
	if (++skip == 8)
	{
		serial_output("!!!LAT:%li,LON:%li,SPD:%.2f,CRT:%.2f,ALT:%li,ALH:%i,CRS:%.2f,BER:%i,WPN:%i,DST:%i,BTV:%.2f***\r\n"
					  "+++THH:%i,RLL:%li,PCH:%li,STT:%i,***\r\n",
			lat_gps.WW / 10 , long_gps.WW / 10 , (float)(sog_gps.BB / 100.0), (float)(climb_gps.BB / 100.0),
			(alt_sl_gps.WW - alt_origin.WW) / 100, desiredHeight, (float)(cog_gps.BB / 100.0), desired_dir_deg,
			waypointIndex, tofinish_line, (float)(voltage_milis.BB / 100.0), 
			(int)((udb_pwOut[THROTTLE_OUTPUT_CHANNEL] - udb_pwTrim[THROTTLE_OUTPUT_CHANNEL])/20),
			earth_roll, earth_pitch,
			mode
		) ;
		skip = 0 ;
	}
	else if (skip % 2 == 0)
	{
		serial_output("+++THH:%i,RLL:%li,PCH:%li,STT:%i,***\r\n",
			(int)((udb_pwOut[THROTTLE_OUTPUT_CHANNEL] - udb_pwTrim[THROTTLE_OUTPUT_CHANNEL])/20),
			earth_roll, earth_pitch,
			mode
		) ;
	}
	
	return ;
}


#elif ( SERIAL_OUTPUT_FORMAT == SERIAL_OSD_REMZIBI )

void serial_output_8hz( void )
{
	// TODO: Output interesting information for OSD.
	// But first we'll have to implement a buffer for passthrough characters to avoid
	// output corruption, or generate NMEA ourselves here.
	return ;
}

#elif ( SERIAL_OUTPUT_FORMAT == SERIAL_MAGNETOMETER )

int skip = 0 ;

extern void rxMagnetometer(void) ;
extern int udb_magFieldBody[3] ;
extern unsigned char magreg[6] ;
extern int magFieldEarth[3] ;
extern int udb_magOffset[3] ;
extern int magGain[3] ;
extern int offsetDelta[3] ;
extern int rawMagCalib[3] ;
// extern int magMessage ;

extern union longww HHIntegral ;

#define OFFSETSHIFT 1

//extern int I2ERROR ;
extern int I2messages ;
extern int I2interrupts ;
/*
void serial_output_8hz( void )
{
	serial_output("MagMessage: %i\r\nI2CCON: %X, I2CSTAT: %X, I2ERROR: %X\r\nMessages: %i\r\nInterrupts: %i\r\n\r\n" ,
		CD[magCDindex].R.iResult ,
		I2CCON , I2CSTAT , I2ERROR ,
		I2messages, I2interrupts ) ;
	return ;
}
*/

void serial_output_8hz( void )
{
	if (++skip == 2)
	{
		if ( CD[0].I2CERROR )	{
		serial_output("mSec: %li, CPU: %li Tcy/s\r\n", tow.WW, old_cpu_counter<<2 );	// Tcy / sec
//		serial_output("MagOffset: %i, %i, %i\r\n", udb_magOffset[0]>>OFFSETSHIFT , udb_magOffset[1]>>OFFSETSHIFT , udb_magOffset[2]>>OFFSETSHIFT );
		serial_output("MagBody:  %5i, %5i, %5i\r\n", udb_magFieldBody[0] , udb_magFieldBody[1] , udb_magFieldBody[2] );
		serial_output("MagEarth: %5i, %5i, %5i\r\n", magFieldEarth[0] , magFieldEarth[1] , magFieldEarth[2] );
		serial_output("Calib:    %5i, %5i, %5i\r\n", rawMagCalib[0] , rawMagCalib[1] , rawMagCalib[2] );
		serial_output("MagGain:  %5i, %5i, %5i\r\n", magGain[0] , magGain[1] , magGain[2] );
		serial_output("MagRaw:   %5i, %5i, %5i\r\n", previousMagFieldRaw[0] , previousMagFieldRaw[1] , previousMagFieldRaw[2] ) ;
		serial_output("AccRaw:   %5i, %5i, %5i\r\n", previousAccFieldRaw[0] , previousAccFieldRaw[1] , previousAccFieldRaw[2] ) ;
		serial_output("MagMessage: %i, TotalMsg: %u\r\nI2CCON: 0x%04X, I2CSTAT: 0x%04X, I2ERROR: 0x%04X\r\n\r\n" ,
			CD[magCDindex].iResult , I2Cmessages ,
			CD[0].I2CERROR_CON , CD[0].I2CERROR_STAT , CD[0].I2CERROR ) ;
		} else {
		serial_output("mSec: %li, CPU: %li Tcy/s\r\n", tow.WW, old_cpu_counter<<2 );	// Tcy / sec
//		serial_output("MagOffset: %i, %i, %i\r\n", udb_magOffset[0]>>OFFSETSHIFT , udb_magOffset[1]>>OFFSETSHIFT , udb_magOffset[2]>>OFFSETSHIFT );
		serial_output("MagBody:  %5i, %5i, %5i\r\n", udb_magFieldBody[0] , udb_magFieldBody[1] , udb_magFieldBody[2] );
		serial_output("MagEarth: %5i, %5i, %5i\r\n", magFieldEarth[0] , magFieldEarth[1] , magFieldEarth[2] );
		serial_output("Calib:    %5i, %5i, %5i\r\n", rawMagCalib[0] , rawMagCalib[1] , rawMagCalib[2] );
		serial_output("MagGain:  %5i, %5i, %5i\r\n", magGain[0] , magGain[1] , magGain[2] );
		serial_output("MagRaw:   %5i, %5i, %5i\r\n", previousMagFieldRaw[0] , previousMagFieldRaw[1] , previousMagFieldRaw[2] ) ;
		serial_output("AccRaw:   %5i, %5i, %5i\r\n", previousAccFieldRaw[0] , previousAccFieldRaw[1] , previousAccFieldRaw[2] ) ;
		serial_output("MagMessage: %i, TotalMsg: %u\r\nI2CCON: 0x%04X, I2CSTAT: 0x%04X, I2ERROR: 0x%04X\r\n\r\n" ,
			CD[magCDindex].iResult , I2Cmessages ,
			I2CCON , I2CSTAT , CD[0].I2CERROR ) ;
		}
		skip = 0;
	}

	return ;
}

#elif ( SERIAL_OUTPUT_FORMAT == SERIAL_RAW )
void serial_output_8hz( void )
{
	return ;
}


#elif ( SERIAL_OUTPUT_FORMAT == SERIAL_STATUS )

int skip = 0 ;

extern void rxMagnetometer(void) ;
extern int udb_magFieldBody[3] ;
extern unsigned char magreg[6] ;
extern int magFieldEarth[3] ;
extern int udb_magOffset[3] ;
extern int magGain[3] ;
extern int offsetDelta[3] ;
extern int rawMagCalib[3] ;
// extern int magMessage ;

extern union longww HHIntegral ;

#define OFFSETSHIFT 1

//extern int I2ERROR ;
extern int I2messages ;
extern int I2interrupts ;
void serial_output_8hz( void )
{
//	if (++skip == 2)
//	{
		if ( CD[0].I2CERROR )	{
		serial_output("mSec:%10lu, CPU: %2d.%01d%%/10, %10lu Tcy/s\r\n", tow.WW, cpu_timer/10, cpu_timer%10, old_cpu_counter );	// Tcy / sec
//		serial_output("MagOffset: %i, %i, %i\r\n", udb_magOffset[0]>>OFFSETSHIFT , udb_magOffset[1]>>OFFSETSHIFT , udb_magOffset[2]>>OFFSETSHIFT );
		serial_output("MagBody:  %5i, %5i, %5i\r\n", udb_magFieldBody[0] , udb_magFieldBody[1] , udb_magFieldBody[2] );
//		serial_output("MagEarth: %5i, %5i, %5i\r\n", magFieldEarth[0] , magFieldEarth[1] , magFieldEarth[2] );
//		serial_output("Calib:    %5i, %5i, %5i\r\n", rawMagCalib[0] , rawMagCalib[1] , rawMagCalib[2] );
//		serial_output("MagGain:  %5i, %5i, %5i\r\n", magGain[0] , magGain[1] , magGain[2] );
		serial_output("MagRaw:   %5i, %5i, %5i\r\n", previousMagFieldRaw[0] , previousMagFieldRaw[1] , previousMagFieldRaw[2] ) ;
		serial_output("AccRaw:   %5i, %5i, %5i\r\n", previousAccFieldRaw[0] , previousAccFieldRaw[1] , previousAccFieldRaw[2] ) ;
		serial_output("GyroRaw:  %5i, %5i, %5i\r\n", AD1_Raw[xgyro_in] , AD1_Raw[ygyro_in] , AD1_Raw[zgyro_in] ) ;
		serial_output("GyroFLT:  %5i, %5i, %5i\r\n", FLT_Value[1] , FLT_Value[2] , FLT_Value[3] ) ;
		serial_output("GyroSamples:  %5i, AccelMsgs: %5u, MagMsgs: %5u\r\n", lastGyroSamples, CD[accCDindex].Messages, CD[magCDindex].Messages ) ;
		serial_output("MagMessage: %i, TotalMsg: %u\r\nI2CCON: 0x%04X, I2CSTAT: 0x%04X, I2ERROR: 0x%04X\r\n\r\n" ,
			CD[magCDindex].iResult , I2Cmessages ,
			CD[0].I2CERROR_CON , CD[0].I2CERROR_STAT , CD[0].I2CERROR ) ;
		} else {
		serial_output("mSec:%10lu, CPU: %2d.%01d%%/10, %10lu Tcy/s\r\n", tow.WW, cpu_timer/10, cpu_timer%10, old_cpu_counter );	// Tcy / sec
//		serial_output("MagOffset: %i, %i, %i\r\n", udb_magOffset[0]>>OFFSETSHIFT , udb_magOffset[1]>>OFFSETSHIFT , udb_magOffset[2]>>OFFSETSHIFT );
		serial_output("MagBody:  %5i, %5i, %5i\r\n", udb_magFieldBody[0] , udb_magFieldBody[1] , udb_magFieldBody[2] );
//		serial_output("MagEarth: %5i, %5i, %5i\r\n", magFieldEarth[0] , magFieldEarth[1] , magFieldEarth[2] );
//		serial_output("Calib:    %5i, %5i, %5i\r\n", rawMagCalib[0] , rawMagCalib[1] , rawMagCalib[2] );
//		serial_output("MagGain:  %5i, %5i, %5i\r\n", magGain[0] , magGain[1] , magGain[2] );
		serial_output("MagRaw:   %5i, %5i, %5i\r\n", previousMagFieldRaw[0] , previousMagFieldRaw[1] , previousMagFieldRaw[2] ) ;
		serial_output("AccRaw:   %5i, %5i, %5i\r\n", previousAccFieldRaw[0] , previousAccFieldRaw[1] , previousAccFieldRaw[2] ) ;
		serial_output("GyroRaw:  %5i, %5i, %5i\r\n", AD1_Raw[xgyro_in] , AD1_Raw[ygyro_in] , AD1_Raw[zgyro_in] ) ;
		serial_output("GyroFLT:  %5i, %5i, %5i\r\n", FLT_Value[1] , FLT_Value[2] , FLT_Value[3] ) ;
		serial_output("GyroSamples:  %5i, AccelMsgs: %5u, MagMsgs: %5u\r\n", lastGyroSamples, CD[accCDindex].Messages, CD[magCDindex].Messages ) ;
		serial_output("MagMessage: %i, TotalMsg: %u\r\nI2CCON: 0x%04X, I2CSTAT: 0x%04X, I2ERROR: 0x%04X\r\n\r\n" ,
			CD[magCDindex].iResult , I2Cmessages ,
			I2CCON , I2CSTAT , CD[0].I2CERROR ) ;
		}
//		skip = 0;
//	}

	return ;
}
#elif (( SERIAL_OUTPUT_FORMAT == SERIAL_UDB ) || ( SERIAL_OUTPUT_FORMAT == SERIAL_UDB_EXTRA ))

int telemetry_counter = 6 ;
int skip = 0 ;

#if ( SERIAL_OUTPUT_FORMAT == SERIAL_UDB_EXTRA )
int pwIn_save[NUM_INPUTS + 1 + 8] ;
int pwOut_save[NUM_OUTPUTS + 1] ;
char print_choice = 0 ;
#endif

extern int waypointIndex ;

#if (RECORD_FREE_STACK_SPACE == 1)
extern unsigned int maxstack ;
#endif

void serial_output_8hz( void )
{
#if ( SERIAL_OUTPUT_FORMAT == SERIAL_UDB )
	// Only run through this function twice per second, by skipping all but every 4th run through it.
	// Saves CPU and XBee power.
	if (++skip < 4) return ;
	skip = 0 ;

#elif ( SERIAL_OUTPUT_FORMAT == SERIAL_UDB_EXTRA )
	// SERIAL_UDB_EXTRA expected to be used with the OpenLog which can take greater transfer speeds than Xbee
	// F2: SERIAL_UDB_EXTRA format is printed out every other time, although it is being called at 8Hz, this
	//		version will output four F2 lines every second (4Hz updates)
#endif

	switch (telemetry_counter)
	{
		// The first lines of telemetry contain info about the compile-time settings from the options.h file
		case 6:
			if ( _SWR == 0 )
			{	// if there was not a software reset (trap error) clear the trap data
				trap_flags = trap_source = 0 ;
			}
			serial_output("\r\nF14:WIND_EST=%i:GPS_TYPE=%i:DR=%i:BOARD_TYPE=%i:AIRFRAME=%i:RCON=0x%X:TRAP_FLAGS=0x%X:TRAP_SOURCE=0x%lX:\r\n",
				WIND_ESTIMATION, GPS_TYPE, DEADRECKONING, BOARD_TYPE, AIRFRAME_TYPE, RCON , trap_flags , trap_source ) ;
				RCON = 0 ;
				trap_flags = 0 ;
				trap_source = 0 ;
			break ;
		case 5:
			serial_output("F4:R_STAB_A=%i:R_STAB_RD=%i:P_STAB=%i:Y_STAB_R=%i:Y_STAB_A=%i:AIL_NAV=%i:RUD_NAV=%i:AH_STAB=%i:AH_WP=%i:RACE=%i:\r\n",
				ROLL_STABILIZATION_AILERONS, ROLL_STABILIZATION_RUDDER, PITCH_STABILIZATION, YAW_STABILIZATION_RUDDER, YAW_STABILIZATION_AILERON,
				AILERON_NAVIGATION, RUDDER_NAVIGATION, ALTITUDEHOLD_STABILIZED, ALTITUDEHOLD_WAYPOINT, RACING_MODE) ;
			break ;
		case 4:
			serial_output("F5:YAWKP_A=%5.3f:YAWKD_A=%5.3f:ROLLKP=%5.3f:ROLLKD=%5.3f:A_BOOST=%3.1f:\r\n",
				YAWKP_AILERON, YAWKD_AILERON, ROLLKP, ROLLKD, AILERON_BOOST ) ;
			break ;
		case 3:
			serial_output("F6:P_GAIN=%5.3f:P_KD=%5.3f:RUD_E_MIX=%5.3f:ROL_E_MIX=%5.3f:E_BOOST=%3.1f:\r\n",
				PITCHGAIN, PITCHKD, RUDDER_ELEV_MIX, ROLL_ELEV_MIX, ELEVATOR_BOOST) ;
			break ;
		case 2:
			serial_output("F7:Y_KP_R=%5.4f:Y_KD_R=%5.3f:RLKP_RUD=%5.3f:RUD_BOOST=%5.3f:RTL_PITCH_DN=%5.3f:\r\n",
				YAWKP_RUDDER, YAWKD_RUDDER, ROLLKP_RUDDER , RUDDER_BOOST, RTL_PITCH_DOWN) ;
			break ;
		case 1:
			serial_output("F8:H_MAX=%6.1f:H_MIN=%6.1f:MIN_THR=%3.2f:MAX_THR=%3.2f:PITCH_MIN_THR=%4.1f:PITCH_MAX_THR=%4.1f:PITCH_ZERO_THR=%4.1f:\r\n",
				HEIGHT_TARGET_MAX, HEIGHT_TARGET_MIN, ALT_HOLD_THROTTLE_MIN, ALT_HOLD_THROTTLE_MAX,
				ALT_HOLD_PITCH_MIN, ALT_HOLD_PITCH_MAX, ALT_HOLD_PITCH_HIGH) ;
			break ;
		default:
			// F2 below means "Format Revision 2: and is used by a Telemetry parser to invoke the right pattern matching
			// F2 is a compromise between easy reading of raw data in a file and not droppping chars in transmission.

#if ( SERIAL_OUTPUT_FORMAT == SERIAL_UDB )
			serial_output("F2:T%li:S%d%d%d:N%li:E%li:A%li:W%i:a%i:b%i:c%i:d%i:e%i:f%i:g%i:h%i:i%i:c%u:s%i:cpu%u:bmv%i:"
				"as%i:wvx%i:wvy%i:wvz%i:\r\n",
				tow.WW, udb_flags._.radio_on, dcm_flags._.nav_capable, flags._.GPS_steering,
				lat_gps.WW , long_gps.WW , alt_sl_gps.WW, waypointIndex,
				rmat[0] , rmat[1] , rmat[2] ,
				rmat[3] , rmat[4] , rmat[5] ,
				rmat[6] , rmat[7] , rmat[8] ,
				(unsigned int)cog_gps.BB, sog_gps.BB, (unsigned int)udb_cpu_load(), voltage_milis.BB,
				air_speed_magnitude, estimatedWind[0], estimatedWind[1],estimatedWind[2]) ;

#elif ( SERIAL_OUTPUT_FORMAT == SERIAL_UDB_EXTRA )
			if (print_choice == 0 )
			{
				serial_output("F2:T%li:S%d%d%d:N%li:E%li:A%li:W%i:a%i:b%i:c%i:d%i:e%i:f%i:g%i:h%i:i%i:c%u:s%i:cpu%u:bmv%i:"
					"as%i:wvx%i:wvy%i:wvz%i:ma%i:mb%i:mc%i:svs%i:hd%i:",
					tow.WW, udb_flags._.radio_on, dcm_flags._.nav_capable, flags._.GPS_steering,
					lat_gps.WW , long_gps.WW , alt_sl_gps.WW, waypointIndex,
					rmat[0] , rmat[1] , rmat[2] ,
					rmat[3] , rmat[4] , rmat[5] ,
					rmat[6] , rmat[7] , rmat[8] ,
					(unsigned int)cog_gps.BB, sog_gps.BB, (unsigned int)udb_cpu_load(), voltage_milis.BB,
					air_speed_magnitude, estimatedWind[0], estimatedWind[1],estimatedWind[2],

#if (MAG_YAW_DRIFT == 1)
					magFieldEarth[0],magFieldEarth[1],magFieldEarth[2],
#else
					(int)0, (int)0, (int)0,
#endif

					svs, hdop ) ;

				// Save  pwIn and PwOut buffers for printing next time around
				int i ;
				for (i=0; i <= NUM_INPUTS; i++)
					pwIn_save[i] = udb_pwIn[i+(RC_START-1)] ;
				for (i=0; i <= NUM_OUTPUTS; i++)
					pwOut_save[i] = udb_pwOut[i] ;
				print_choice = 1 ;
			}
			else
			{
				int i ;
				for (i= 1; i <= NUM_INPUTS; i++)
					serial_output("p%ii%i:",i,(int)(pwIn_save[i]/16)+3000);
				for (i= 1; i <= NUM_OUTPUTS; i++)
					serial_output("p%io%i:",i,(int)(pwOut_save[i]/2.5));
				serial_output("imx%i:imy%i:imz%i:fgs%X:",IMUlocationx._.W1 ,IMUlocationy._.W1 ,IMUlocationz._.W1, flags.WW );
#if (RECORD_FREE_STACK_SPACE == 1)
				serial_output("stk%d:", (int)(4096-maxstack));
#endif
				serial_output("\r\n");
				print_choice = 0 ;
			}
#endif
			if (flags._.f13_print_req == 1)
			{
				// The F13 line of telemetry is printed when origin has been captured and inbetween F2 lines in SERIAL_UDB_EXTRA
#if ( SERIAL_OUTPUT_FORMAT == SERIAL_UDB_EXTRA )
				if (print_choice != 0) return ;
#endif
				serial_output("F13:week%i:origN%li:origE%li:origA%li:\r\n", week_no, lat_origin.WW, long_origin.WW, alt_origin) ;
				flags._.f13_print_req = 0 ;
			}

			return ;
	}
				// Approximate time passing between each telemetry line, even though
				// we may not have new GPS time data each time through.
			/*	if (tow.WW > 0) */ tow.WW += 250 ;

	telemetry_counter-- ;
	return ;
}



#else // If SERIAL_OUTPUT_FORMAT is set to SERIAL_NONE, or is not set

void serial_output_8hz( void )
{
	return ;
}

#endif
#endif
