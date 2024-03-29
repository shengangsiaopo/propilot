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


#ifndef UDB_DEFINES_H
#define UDB_DEFINES_H

// Types
struct bb { unsigned char B0 ; unsigned char B1 ; } ;
struct bbbb { unsigned char B0 ; unsigned char B1 ; unsigned char B2 ; unsigned char B3 ; } ;
struct ww { int W0 ; int W1 ; } ;
struct uu { unsigned int U0 ; unsigned int U1 ;  };
struct uuuu { unsigned int U0 ; unsigned int U1 ; unsigned int U2 ; unsigned int U3 ; };

union intbb { int BB ; struct bb _ ; } ;
union longbbbb { long WW ; struct ww _ ; struct bbbb __ ; } ;
union longww { long  WW ; struct ww _ ; struct uu __ ;} ;
union longlongww { long long  WW ; struct ww _ ; struct uuuu __ ;} ;

typedef unsigned char BYTE, *LPBYTE;
typedef unsigned int WORD, *LPWORD;
typedef unsigned long DWORD, *LPDWORD;

// Build for the specific board type
#define RED_BOARD		1
#define GREEN_BOARD		2
#define UDB3_BOARD		3	// Test board for Inversense Gyros
#define RUSTYS_BOARD	4	// Red board with Rusty's IXZ-500_RAD2a patch board
#define UDB4_BOARD		5
#define CAN_INTERFACE	6
#define ASPG_BOARD		7

// Clock configurations
#define CRYSTAL_CLOCK	1
#define FRC8X_CLOCK		2


// Include the necessary files for the current board type
#if (BOARD_TYPE == RED_BOARD)
#include "p30f4011.h"
#include "ConfigRed.h"

#elif (BOARD_TYPE == GREEN_BOARD)
#include "p30f4011.h"
#include "ConfigGreen.h"

#elif (BOARD_TYPE == UDB3_BOARD)
#include "p30f4011.h"
#include "ConfigIXZ500.h"

#elif (BOARD_TYPE == RUSTYS_BOARD)
#include "p30f4011.h"
#include "ConfigIXZ500RAD2a.h"

#elif (BOARD_TYPE == UDB4_BOARD)
#include "p33fj256gp710a.h"
#include "ConfigUDB4.h"

#elif (BOARD_TYPE == CAN_INTERFACE)
#include "p30f6010A.h"
#include "../CANInterface/ConfigCANInterface.h"

#elif (BOARD_TYPE == ASPG_BOARD)
#if defined(ECLIPSE_BUILD)
#include "p33fj256gp710.h"
#else
#include "p33fj256gp710A.h"
#endif
#include "ConfigASPG.h"

#else
#error "Board type must be defined!"
#endif

#if !defined(FAR_BUF)
#define FAR_BUF __attribute__ ((far))
#define NEAR_BUF __attribute__ ((near))
#define IMPORTANT __attribute__ ((near))
#define IMPORTANTz __attribute__ ((near))
#define PARAMETER __attribute__ ((near))
#endif

#if (HILSIM == 1)
#include "ConfigHILSIM.h"
#endif


#if ((USE_PPM_INPUT == 1) && !(BOARD_TYPE == ASPG_BOARD))
#undef MAX_INPUTS
#define MAX_INPUTS 8
#undef MAX_OUTPUTS
#define MAX_OUTPUTS 9
#endif


// define the board rotations here.
// This include must go just after the board type has been declared
// Do not move this
// Orientation of the board
#define ORIENTATION_FORWARDS		0
#define ORIENTATION_BACKWARDS		1
#define ORIENTATION_INVERTED		2
#define ORIENTATION_FLIPPED			3
#define ORIENTATION_ROLLCW			4
#define ORIENTATION_ROLLCW180		5

#include "boardRotation_defines.h"


#if (BOARD_TYPE == GREEN_BOARD || BOARD_TYPE == RED_BOARD || BOARD_TYPE == UDB3_BOARD || BOARD_TYPE == RUSTYS_BOARD)

#define BOARD_IS_CLASSIC_UDB		1
#define CLK_PHASES	4

#if ( CLOCK_CONFIG == FRC8X_CLOCK )
#define FREQOSC		58982400
#else
#define FREQOSC		16000000
#endif
#elif (BOARD_TYPE == ASPG_BOARD)
	#define FREQOSC 	80000000
	#define CLK_PHASES	2
#else
	#define BOARD_IS_CLASSIC_UDB		0
	#define FREQOSC 	32000000
	#define CLK_PHASES	2
#endif


// Types
typedef char boolean;
#define true	1
#define false	0

struct ADchannel {
	int input; // raw input
	int value; // filtered a little bit as part of A/D
	int offset;  // baseline at power up 
};  // variables for processing an AD channel


struct udb_flag_bits {	// this is not actually a byte - c bitfields are mod 16 bits allocated from low bit
			unsigned int a2d_read				: 1 ;
			unsigned int mavlink_send_specific_variable : 1 ;
			unsigned int mavlink_send_variables 		: 1 ;
			unsigned int mavlink_send_waypoints 		: 1 ;
			unsigned int firstsamp				: 1 ;
			unsigned int radio_on				: 1 ;
			unsigned int unused					: 2 ;
			} ;


// Baud Rate Generator -- See section 19.3.1 of datasheet.
// Fcy = FREQOSC / CLK_PHASES
// UXBRG = (Fcy/(16*BaudRate))-1
// UXBRG = ((32000000/2)/(16*9600))-1
// UXBRG = 103
#define UDB_BAUD(x)		((int)((FREQOSC / CLK_PHASES) / ((long)4 * x) - 1))


// LED states
#define LED_ON		0
#define LED_OFF		1


// Channel numbers on the board, mapped to positions in the pulse width arrays.
#define CHANNEL_UNUSED	0	// udb_pwIn[0], udb_pwOut[0], etc. are not used, but allow lazy code everywhere else  :)
#define CHANNEL_1		1
#define CHANNEL_2		2
#define CHANNEL_3		3
#define CHANNEL_4		4
#define CHANNEL_5		5
#define CHANNEL_6		6
#define CHANNEL_7		7
#define CHANNEL_8		8
#define CHANNEL_9		9

// Serial Output Format
#define SERIAL_NONE			0	// No serial data is sent
#define SERIAL_DEBUG		1	// UAV Dev Board debug info
#define SERIAL_ARDUSTATION	2	// Compatible with ArduStation
#define SERIAL_UDB			3	// Pete's efficient UAV Dev Board format
#define SERIAL_OSD_REMZIBI	4	// Output data formatted to use as input to a Remzibi OSD (only works with GPS_UBX)
#define SERIAL_OSD_IF		5	// Output data formatted to use as input to a IF OSD (only works with GPS_UBX)
#define SERIAL_MAGNETOMETER	6	// Debugging the magnetometer
#define SERIAL_UDB_EXTRA	7	// Extra Telemetry beyond that provided by SERIAL_UDB for higher bandwidth connections
#define SERIAL_STATUS		8	// some low level a/d + process status
#define SERIAL_RAW			9	// extreme high speed (1megabit) serial of raw a/d
#define SERIAL_MAVLINK		10	// mavlink protocol

// Constants
#define FILTERSHIFT 3
#define RMAX   0b0100000000000000	//	1.0 in 2.14 fractional format
#define GRAVITY ((long)(5280.0/SCALEACCEL))  // gravity in AtoD/2 units

#if (BOARD_TYPE == ASPG_BOARD)		// these really should come from mixer.h but thats also a different range
#define SERVOCENTER 7500
#define SERVORANGE (int) (SERVOSAT*2500)
#define SERVOMAX SERVOCENTER + SERVORANGE
#define SERVOMIN SERVOCENTER - SERVORANGE
#else
#define SERVOCENTER 3000
#define SERVORANGE (int) (SERVOSAT*1000)
#define SERVOMAX SERVOCENTER + SERVORANGE
#define SERVOMIN SERVOCENTER - SERVORANGE
#endif

// Serial Output Format (Can be SERIAL_NONE, SERIAL_DEBUG, SERIAL_ARDUSTATION, SERIAL_UDB,
// SERIAL_UDB_EXTRA, SERIAL_OSD_REMZIBI or SERIAL_MAGNETOMETER, SERIAL_STATUS, SERIAL_RAW )
//#define SERIAL_NONE			0
//#define SERIAL_DEBUG		(SERIAL_NONE+1)
//#define SERIAL_ARDUSTATION	(SERIAL_DEBUG+1)
//#define SERIAL_UDB			(SERIAL_ARDUSTATION+1)
//#define SERIAL_UDB_EXTRA	(SERIAL_UDB+1)
//#define SERIAL_OSD_REMZIBI	(SERIAL_UDB_EXTRA+1)
//#define SERIAL_MAGNETOMETER	(SERIAL_OSD_REMZIBI+1)
//#define SERIAL_STATUS		(SERIAL_MAGNETOMETER+1)
//#define SERIAL_RAW			(SERIAL_STATUS+1)

#endif
