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

#if (BOARD_TYPE == UDB4_BOARD)

//	Analog to digital processing.
//	Sampling and conversion is done automatically, so that all that needs to be done during 
//	interrupt processing is to read the data out of the buffer.
//	Raw samples are taken approximately 500 per second per channel.
//	A first order digital lowpass filter with a time constant of about 32 milliseconds 
//  is applied to improve signal to noise.

//	Variables.

struct ADchannel udb_xaccel, udb_yaccel , udb_zaccel ; // x, y, and z accelerometer channels
struct ADchannel udb_xrate , udb_yrate, udb_zrate ;  // x, y, and z gyro channels
struct ADchannel udb_vref ; // reference voltage

char sampcount = 1 ;


void udb_init_gyros( void )
{
	// turn off auto zeroing 
	_TRISC4 = _TRISB14 = 0 ;
	_LATC4 = _LATB14 = 0 ;
	
	return ;
}


void udb_init_accelerometer(void)
{
	_TRISA6 = 0 ;  // GSELECT is an output
	_LATA6 = 1 ;   // 6 G setting
	
	//	set as inputs:
	_TRISB9 = 1 ;
	_TRISB10 = 1 ;
	_TRISB11 = 1 ;
	
	return ;
}


void udb_init_ADC( void )
{
	udb_init_gyros() ;
	udb_init_accelerometer() ;
	
	udb_flags._.firstsamp = 1 ;
	
	AD2CSSL = 0 ; // start with no channels selected
	AD2PCFGL = 0b1111111111111111 ; // start with all digital, set the A/D
	
//	include the 110 degree/second scale, gyro
	/*
	AD2CSSLbits.CSS0 = 1 ;
	AD2CSSLbits.CSS3 = 1 ;
	AD2CSSLbits.CSS5 = 1 ;

	AD2PCFGLbits.PCFG0 = 0 ;
	AD2PCFGLbits.PCFG3 = 0 ;
	AD2PCFGLbits.PCFG5 = 0 ;
	*/
	
//	include the 500 degree/second scale, gyro
	AD2CSSLbits.CSS1 = 1 ;
	AD2CSSLbits.CSS4 = 1 ;
	AD2CSSLbits.CSS6 = 1 ;
	
	AD2PCFGLbits.PCFG1 = 0 ;
	AD2PCFGLbits.PCFG4 = 0 ;
	AD2PCFGLbits.PCFG6 = 0 ;
	
//	include the accelerometer in the scan:
	AD2CSSLbits.CSS9 = 1 ;
	AD2CSSLbits.CSS10 = 1 ;
	AD2CSSLbits.CSS11 = 1 ;
	
	AD2PCFGLbits.PCFG9 = 0 ;
	AD2PCFGLbits.PCFG10 = 0 ;
	AD2PCFGLbits.PCFG11 = 0 ;
	
	AD2CON1bits.AD12B = 1 ;		// 12 bit A to D
	AD2CON1bits.FORM = 3 ;		// signed fractional
	AD2CON1bits.SSRC = 7 ;		// auto convert
	AD2CON1bits.ASAM = 1 ;		// auto samp
	AD2CON1bits.SIMSAM = 0 ;	// multiple channels in sequence
	
	AD2CON2bits.VCFG = 0 ;		// use supply as reference voltage
	AD2CON2bits.CSCNA = 1 ;		// scanA ch0
	
	AD2CON2bits.ALTS = 0 ;		// always A
//	AD2CON2bits.BUFM = 1 ;		// ping-pong buffers
	
	AD2CON3bits.SAMC = 31 ;		// auto sample time = 31 TAD, approximately 248 microseconds
	AD2CON3bits.ADCS = 127 ;	// TAD = 8 microseconds
	
//	AD2CON1bits.ADDMABM = 1 ;	// DMA buffer written in conversion order
	AD2CON2bits.SMPI = 5 ;		// 6 samples
//	AD2CON4bits.DMABL = 1 ;		// double buffering
	
	_AD2IF = 0 ;		// clear the AD interrupt
	_AD2IP = 5 ;		// priority 5
	_AD2IE = 1 ;		// enable the interrupt
	AD2CON1bits.ADON = 1 ;		// turn on the A to D
	
	return ;
}


#define ADC2SAMPLE ((int)(ADC2BUF0))

void __attribute__((__interrupt__,__no_auto_psv__)) _ADC2Interrupt(void)
{	
	interrupt_save_extended_state ;
	
	indicate_loading_inter ;
	
	_AD2IF = 0 ; 	// clear the AD interrupt
	
	switch ( sampcount ) {
		case yrateBUFF :
			udb_yrate.input = ADC2SAMPLE ;
			if ( udb_flags._.firstsamp )
			{
				udb_yrate.value = udb_yrate.input ;
			}
			else
			{
				udb_yrate.value = udb_yrate.value + ((( (udb_yrate.input>>1) - (udb_yrate.value>>1) ))>>FILTERSHIFT ) ;
			}
			break;
			
		case zrateBUFF :
			udb_zrate.input = ADC2SAMPLE ;
			if ( udb_flags._.firstsamp )
			{
				udb_zrate.value = udb_zrate.input ;
			}
			else
			{
				udb_zrate.value = udb_zrate.value + ((( (udb_zrate.input>>1) - (udb_zrate.value>>1) ))>>FILTERSHIFT ) ;
			}
			break;
			
		case xrateBUFF :
			udb_xrate.input = ADC2SAMPLE ;
			if ( udb_flags._.firstsamp )
			{
				udb_xrate.value = udb_xrate.input ;
			}
			else
			{
				udb_xrate.value = udb_xrate.value + ((( (udb_xrate.input>>1) - (udb_xrate.value>>1) ))>>FILTERSHIFT ) ;
			}
			break;
			
		case zaccelBUFF :
			udb_zaccel.input = ADC2SAMPLE ;
			if ( udb_flags._.firstsamp )
			{
				udb_zaccel.value = udb_zaccel.input ;
			}
			else
			{
				udb_zaccel.value = udb_zaccel.value + ((( (udb_zaccel.input>>1) - (udb_zaccel.value>>1) ))>>FILTERSHIFT ) ;
			}
			break;
			
		case xaccelBUFF :
			udb_xaccel.input = -ADC2SAMPLE ;
			if ( udb_flags._.firstsamp )
			{
				udb_xaccel.value = udb_xaccel.input ;
			}
			else
			{
				udb_xaccel.value = udb_xaccel.value + (((( udb_xaccel.input>>1 )- (udb_xaccel.value>>1) ))>>FILTERSHIFT ) ;
			}
			break;
			
		case yaccelBUFF :
			udb_yaccel.input = -ADC2SAMPLE ;
			if ( udb_flags._.firstsamp )
			{
				udb_yaccel.value = udb_yaccel.input ;
				udb_flags._.firstsamp = 0 ;
			}
			else
			{
				udb_yaccel.value = udb_yaccel.value + ((( (udb_yaccel.input>>1) - (udb_yaccel.value>>1) ))>>FILTERSHIFT ) ;
			}
			break;
			
		default :
			break;
	}
	
	sampcount++ ;
	if ( sampcount > 6 )
	{
		sampcount = 1 ;
	}
	
	interrupt_restore_extended_state ;
	return ;
}

#endif
