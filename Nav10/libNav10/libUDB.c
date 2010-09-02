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


#include "libUDB_internal.h"

#if (BOARD_IS_CLASSIC_UDB)
_FOSC( CSW_FSCM_OFF & HS ) ;		// external high speed crystal
_FWDT( WDT_OFF ) ;					// no watchdog timer
_FBORPOR( 	PBOR_OFF &				// brown out detection off
			MCLR_EN &				// enable MCLR
			RST_PWMPIN &			// pwm pins as pwm
			PWMxH_ACT_HI &			// PWMH is active high
			PWMxL_ACT_HI ) ;		// PMWL is active high
_FGS( CODE_PROT_OFF ) ;				// no protection
_FICD( 0xC003 ) ;					// normal use of debugging port

#elif (BOARD_TYPE == UDB4_BOARD)
_FOSCSEL(FNOSC_FRCPLL) ;			// fast RC plus PLL
_FOSC(	FCKSM_CSECMD &
		OSCIOFNC_ON &
		POSCMD_NONE ) ;
_FWDT(	FWDTEN_OFF &
		WINDIS_OFF ) ;
_FGS(	GSS_OFF &
		GCP_OFF &
		GWRP_OFF ) ;
_FPOR(	FPWRT_PWR1 ) ;
_FICD(	JTAGEN_OFF &
		ICS_PGD2 ) ;
#endif


union udb_fbts_byte udb_flags ;

boolean timer_5_on = 0 ;
boolean needSaveExtendedState = 0 ;
int defaultCorcon = 0 ;


void udb_init(void)
{
	defaultCorcon = CORCON ;
	
#if (BOARD_TYPE == UDB4_BOARD)
	CLKDIVbits.PLLPRE = 1 ;
	PLLFBDbits.PLLDIV = 50 ; // FOSC = 32 MHz (FRC = 7.37MHz, N1=3, N2=4, M = 52)
#endif

	udb_flags.B = 0 ;
	
	udb_init_leds() ;
	udb_init_ADC() ;
	udb_init_clock() ;
	udb_init_capture() ;
	udb_init_I2C() ;
	udb_init_GPS() ;
	udb_init_USART() ;
	udb_init_pwm() ;
	SRbits.IPL = 0 ;	// turn on all interrupt priorities
	
	return ;
}


void udb_run(void)
{
	//  nothing else to do... entirely interrupt driven
	while (1)
	{
		// pause cpu counting timer while not in an ISR
		indicate_loading_main ;
	}
	// Never returns
}


void udb_init_leds( void )
{
	
#if (BOARD_IS_CLASSIC_UDB == 1)
	TRISFbits.TRISF0 = 0 ;
	
#elif (BOARD_TYPE == UDB4_BOARD)
	_TRISE1 = _TRISE2 = _TRISE3 = _TRISE4 = 0 ;
	_LATE1 = _LATE2 = _LATE3 = _LATE4 = LED_OFF ;
#endif
	
	return ;
}


// the compiler does not respect the resource used by the Microchip math
// library, so interrupts need to save and restore extended state, and
// reset CORCON if firing in the middle of a math lib call.
void udb_setDSPLibInUse(boolean inUse)
{
	needSaveExtendedState = inUse ;
	return ;
}


void udb_a2d_record_offsets(void)
{
	// almost ready to turn the control on, save the input offsets
	udb_xaccel.offset = udb_xaccel.value ;
	udb_xrate.offset = udb_xrate.value ;
	udb_yaccel.offset = udb_yaccel.value ;
	udb_yrate.offset = udb_yrate.value ;
	udb_zaccel.offset = udb_zaccel.value - ((int)(2*GRAVITY)) ; // GRAVITY is measured in A-D/2 units
	udb_zrate.offset = udb_zrate.value ;
#ifdef VREF
	udb_vref.offset = udb_vref.value ;
#endif
	return ;
}


void udb_servo_record_trims(void)
{
	int i;
	for (i=0; i <= NUM_INPUTS; i++)
		udb_pwTrim[i] = udb_pwIn[i] ;
	
	return ;
}


// saturation logic to maintain pulse width within bounds
int udb_servo_pulsesat ( long pw )
{
	if ( pw > SERVOMAX ) pw = SERVOMAX ;
	if ( pw < SERVOMIN ) pw = SERVOMIN ;
	return (int)pw ;
}
