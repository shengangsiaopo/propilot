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


// The Coordinate Frame and Dimensional Units of Mavlink are
// explained in detail at this web URL:-
// http://pixhawk.ethz.ch/wiki/software/coordinate_frame
// An abreviated summary is:
// Mavlink Aviation  X Axis is the UDB Aviation Y axis which is the fuselage axis.
// Mavlink Avitation Y axis is out of the right wing, and so is the negative of the UDB X Axis
// Mavlink Aviation  Z axis is downward from the plane, ans so is the same as UDB Z axis.
// Mavlink Yaw is positive to the right (same as UDB)
// Pitch is positive when the front of the plane pitches up from horizontal (opposite of UDB)
// Roll is possitive to the right of the plane (same as UDB)
// So angles follow the "right hand rule"


#include "options.h"
#include "../libUDB/libUDB.h"
#if (SERIAL_OUTPUT_FORMAT == SERIAL_MAVLINK)

#include <string.h>
#include "defines.h"
#include "gain_variables.h"
#include "../libDCM/libDCM_internal.h" // Needed for access to internal DCM value

#define MAVLINK_COMM_NUM_BUFFERS 1
#define MAVLINK_USE_CONVENIENCE_FUNCTIONS

#include "inttypes.h"
#include "mavlink_types.h"

//#include "matrixpilot_mavlink_bridge_header.h"
mavlink_system_t mavlink_system PARAMETER = {
	.sysid = 1, .compid = MAV_COMP_ID_IMU
};

#define comm_send_ch( chan, c) udb_serial_send_char( c )

#include "common/mavlink.h"

#include "../libUDB/libUDB.h"

//#define 	SERIAL_BUFFER_SIZE 	MAVLINK_MAX_PACKET_LEN
#define 	BYTE_CIR_16_TO_RAD  ((2.0 * 3.14159265) / 65536.0 ) // Conveert 16 bit byte circular to radians
#define 	MAVLINK_FRAME_FREQUENCY	40

#define	send_text( x ) udb_serial_send_string( x )
#define uart1_send( dat, len) udb_serial_send_packet( dat, len )
#define	uart1_transmit( x ) udb_serial_send_char( x )

void mavlink_msg_recv(unsigned char);
void handleMessage(mavlink_message_t* msg) ;
//void send_text(uint8_t text[]) ;
//void uart1_send(uint8_t buf[], uint16_t len) ;
boolean is_this_the_moment_to_send( unsigned char counter, unsigned char max_counter ) ;
boolean mavlink_frequency_send( unsigned char transmit_frequency, unsigned char counter) ;
boolean mavlink_check_target( uint8_t target_system, uint8_t target_component ) ;

union intbb voltage_milis = {0} ;
unsigned char counter_40hz = 0 ;
uint64_t usec = 0 ;			// A measure of time in microseconds (should be from Unix Epoch).

int sb_index = 0 ;
int end_index = 0 ;
unsigned char serial_buffer[SERIAL_BUFFER_SIZE] FAR_BUF = {0};

float previous_earth_pitch  = 0.0 ;
float previous_earth_roll   = 0.0 ;
float previous_earth_yaw    = 0.0 ;

#define     MAVLINK_ATTITUDE_FREQ	8 // Be careful if you change this. Requested frequency may not be actual freq.
unsigned char PARAMETER streamRateRawSensors      = 1 ;
unsigned char PARAMETER streamRateRCChannels      = 1 ;
unsigned char PARAMETER streamRateExtendedStatus  = 1; 
unsigned char PARAMETER streamRateRawController   = MAVLINK_ATTITUDE_FREQ; 
unsigned char PARAMETER streamRatePosition        = MAVLINK_ATTITUDE_FREQ; 
unsigned char PARAMETER streamRateExtra1 = 0; 
unsigned char PARAMETER streamRateExtra2 = 0; 
unsigned char PARAMETER streamRateExtra3 = 0; 
//unsigned char streamRateRawSensorFusion = 0; 

//void init_serial()
//{
//	udb_serial_set_rate(SERIAL_OUTPUT_BAUD) ;
//  udb_serial_set_rate(19200) ;
//	udb_serial_set_rate(38400) ;
//	udb_serial_set_rate(57600) ;
//	udb_serial_set_rate(115200) ;
//	udb_serial_set_rate(230400) ;
//	udb_serial_set_rate(460800) ;
//	udb_serial_set_rate(921600) ; // yes, it really will work at this rate
//return ;
//}

inline void mavlink_send_uart(mavlink_channel_t chan, mavlink_message_t* msg)
{
	// uavDB board implementation - lets get this fixed
//	udb_serial_send_char( MAVLINK_STX );
//	udb_serial_send_char( msg->len );
//	udb_serial_send_char( msg->seq );
//	udb_serial_send_char( msg->sysid );
//	udb_serial_send_char( msg->compid );
//	udb_serial_send_char( msg->msgid );
//	if ( (msg->msgid == 0x39) || (msg->msgid == 0x0f) )
//		Nop();
//	else Nop();
	msg->STX = MAVLINK_STX;
	udb_serial_send_packet( &msg->STX, 6 );
	udb_serial_send_packet( &msg->payload[0], msg->len );
	udb_serial_send_char( msg->ck_a );
	udb_serial_send_char( msg->ck_b );
}

void init_serial( void )
{
	udb_serial_set_rate(SERIAL_OUTPUT_BAUD) ;
//	mavlink_system.sysid  = 1 ; 				// System ID, 1-255, ID of your Plane for GCS
//	mavlink_system.compid = MAV_COMP_ID_IMU ;	// Component/Subsystem ID,  (1-255) MatrixPilot on UDB is component 1.
#if ( SERIAL_INPUT_FORMAT == SERIAL_MAVLINK )
//	streamRateRCChannels = 0 ;
//	streamRateRawSensors = 0 ;
#else 
	streamRateRCChannels = 10 ;
	streamRateRawSensors = 40 ;
#endif
}

static inline int udb_serial_callback_get_char_to_send(void)
// routine returns a signed integer so as to allow sending binary code (including 0x00) over serial
{ 
	if ( sb_index < end_index && sb_index < SERIAL_BUFFER_SIZE ) // ensure never end up racing thru memory.
	{
		unsigned char txchar = serial_buffer[ sb_index++ ] ;
		return (int) txchar ;
	}
	else
	{
		sb_index = 0 ;
		end_index = 0 ;
	}
	
	return -1 ;
}


////////////////////////////////////////////////////////////////////////////////
// 
// MAIN MATRIXPILOT MAVLINK CODE FOR RECEIVING COMMANDS FROM THE GROUND CONTROL STATION
//

#if (  SERIAL_INPUT_FORMAT == SERIAL_MAVLINK )
mavlink_message_t msg ;
mavlink_status_t  r_mavlink_status ;

void udb_serial_callback_received_char(char rxchar)
{
	if (mavlink_parse_char(0, rxchar, &msg, &r_mavlink_status ))
    {
		handleMessage(&msg) ;
	}
	return ;
}
#else 
void udb_serial_callback_received_char(char rxchar)
{
	return ; // Do nothing with received characters MAVLINK disabled for input
}
#endif

#if (  SERIAL_INPUT_FORMAT == SERIAL_MAVLINK )
extern unsigned int maxstack ;
// void mavlink_msg_param_value_send_by_index(unsigned char index) ;
unsigned char send_variables_counter = 0;
unsigned char send_by_index = 0 ;

// ROUTINES FOR CHANGING UAV ONBOARD PARAMETERS
// All paramaters are sent as type (float) between Ground Control Station and MatrixPilot.
// So paramaters have to be converted between type (float) and their normal representation.
// An explanation of the MAVLink protocol for changing paramaters can be found at:
// http://www.qgroundcontrol.org/parameter_interface

enum type_codes {
	TYPE_FLOAT = 0,		// is a 32 bit float
	TYPE_2Q14,			// sign, mag, mantisa (range -2 to +2)
	TYPE_Q15,			// sign, mantisa (range -1 to +1)
	TYPE_INT,			// 16 bit signed int (-32k to +32k)
	TYPE_UINT,			// 16 bit unsigned int (0 to 64kk)
	TYPE_CHAR,			// 8 bit signed int (-128 to +127)
	TYPE_UCHAR,			// 8 bit unsigned int (0 to 255)
	TYPE_CHAR_A,		// 8 bit signed int (-128 to +127) angle, converts to 0 -> 360 degrees
};

typedef union __mavlink_parameter_p {
	float 	*p_float;
	int		*p_2Q14;
	int		*p_Q15;
	int		*p_int;
unsigned int *p_uint;
	char	*p_char;
unsigned char *p_uchar;
signed char	*p_char_a;
} MAVLINK_PARAMETER_P;

typedef struct __mavlink_parameter 	{ 	
					int8_t name[16];// Name that will be displayed in the GCS
					float min ;     // Minimum allowed (float) value for parameter
					float max ;     // Maximum allowed (float) value for parameter
		MAVLINK_PARAMETER_P var; 	// address of parameter to send to GCS after converting to float.
			unsigned char type ;    // type code of var, see type_codes enum above
					char readonly ; // Parameter is readonly (true) or Read / Write (false)
} MAVLINK_PARAMETER, *LPMAVLINK_PARAMETER;

#define READONLY	1
#define READWRITE	0

#define USE_VARIABLE_MAG

#if defined(USE_VARIABLE_MAG)
extern char mag_xy;
extern int mag_x_sign;
extern int mag_y_sign;
#endif


const MAVLINK_PARAMETER mavlink_parameters_list[] =	{
	{"PID_RollKP"     , 0.0 , 0.4  ,  .var.p_2Q14 = &rollkp                 , TYPE_2Q14, READWRITE },
	{"PID_RollKD"     , 0.0 , 0.4  ,  .var.p_2Q14 = &rollkd                 , TYPE_2Q14, READWRITE },
	{"PID_YawKPAIL"   , 0.0 , 0.4  ,  .var.p_2Q14 = &yawkpail               , TYPE_2Q14, READWRITE },
	{"PID_YawKDAIL"   , 0.0 , 0.4  ,  .var.p_2Q14 = &yawkdail               , TYPE_2Q14, READWRITE },
	{"PID_Pitchgain"  , 0.0 , 0.4  ,  .var.p_2Q14 = &pitchgain              , TYPE_2Q14, READWRITE },
	{"PID_PitchKD"    , 0.0 , 0.4  ,  .var.p_2Q14 = &pitchkd                , TYPE_2Q14, READWRITE },
	{"PID_YawKDrud"   , 0.0 , 0.4  ,  .var.p_2Q14 = &yawkdrud               , TYPE_2Q14, READWRITE },
	{"PID_RollKPrud"  , 0.0 , 0.4  ,  .var.p_2Q14 = &rollkprud              , TYPE_2Q14, READWRITE },

	{"ML_SysID"       , 1.0 , 254.0,  .var.p_uchar = &mavlink_system.sysid  , TYPE_UCHAR, READWRITE },
	{"ML_CompID"      , 0.0 , 255.0,  .var.p_uchar = &mavlink_system.compid , TYPE_UCHAR, READWRITE },
	{"ML_RawSensors"  , 0.0 , 250.0,  .var.p_uchar = &streamRateRawSensors  , TYPE_UCHAR, READWRITE },
	{"ML_RCChannels"  , 0.0 , 250.0,  .var.p_uchar = &streamRateRCChannels  , TYPE_UCHAR, READWRITE },
	{"ML_ExtendStat"  , 0.0 , 250.0,  .var.p_uchar = &streamRateExtendedStatus, TYPE_UCHAR, READWRITE },
	{"ML_RawControl"  , 0.0 , 250.0,  .var.p_uchar = &streamRateRawController, TYPE_UCHAR, READWRITE },
	{"ML_Position"    , 0.0 , 250.0,  .var.p_uchar = &streamRatePosition    , TYPE_UCHAR, READWRITE },
	{"ML_RateExtra1"  , 0.0 , 250.0,  .var.p_uchar = &streamRateExtra1      , TYPE_UCHAR, READWRITE },
	{"ML_RateExtra2"  , 0.0 , 250.0,  .var.p_uchar = &streamRateExtra2      , TYPE_UCHAR, READWRITE },
	{"ML_RateExtra3"  , 0.0 , 250.0,  .var.p_uchar = &streamRateExtra3      , TYPE_UCHAR, READWRITE },

	{"CFG_DECLIN"     , -128.0, 127.0,.var.p_char_a = &DECLINATIONANGLE     , TYPE_CHAR_A, READWRITE },
#if defined(USE_VARIABLE_MAG)
	{"CFG_DECxCH"     ,    0.0,   1.0,.var.p_char  = &mag_xy                , TYPE_CHAR, READWRITE },
	{"CFG_DECxSC"     ,   -1.0,   1.0,.var.p_int   = &mag_x_sign            , TYPE_INT, READWRITE },
	{"CFG_DECySC"     ,   -1.0,   1.0,.var.p_int   = &mag_y_sign            , TYPE_INT, READWRITE },
#endif


#if ( RECORD_FREE_STACK_SPACE ==  1)
#if defined(__dsPIC30F)
	{"MAXSTACK", 0.0 , 4096.0 ,  .var.p_uint = &maxstack, TYPE_UINT, READWRITE },
#else
	{"MAXSTACK", 0.0 , 32767.0 ,  .var.p_uint = &maxstack, TYPE_UINT, READWRITE },
#endif
#endif
	} ;    

const int count_of_parameters_list =  sizeof mavlink_parameters_list / sizeof mavlink_parameters_list[0] ;

void mavlink_param( unsigned char idx, unsigned char rw, float f_value )
{
	float	f_temp;
	int i_temp;
//	unsigned int ui_temp;

	if ( idx >= count_of_parameters_list ) return;	// invalid entry

	if ( rw == 0 ) {	// read & send request
		switch ( mavlink_parameters_list[idx].type ) {
		case TYPE_FLOAT:
			f_temp = *mavlink_parameters_list[idx].var.p_float;
		break;
		case TYPE_2Q14:
			i_temp = *mavlink_parameters_list[idx].var.p_2Q14;
			f_temp = (float)i_temp / (float)RMAX;
		break;
		case TYPE_Q15:
			i_temp = *mavlink_parameters_list[idx].var.p_Q15;
			f_temp = (float)i_temp / 32767.0;
		break;
		case TYPE_INT:
			f_temp = (float)*mavlink_parameters_list[idx].var.p_int;
		break;
		case TYPE_UINT:
			f_temp = (float)*mavlink_parameters_list[idx].var.p_uint;
		break;
		case TYPE_CHAR:
			f_temp = (float)*mavlink_parameters_list[idx].var.p_char;
		break;
		case TYPE_UCHAR:
			f_temp = (float)*mavlink_parameters_list[idx].var.p_uchar;
		break;
		case TYPE_CHAR_A:
			f_temp = (float)*mavlink_parameters_list[idx].var.p_char_a;
			f_temp = f_temp * 180.0 / 128.0;
//			if ( f_temp < 0.0 )
//				f_temp = 180.0 + f_temp;
		break;
		default:
			f_temp = 0.0;
		break;
		}
		mavlink_msg_param_value_send( MAVLINK_COMM_0, mavlink_parameters_list[idx].name ,
				f_temp , count_of_parameters_list, idx ); // send packet
	} else {	// write request
		if ( (f_value > mavlink_parameters_list[idx].max) || (f_value < mavlink_parameters_list[idx].min) )
			return;
		else
		switch ( mavlink_parameters_list[idx].type ) {
		case TYPE_FLOAT:
			*mavlink_parameters_list[idx].var.p_float = f_value;
		break;
		case TYPE_2Q14:
			i_temp = (int) ((float)f_value * (float)RMAX);
			*mavlink_parameters_list[idx].var.p_2Q14 = i_temp;
		break;
		case TYPE_Q15:
			i_temp = (int) ((float)f_value * (float)32767.0);
			*mavlink_parameters_list[idx].var.p_2Q14 = i_temp;
		break;
		case TYPE_INT:
			*mavlink_parameters_list[idx].var.p_int = (int)f_value;
		break;
		case TYPE_UINT:
			*mavlink_parameters_list[idx].var.p_uint = (unsigned int)f_value;
		break;
		case TYPE_CHAR:
			*mavlink_parameters_list[idx].var.p_char = (char)f_value;
		break;
		case TYPE_UCHAR:
			*mavlink_parameters_list[idx].var.p_uchar = (unsigned char)f_value;
		break;
		case TYPE_CHAR_A:
			if ( f_value > 180.0 )
				f_value = f_value - 360.0;
			f_value = f_value * 128.0 / 180.0;
			*mavlink_parameters_list[idx].var.p_char_a = (char)f_value;
		break;
		default:
			f_temp = 0.0;
		break;
		}
	}	
	
}

// END OF GENERAL ROUTINES FOR CHANGING UAV ONBOARD PARAMETERS

boolean mavlink_check_target( uint8_t target_system, uint8_t target_component )
{
	if ( target_system == mavlink_system.sysid )
			// &&
			//( target_component == mavlink_system.compid ))
			//( target_component == 25 )
			// Note QGroundControl 0.8 may have bug in that request for list of parameters always uses component id of 25 even though we are using component id 1.
			// However when setting parameters QGroundConrol then appears to use the correct component id of 1. So for now we do not check component Ids.
	{
		return true ;
	}
	else
	{
		send_text( (unsigned char*) "System Target Check Failed: 0x");
		uart1_transmit(( target_system >> 4 ) + 0x30 ) ;
		uart1_transmit(( target_system & 0x0f ) + 0x30 ) ;
		send_text( (unsigned char*) " 0x");
		uart1_transmit(( target_component >> 4 ) + 0x30 ) ;
		uart1_transmit(( target_component & 0x0f ) + 0x30 ) ;
		send_text( (unsigned char*) "\r\n");
		return false ;
	}
}

// Portions of the following code in handlesmessage() are templated off source code written by James Goppert for the
// ArdupilotMega, and are used by his kind permission and also in accordance with the GPS V3 licensing
// of that code.

void handleMessage(mavlink_message_t* msg)
// This is the main routine for taking action against a parsed message from the GCS
{
	// send_text( (const unsigned char*) "Handling message ID ..");
	// uart1_transmit(( msg->msgid >> 4 ) + 0x30 ) ;
	// uart1_transmit(( msg->msgid & 0x0f ) + 0x30 ) ;
	// send_text( (unsigned char*) "\r\n");

	switch (msg->msgid)	
	{
	    case MAVLINK_MSG_ID_HEARTBEAT:  
	    {
			Nop();
		}
	    case MAVLINK_MSG_ID_REQUEST_DATA_STREAM:  
	    {
	        // decode
	        mavlink_request_data_stream_t packet;
	        mavlink_msg_request_data_stream_decode(msg, &packet);
			// send_text((const unsigned char*) "Action: Request data stream\r\n");
	        if (mavlink_check_target(packet.target_system,packet.target_component) == false ) break;
	
	        int freq = 0; // packet frequency
	
	        if (packet.start_stop == 0) freq = 0; // stop sending
	        else if (packet.start_stop == 1) freq = packet.req_message_rate; // start sending
	        else break;
	
	        switch(packet.req_stream_id)
	        {
	        case MAV_DATA_STREAM_ALL:
	            streamRateRawSensors = freq ; 
	            streamRateExtendedStatus = freq; 
	            streamRateRCChannels = freq; 
	            streamRateRawController = freq; 
//	            streamRateRawSensorFusion = freq; 
	            streamRatePosition = freq; 
	            streamRateExtra1 = freq; 
	            streamRateExtra2 = freq; 
	            streamRateExtra3 = freq; 
	            break;
	        case MAV_DATA_STREAM_RAW_SENSORS:
				// send_text((unsigned char*) "Action: Request Raw Sensors\r\n");
	            streamRateRawSensors = freq ;  
	            break;
	        case MAV_DATA_STREAM_EXTENDED_STATUS:
	            streamRateExtendedStatus = freq; 
	            break;
	        case MAV_DATA_STREAM_RC_CHANNELS:
	            streamRateRCChannels = freq; 
	            break;
	        case MAV_DATA_STREAM_RAW_CONTROLLER:
	            streamRateRawController = freq; 
	            break;
//	        case MAV_DATA_STREAM_RAW_SENSOR_FUSION:
//	            // streamRateRawSensorFusion = freq; 
//	            break;
	        case MAV_DATA_STREAM_POSITION:
	            streamRatePosition = freq; 
	            break;
	        case MAV_DATA_STREAM_EXTRA1:
	            streamRateExtra1 = freq; 
	            break;
	        case MAV_DATA_STREAM_EXTRA2:
	            streamRateExtra2 = freq; 
	            break;
	        case MAV_DATA_STREAM_EXTRA3:
	            streamRateExtra3 = freq; 
	            break;
	        default:
	            break;
	        }
	    }
	    case MAVLINK_MSG_ID_ACTION:
	    {
			// send_text((unsigned char*) "Action: Specific Action Required\r\n");
	        // decode
	        mavlink_action_t packet;
	        mavlink_msg_action_decode(msg, &packet);
	        if (mavlink_check_target(packet.target,packet.target_component) == false ) break;
			
	        switch(packet.action)
	        {
	
	            case MAV_ACTION_LAUNCH:
					// send_text((unsigned char*) "Action: Launch !\r\n");
	                //set_mode(TAKEOFF);
						
	                break;
	
	            case MAV_ACTION_RETURN:
					// send_text((unsigned char*) "Action: Return !\r\n");
	                //set_mode(RTL);
	                break;
	
	            case MAV_ACTION_EMCY_LAND:
					// send_text((unsigned char*) "Action: Emergency Land !\r\n");
	                //set_mode(LAND);
	                break;
	
	            case MAV_ACTION_HALT: 
					// send_text((unsigned char*) "Action: Halt !\r\n");
	                //loiter_at_location();
	                break;
	
	            case MAV_ACTION_MOTORS_START:
	            case MAV_ACTION_CONFIRM_KILL:
	            case MAV_ACTION_EMCY_KILL:
	            case MAV_ACTION_MOTORS_STOP:
	            case MAV_ACTION_SHUTDOWN: 
	                //set_mode(MANUAL);
	                break;
	
	            case MAV_ACTION_CONTINUE:
	                //process_next_command();
	                break;
	
	            case MAV_ACTION_SET_MANUAL: 
	                //set_mode(MANUAL);
	                break;
	
	            case MAV_ACTION_SET_AUTO:
	                //set_mode(AUTO);
	                break; 
	
	            case MAV_ACTION_STORAGE_READ:
					if ( iEEpresent && udb_flags._.radio_on && flags._.man_req && !flags._.read_EE && !flags._.write_EE)
						send_text((unsigned char*) "\r\nAction: EE Storage Read "),  flags._.read_EE = 1;
					else if ( !flags._.read_EE )  // allready doing it
						send_text((unsigned char*) "\r\nILLEGAL ACTION: EE Storage Read ");
	                break; 
	
	            case MAV_ACTION_STORAGE_WRITE:
					if ( iEEpresent && udb_flags._.radio_on && flags._.man_req && !flags._.read_EE && !flags._.write_EE )
						send_text((unsigned char*) "\r\nAction: EE Storage Write "),  flags._.write_EE = 1;
					else if ( !flags._.write_EE ) // allready doing it
						send_text((unsigned char*) "\r\nILLEGAL ACTION: EE Storage Write ");
	                break;
	
	            case MAV_ACTION_CALIBRATE_RC:
					//send_text((unsigned char*) "Action: Calibrate RC\r\n"); 
	                break;
	            
	            case MAV_ACTION_CALIBRATE_GYRO:
	            case MAV_ACTION_CALIBRATE_MAG: 
	            case MAV_ACTION_CALIBRATE_ACC: 
	            case MAV_ACTION_CALIBRATE_PRESSURE:
	            case MAV_ACTION_REBOOT: 
	                //startup_IMU_ground();     
	                break; 
	
	            case MAV_ACTION_REC_START: break; 
	            case MAV_ACTION_REC_PAUSE: break; 
	            case MAV_ACTION_REC_STOP: break; 
	
	            case MAV_ACTION_TAKEOFF:
					//send_text((unsigned char*) "Action: Take Off !\r\n");
	                //set_mode(TAKEOFF);
	                break; 
	
	            case MAV_ACTION_NAVIGATE:
					// send_text((unsigned char*) "Action: Navigate !\r\n");
	                //set_mode(AUTO);
	                break; 
	
	            case MAV_ACTION_LAND:
	                //set_mode(LAND);
	                break; 
	
	            case MAV_ACTION_LOITER:
	                //set_mode(LOITER);
	                break; 
	
	            default: break;
	        }
	    }
	    break;
	
	    case MAVLINK_MSG_ID_WAYPOINT_REQUEST_LIST:
	    {
			// send_text((unsigned char*) "waypoint request list\r\n");
	
	        // decode
	        //mavlink_waypoint_request_list_t packet;
	        //mavlink_msg_waypoint_request_list_decode(msg, &packet);
	        //if (mavlink_check_target(packet.target_system,packet.target_component)) break;
	
	        // Start sending waypoints
	        //mavlink_msg_waypoint_count_send(chan,msg->sysid,
	                                        //msg->compid,get(PARAM_WP_TOTAL));
	        //global_data.waypoint_timelast_send = millis();
	        //global_data.waypoint_sending = true;
	        //global_data.waypoint_receiving = false;
	        //global_data.waypoint_dest_sysid = msg->sysid;
	        //global_data.waypoint_dest_compid = msg->compid;
	
	    }
	    break;
	
	    case MAVLINK_MSG_ID_WAYPOINT_REQUEST:
	    {
			// send_text((unsigned char*)"waypoint request\r\n");
	
	        // Check if sending waypiont
	        //if (!global_data.waypoint_sending) break;
	
	        // decode
	        //mavlink_waypoint_request_t packet;
	        //mavlink_msg_waypoint_request_decode(msg, &packet);
	        //if (mavlink_check_target(packet.target_system,packet.target_component)) break;
	
	        // send waypoint
	        //tell_command = get_wp_with_index(packet.seq);
	
	        // set frame of waypoint
	        //uint8_t frame = MAV_FRAME_GLOBAL; // reference frame 
	        //uint8_t action = MAV_ACTION_NAVIGATE; // action
	        //uint8_t orbit_direction = 0; // clockwise(0), counter-clockwise(1)
	        //float orbit = 0; // loiter radius
	        //float param1 = 0, param2 = 0;
	
	        //switch(tell_command.id)
	        //{
	
	        //case CMD_WAYPOINT: // navigate
	            //action = MAV_ACTION_NAVIGATE; // action
	            //break;
	
	       // case CMD_LOITER_TIME: // loiter
	            //orbit = get(PARAM_WP_RADIUS); // XXX setting loiter radius as waypoint acceptance radius
	            //action = MAV_ACTION_LOITER; // action
	            //param1 = get(PARAM_WP_RADIUS);
	            //param2 = tell_command.p1*100; // loiter time
	            //break;
	
	       // case CMD_TAKEOFF: // takeoff
	            //action = MAV_ACTION_TAKEOFF;
	            //break;
	
	        //case CMD_LAND: // land
	            //action = MAV_ACTION_LAND;
	            //break; 
	
	        //defaut:
				//gcs.send_text("command not handled");
	            //break;
	        //}
	
	        // time that the mav should loiter in milliseconds
	        //uint8_t current = 0; // 1 (true), 0 (false)
	        //if (packet.seq == get(PARAM_WP_INDEX)) current = 1;
	        //float yaw_dir = 0; // yaw orientation in radians, 0 = north XXX: what does this do?
	        //uint8_t autocontinue = 1; // 1 (true), 0 (false)
	        //float x = tell_command.lng/1.0e7; // local (x), global (longitude)
	        //float y = tell_command.lat/1.0e7; // local (y), global (latitude)
	        //float z = tell_command.alt/1.0e2; // local (z), global (altitude)
	        // note XXX: documented x,y,z order does not match with gps raw
	        //mavlink_msg_waypoint_send(chan,msg->sysid,
	                                  //msg->compid,packet.seq,frame,action,
	                                  //orbit,orbit_direction,param1,param2,current,x,y,z,yaw_dir,autocontinue);
	
	        // update last waypoint comm stamp
	        //global_data.waypoint_timelast_send = millis();
	    }
	    break;
	
	    case MAVLINK_MSG_ID_WAYPOINT_ACK:
	    {
			send_text((unsigned char*)"waypoint ack\r\n");
	
	        // decode
	        //mavlink_waypoint_ack_t packet;
	        //mavlink_msg_waypoint_ack_decode(msg, &packet);
	        //if (mavlink_check_target(packet.target_system,packet.target_component)) break;
	
	        // check for error
	        //uint8_t type = packet.type; // ok (0), error(1)
	
	        // turn off waypoint send
	        //global_data.waypoint_sending = false;
	    }
	    break;
	
	    case MAVLINK_MSG_ID_PARAM_REQUEST_LIST:
	    {
			//send_text((unsigned char*)"param request list\r\n");
	
	        // decode
	        mavlink_param_request_list_t packet;
	        mavlink_msg_param_request_list_decode(msg, &packet);
	        if ( mavlink_check_target(packet.target_system,packet.target_component) == true )
			{
				// Start sending parameters
	        	udb_flags._.mavlink_send_variables = 1 ;
			}
	    }
	    break;
	
	    case MAVLINK_MSG_ID_WAYPOINT_CLEAR_ALL:
	    {
			//send_text((unsigned char*)"waypoint clear all\r\n");
	
	        // decode
	        //mavlink_waypoint_clear_all_t packet;
	        //mavlink_msg_waypoint_clear_all_decode(msg, &packet);
	        //if (mavlink_check_target(packet.target_system,packet.target_component)) break;
	
	        // clear all waypoints
	        //uint8_t type = 0; // ok (0), error(1)
	        //set(PARAM_WP_TOTAL,0);
	
	        // send acknowledgement 3 times to makes sure it is received
	        //for (int i=0;i<3;i++) mavlink_msg_waypoint_ack_send(chan,msg->sysid,msg->compid,type);
	
	        break;
	    }
	
	    case MAVLINK_MSG_ID_WAYPOINT_SET_CURRENT:
	    {
			//send_text((unsigned char*)"waypoint set current\r\n");
	
	        // decode
	        //mavlink_waypoint_set_current_t packet;
	        //mavlink_msg_waypoint_set_current_decode(msg, &packet);
	        //if (mavlink_check_target(packet.target_system,packet.target_component)) break;
	
	        // set current waypoint
	        //set(PARAM_WP_INDEX,packet.seq);
			//{
				//Location temp;	// XXX this is gross
				//temp = get_wp_with_index(packet.seq);
				//set_next_WP(&temp);
			//}
	        //mavlink_msg_waypoint_current_send(chan,get(PARAM_WP_INDEX));
	        break;
	    }
	
	    case MAVLINK_MSG_ID_WAYPOINT_COUNT:
	    {
			//send_text((unsigned char*)"waypoint count\r\n");
	
	        // decode
	        //mavlink_waypoint_count_t packet;
	        //mavlink_msg_waypoint_count_decode(msg, &packet);
	        //if (mavlink_check_target(packet.target_system,packet.target_component)) break;
	
	        // start waypoint receiving
	        //set(PARAM_WP_TOTAL,packet.count);
	        //if (get(PARAM_WP_TOTAL) > MAX_WAYPOINTS)
	            //set(PARAM_WP_TOTAL,MAX_WAYPOINTS);
	        //global_data.waypoint_timelast_receive = millis();
	        //global_data.waypoint_receiving = true;
	        //global_data.waypoint_sending = false;
	        //global_data.waypoint_request_i = 0;
	        break;
	    }
	
	    case MAVLINK_MSG_ID_WAYPOINT:
	    {
			//send_text((unsigned char*)"waypoint\r\n");
	        // Check if receiving waypiont
	        //if (!global_data.waypoint_receiving) break;
	
	        // decode
	        //mavlink_waypoint_t packet;
	        //mavlink_msg_waypoint_decode(msg, &packet);
	        //if (mavlink_check_target(packet.target_system,packet.target_component)) break;
	
	        // check if this is the requested waypoint
	        //if (packet.seq != global_data.waypoint_request_i) break;
	
	        // store waypoint
	       // uint8_t loadAction = 0; // 0 insert in list, 1 exec now
	
	        //switch (packet.frame)
	        //{
	            //case MAV_FRAME_GLOBAL:
	            //{
	                //tell_command.lng = 1.0e7*packet.x;
	                //tell_command.lat = 1.0e7*packet.y;
	                //tell_command.alt = packet.z*1.0e2;
	               // break;
	            //}
	
	            //case MAV_FRAME_LOCAL: // local (relative to home position)
	            //{
	                //tell_command.lng = 1.0e7*ToDeg(packet.x/
	                        //(radius_of_earth*cos(ToRad(home.lat/1.0e7)))) + home.lng;
	                //tell_command.lat = 1.0e7*ToDeg(packet.y/radius_of_earth) + home.lat;
	                //tell_command.alt = -packet.z*1.0e2 + home.alt;
	                //break;
	            //}
	        //}
	
	        // defaults
	        //tell_command.id = CMD_BLANK;
	
	       // switch (packet.action)
	        //{
	        
	            //case MAV_ACTION_TAKEOFF:
	            //{
	                //tell_command.id = CMD_TAKEOFF;
	                //break;
	           // } 
	            //case MAV_ACTION_LAND:
	            //{
	                //tell_command.id = CMD_LAND;
	                //break;
	            //}
	
	            //case MAV_ACTION_NAVIGATE:
	            //{
	                //tell_command.id = CMD_WAYPOINT;
	               // break;
	            //}
	
	            //case MAV_ACTION_LOITER:
	            //{
	                //tell_command.id = CMD_LOITER_TIME;
	               // tell_command.p1 = packet.param2/1.0e2;
	               // break;
	            //}
	        //}
	
	        // save waypoint
	        //set_wp_with_index(tell_command, packet.seq);
	
	        // update waypoint receiving state machine
	        //global_data.waypoint_timelast_receive = millis();
	        //global_data.waypoint_request_i++;
	
	        //if (global_data.waypoint_request_i == get(PARAM_WP_TOTAL))
	        //{
				//gcs.send_text("flight plane received");
	            //uint8_t type = 0; // ok (0), error(1)
	            //mavlink_msg_waypoint_ack_send(chan,msg->sysid,msg->compid,type);
	            //global_data.waypoint_receiving = false;
	           	// XXX ignores waypoint radius for individual waypoints, can
				// only set WP_RADIUS parameter
	        //}
	        break;
	    }
	
	    case MAVLINK_MSG_ID_PARAM_SET:
	    {
	        // decode
			//send_text((unsigned char*)"Param Set\r\n");
	        mavlink_param_set_t packet;
	        mavlink_msg_param_set_decode(msg, &packet);
	        if (mavlink_check_target(packet.target_system,packet.target_component) == false)
			{
				send_text((unsigned char*) "failed target system check on parameter set \r\n");
				break;
			}
			else
			{
		        // set parameter
		        const char * key = (const char*) packet.param_id;
		
		        // iterate known parameters
				int i = 0 ;
		        for ( i = 0; i < count_of_parameters_list ; i++) 
				{
		            // compare key with parameter name
		            if (!strncmp(key,(const char *) mavlink_parameters_list[i].name, 15))
				    {
//						mavlink_parameters_list[i].set_parm(packet.param_value, i) ;
						mavlink_param( i, 1, packet.param_value );
						// After setting parameter, re-send it to GCS as acknowledgement of success.
						if( udb_flags._.mavlink_send_specific_variable == 0 )
						{
							send_by_index = i ;
							udb_flags._.mavlink_send_specific_variable = 1 ;
						}
#if defined(__DEBUG)
						if ( strncmp(key,"CFG_DECLIN", 10 ) ) // TODO: REMOVE THIS
						{
							dcm_init_rmat();
							dcm_flags._.first_mag_reading = 1;
						}
#endif
					}
				}
	        }
	        break;
	    } // end case

		/* Following case statement now out of date and needs re-writing for new parameter structures  - PDH
		case MAVLINK_MSG_ID_PARAM_VALUE :
		{
			send_text((unsigned char*)"Specific Param Requested\r\n");
			mavlink_param_value_t packet ;
			mavlink_msg_param_value_decode(msg, &packet) ;
			if (mavlink_check_target(packet.target_system,packet.target_component))break;
			send_by_index = packet.param_index ;
			udb_flags._.mavlink_send_specific_variable = 1 ;
			break ;
		} // end case
		*/
  	} // end switch
} // end handle mavlink

#endif	// ( SERIAL_INPUT_FORMAT == SERIAL_MAVLINK )


////////////////////////////////////////////////////////////////////////////////
// 
// MAIN MAVLINK CODE FOR SENDING COMMANDS TO THE GROUND CONTROL STATION
//

const unsigned char mavlink_freq_table[] = { 0,40,20,13,10,8,7,6,5,4,3,2,1 } ;

boolean is_this_the_moment_to_send( unsigned char counter, unsigned char max_counter )
{
	if ( counter % max_counter == 0 )	// this is really bad - causes a 17 clock divide
	{
		return true ;
	}
	else
	{
		return false;
	}	
}

boolean mavlink_frequency_send( unsigned char frequency, unsigned char counter)
// Decide whether it the correct moment to send a given telemetry update, depending on requested frequency
{
	unsigned char max_counter ;
	if ( frequency == 0 )
	{
		return false ;
	}
	else if ( frequency > 0 && frequency < 8 )
	{
		max_counter = mavlink_freq_table[frequency] ;
		return is_this_the_moment_to_send( counter, max_counter ) ;
	}	 
	else if ( frequency > 7 && frequency < 14 )
	{
		max_counter = 4 ;
		return is_this_the_moment_to_send( counter,max_counter ) ;
	}
	else if (frequency > 13 && frequency < 17)
	{
		max_counter = 3 ;
		return is_this_the_moment_to_send( counter,max_counter ) ;
	}
	else if (frequency > 16 && frequency < 24 )
	{
		max_counter = 2 ;
		return is_this_the_moment_to_send( counter,max_counter ) ;
	}
	else if ( frequency > 23 )
	{
		return true ; // send data on every call
	}
	else
	{
		return false ; // should never reach this line
	}
}

void mavlink_output_40hz( void )
{
	struct relative2D matrix_accum ;
	float earth_pitch ;			 // pitch in radians with respect to earth 
	float earth_roll ;		 	 // roll in radians of the plane with respect to earth frame
	float earth_yaw ;			 // yaw in radians with respect to earth frame
	float earth_pitch_velocity ; // radians / sec with respect to earth
	float earth_roll_velocity ;  // radians / sec with respect to earth
	float earth_yaw_velocity ;   // radians / sec with respect to earth
	float perSec;				// temp so we only cvt once
	int accum ;					 // general purpose temporary storage
	long accum_long ;			 // general purpose temporary storage
	uint8_t mode; 				// System mode, see MAV_MODE ENUM in mavlink/include/mavlink_types.h
	unsigned char spread_transmission_load = 0; // Used to spread sending of different message types over a period of 1 second.

    if ( ++counter_40hz == 40) counter_40hz = 0 ;
	
#if (BOARD_TYPE == ASPG_BOARD)
//	usec = (tagUSec_x40.WW + TMR3) / 40; // Frequency sensitive code
	usec = (tagUSec.WW + (TMR3/40)); // Frequency sensitive code
#else
	usec = usec + 25000 ; // Frequency sensitive code
#endif

	// Note that message types are arranged in order of importance so that if the serial buffer fills up,
	// critical message types are more likely to still be transmitted.

	// HEARTBEAT
	spread_transmission_load = -1;
	if ( mavlink_frequency_send( 1, counter_40hz + spread_transmission_load)) 
	{	
//		mavlink_msg_heartbeat_send(MAVLINK_COMM_0, MAV_FIXED_WING, MAV_AUTOPILOT_UAVDB) ;
		mavlink_msg_heartbeat_send(MAVLINK_COMM_0, MAV_FIXED_WING, 3) ;
	}

	// GLOBAL POSITION - derived from fused sensors
	// Note: This code assumes that Dead Reckoning is running.
	if ( !streamRateRawController )
		;
	else { spread_transmission_load = 6 / streamRateRawController ;
	if (mavlink_frequency_send( streamRateRawController, counter_40hz + spread_transmission_load))
	{ 
		
		float lat_float, lon_float, alt_float = 0.0 ;
		accum_long = IMUlocationy._.W1 + ( lat_origin.WW / 90 ) ; //  meters North from Equator
		lat_float  =  ( accum_long * 90 ) / 10000000.0 ;          // degrees North from Equator 
		lon_float =   (long_origin.WW  + ((( IMUlocationx._.W1 * 90 )) / ( float )( cos_lat / 16384.0 ))) / 10000000.0 ;
		alt_float = (float) (((((long) (IMUlocationz._.W1)) * 100) + alt_origin._.W0) / 100.0) ;
		mavlink_msg_global_position_send(MAVLINK_COMM_0, usec, 
			lat_float , lon_float, alt_float ,
			(float) IMUvelocityx._.W1, (float) IMUvelocityy._.W1, (float) IMUvelocityz._.W1 ) ; // meters per secon
	} 
	}

	// ATTITUDE
	//  Roll: Earth Frame of Reference
	if ( !streamRatePosition )
		;
	else { spread_transmission_load = 12 / streamRatePosition;
	if (mavlink_frequency_send( streamRatePosition , counter_40hz + spread_transmission_load))
	{ 
		matrix_accum.x = rmat[8] ;
		matrix_accum.y = rmat[6] ;
		accum = rect_to_polar16(&matrix_accum) ;			// binary angle (0 to 65536 = 360 degrees)
		earth_roll = ( - accum ) * BYTE_CIR_16_TO_RAD ;		// Convert to Radians
		
		//  Pitch: Earth Frame of Reference
		//  Note that we are using the matrix_accum.x
		//  left over from previous rect_to_polar in this calculation.
		//  so this Pitch calculation must follow the Roll calculation
		matrix_accum.y = rmat[7] ;
		accum = rect_to_polar16(&matrix_accum) ;			// binary angle (0 to 65536 = 360 degrees)
		earth_pitch = ( accum) * BYTE_CIR_16_TO_RAD ;		// Convert to Radians
		
		// Yaw: Earth Frame of Reference
		
		matrix_accum.x = rmat[4] ;
		matrix_accum.y = rmat[1] ;
		accum = rect_to_polar16(&matrix_accum) ;			// binary angle (0 to 65536 = 360 degrees)
		earth_yaw = ( - accum * BYTE_CIR_16_TO_RAD) ;			// Convert to Radians

		perSec = (float) streamRatePosition;
		// Beginning of frequency sensitive code
		earth_pitch_velocity = ( earth_pitch - previous_earth_pitch ) * perSec ; 
		earth_roll_velocity  = ( earth_roll  - previous_earth_roll  ) * perSec ;
		earth_yaw_velocity   = ( earth_yaw   - previous_earth_yaw   ) * perSec ;
		// End of frequency sensitive code

		previous_earth_pitch = earth_pitch ;
		previous_earth_roll  = earth_roll  ;
		previous_earth_yaw   = earth_yaw   ;

		mavlink_msg_attitude_send(MAVLINK_COMM_0,usec, earth_roll, earth_pitch, earth_yaw, 
				                  earth_roll_velocity, earth_pitch_velocity, earth_yaw_velocity ) ;
	}
	}

	// SYSTEM STATUS
	if ( !streamRateExtendedStatus )
		;
	else { spread_transmission_load = 18 / streamRateExtendedStatus ;
	if (mavlink_frequency_send( streamRateExtendedStatus, counter_40hz + spread_transmission_load)) 
	{
		if (flags._.GPS_steering == 0 && flags._.pitch_feedback == 0)
				 mode = MAV_MODE_MANUAL ;
		else if (flags._.GPS_steering == 0 && flags._.pitch_feedback == 1) 
				 mode = MAV_MODE_GUIDED ;
		else if (flags._.GPS_steering == 1 && flags._.pitch_feedback == 1 && udb_flags._.radio_on == 1)
				 mode = MAV_MODE_AUTO ;
		else if (flags._.GPS_steering == 1 && flags._.pitch_feedback == 1 && udb_flags._.radio_on == 0)
				 mode = MAV_MODE_TEST1 ; // Return to Landing (lost contact with transmitter)
		else
				 mode = MAV_MODE_TEST1 ; // Unknown state 

		mavlink_msg_sys_status_send(MAVLINK_COMM_0, mode, MAV_NAV_WAYPOINT, MAV_STATE_ACTIVE,
#if (BOARD_TYPE == ASPG_BOARD)
		    (uint16_t) cpu_timer,
#else
		    (uint16_t) (udb_cpu_load()) * 10,
#endif
			(uint16_t)  10000,  // Battery voltage in mV
			(uint16_t)  0,      // battery remaining
#if ( SERIAL_INPUT_FORMAT == SERIAL_MAVLINK )
			(uint16_t)  r_mavlink_status.packet_rx_drop_count) ;    // Not tested yet, may not be correct.
#else
			(uint16_t) 0 ) ; 
#endif
	}
	}

	// RC SERVO CHANNELS
	// Channel values shifted left by 1, to divide by two, so values reflect PWM pulses in microseconds.
	// mavlink_msg_rc_channels_raw_send(mavlink_channel_t chan, uint16_t chan1_raw, uint16_t chan2_raw,
	//    uint16_t chan3_raw, uint16_t chan4_raw, uint16_t chan5_raw, uint16_t chan6_raw, uint16_t chan7_raw,
	//    uint16_t chan8_raw, uint8_t rssi)
	if ( !streamRateRCChannels )
		;
	else { spread_transmission_load = 24 / streamRateRCChannels;
	if (mavlink_frequency_send( streamRateRCChannels, counter_40hz + spread_transmission_load)) 
	{
	 	mavlink_msg_servo_output_raw_send(MAVLINK_COMM_0,
#if (BOARD_TYPE == ASPG_BOARD)	// wanted to see these at full precision of 0.2uSec
			 (uint16_t) udb_pwOut[1]/5,  (uint16_t) udb_pwOut[2]/5, (uint16_t) udb_pwOut[3]/5, (uint16_t) udb_pwOut[4]/5,
			 (uint16_t) udb_pwOut[5]/5, (uint16_t) udb_pwOut[6]/5, (uint16_t) udb_pwOut[7]/5, (uint16_t) udb_pwOut[8]/5
#else
			 (uint16_t)(udb_pwOut[1]>>1),  (uint16_t) (udb_pwOut[2]>>1), (uint16_t) (udb_pwOut[3]>>1), (uint16_t) (udb_pwOut[4]>>1),
			 (uint16_t) (udb_pwOut[5]>>1), (uint16_t) (udb_pwOut[6]>>1), (uint16_t) (udb_pwOut[7]>>1), (uint16_t) (udb_pwOut[8]>>1)
#endif
			 );
	}
	}

	// RAW SENSORS - ACCELOREMETERS and GYROS
	// The values sent are raw with no offsets, scaling, and sign correction
	// It is expected that these values are graphed to allow users to check basic sensor operation,
	// and to graph noise on the signals.
	if ( !streamRateRawSensors )
		;
	else { spread_transmission_load = 30 / streamRateRawSensors;
	if (mavlink_frequency_send( streamRateRawSensors , counter_40hz + spread_transmission_load))
	{ 				
		extern int previousMagFieldRaw[] ;
		mavlink_msg_raw_imu_send(MAVLINK_COMM_0, usec,
					 (int16_t)   udb_yaccel.value,
					 (int16_t) - udb_xaccel.value,
					 (int16_t)   udb_zaccel.value, 
					 (int16_t)   ( udb_yrate.value ),
	                 (int16_t) - ( udb_xrate.value ),
	                 (int16_t)   ( udb_zrate.value ), 
#if ( MAG_YAW_DRIFT == 1 )
					  (int16_t) previousMagFieldRaw[0], (int16_t) previousMagFieldRaw[1], (int16_t) previousMagFieldRaw[2]) ;
#else
				      (int16_t) 0,(int16_t)  0,(int16_t)  0 ) ; // MagFieldRaw[] zero as mag not connected.
#endif
	}
	}

	// RC INPUT CHANNELS
	// Channel values shifted left by 1, to divide by two, so values reflect PWM pulses in microseconds.
	// mavlink_msg_rc_channels_raw_send(mavlink_channel_t chan, uint16_t chan1_raw, uint16_t chan2_raw,
	//    uint16_t chan3_raw, uint16_t chan4_raw, uint16_t chan5_raw, uint16_t chan6_raw, uint16_t chan7_raw,
	//    uint16_t chan8_raw, uint8_t rssi)
	if ( !streamRateExtra1 )
		;
	else { spread_transmission_load = 24 / streamRateExtra1;
	if (mavlink_frequency_send( streamRateExtra1, counter_40hz + spread_transmission_load)) 
	{
#if (BOARD_TYPE == ASPG_BOARD)	// want to see these at full precision, should be divide ~1.7
	 	mavlink_msg_rc_channels_scaled_send(MAVLINK_COMM_0,
			(int16_t) udb_pwIn[(RC_START-1)+1]/2, (int16_t) udb_pwIn[(RC_START-1)+2]/2,
			(int16_t) udb_pwIn[(RC_START-1)+3]/2, (int16_t) udb_pwIn[(RC_START-1)+4]/2,
			(int16_t) udb_pwIn[(RC_START-1)+5]/2, (int16_t) udb_pwIn[(RC_START-1)+6]/2, 
			(int16_t) udb_pwIn[(RC_START-1)+7]/2, (int16_t) udb_pwIn[(RC_START-1)+8]/2,
#else
	 	mavlink_msg_rc_channels_raw_send(MAVLINK_COMM_0,
			(uint16_t)(udb_pwIn[1]>>1), (uint16_t) (udb_pwIn[2]>>1), (uint16_t) (udb_pwIn[3]>>1), (uint16_t) (udb_pwIn[4]>>1),
			(uint16_t)(udb_pwIn[5]>>1), (uint16_t) (udb_pwIn[6]>>1), (uint16_t) (udb_pwIn[7]>>1), (uint16_t) (udb_pwIn[8]>>1),
#endif
			(uint8_t) 0 ); // no rssi on board
	}
	}

	// SCALED SENSORS - ACCELOREMETERS and GYROS
	// The values sent are raw with offsets, scaling, and sign correction
	if ( !streamRateExtra2 )
		;
	else { spread_transmission_load = 12 / streamRateExtra2;
	if (mavlink_frequency_send( streamRateExtra2, counter_40hz + spread_transmission_load)) 
	{ 				
		extern int MagFieldFilter[] ;
		mavlink_msg_scaled_imu_send(MAVLINK_COMM_0, usec,
					 (int16_t)   YACCEL_VALUE,
					 (int16_t) - XACCEL_VALUE,
					 (int16_t)   ZACCEL_VALUE, 
					 (int16_t)   ( YRATE_VALUE ),
	                 (int16_t) - ( XRATE_VALUE ),
	                 (int16_t)   ( ZRATE_VALUE ), 
#if ( MAG_YAW_DRIFT == 1 )
					  (int16_t) udb_magFieldBody[1], (int16_t) udb_magFieldBody[0], (int16_t) udb_magFieldBody[2]) ;
#else
				      (int16_t) 0,(int16_t)  0,(int16_t)  0 ) ; // MagFieldRaw[] zero as mag not connected.
#endif
	}
	}

#if ( SERIAL_INPUT_FORMAT == SERIAL_MAVLINK )
	// SEND VALUES OF PARAMETERS IF THE LIST HAS BEEN REQUESTED
	if 	( udb_flags._.mavlink_send_variables == 1 )
	{
		if ( send_variables_counter < count_of_parameters_list)
		{
//			mavlink_parameters_list[send_variables_counter].send_parm( send_variables_counter) ;
			mavlink_param( send_variables_counter, 0, 0.0 );
			send_variables_counter++ ;
		}
		else 
		{
			send_variables_counter = 0 ;
			udb_flags._.mavlink_send_variables = 0 ;
		}	
	}

	// SEND SPECIFICALLY REQUESTED PARAMETER
	if ( udb_flags._.mavlink_send_specific_variable == 1 )
	{
//		mavlink_parameters_list[send_by_index].send_parm( send_by_index ) ;
		mavlink_param( send_by_index, 0, 0.0 );
		udb_flags._.mavlink_send_specific_variable = 0 ;
	}	
					
#endif		
	return ;
}

#endif  // ( SERIAL_OUTPUT_FORMAT == SERIAL_MAVLINK )
//boolean mavlink_parameter_out_of_bounds( float parm, unsigned char i )
//{
//	if (( parm < mavlink_parameters_list[i].min ) || ( parm > mavlink_parameters_list[i].max ))
//    {
//		return  true ;
//	}
//	else { return false ; }
//}
//
//#if ( RECORD_FREE_STACK_SPACE ==  1)
//void mavlink_send_param_maxstack( unsigned char i )
//{
//	mavlink_msg_param_value_send( MAVLINK_COMM_0, mavlink_parameters_list[i].name , 
//		(float) ( 4096 - maxstack ) , count_of_parameters_list , 0 ) ;	
//	return ;
//} 
//
//void mavlink_set_maxstack( float setting , unsigned char i ) 
//{
//	//send_text((unsigned char*)"Setting maxstack \r\n");
//	if (( mavlink_parameters_list[i].readonly == true ) ||
//			 ( mavlink_parameter_out_of_bounds( setting , i ) == true )) return ;
//	maxstack = (int)( 4096 - setting ) ;
//	return ;
//}
//
//#endif
//
//void mavlink_send_param_rollkp( unsigned char i )
//{
//	mavlink_msg_param_value_send( MAVLINK_COMM_0, mavlink_parameters_list[i].name ,
//		(float) (rollkp / 16384.0 ), count_of_parameters_list, 0 ) ; // 16384.0 is RMAX defined as a float.	
//	return ;
//} 
//
//void mavlink_set_rollkp(float setting,  unsigned char i ) 
//{
//	//send_text((unsigned char*)"Setting rollkp \r\n");
//	if (( mavlink_parameters_list[i].readonly == true ) || 
//			( mavlink_parameter_out_of_bounds( setting, i ) == true )) return ;							
//	rollkp = (int) ( setting * 16384.0 ) ;
//	return ;
//}
//
//void mavlink_send_param_rollkd( unsigned char i ) 
//{
//	mavlink_msg_param_value_send( MAVLINK_COMM_0, mavlink_parameters_list[i].name ,
//		(float) (rollkd / ( SCALEGYRO * 16384.0 )) , count_of_parameters_list, 0 ) ; // 16384.0 is RMAX defined as a float.	
//	return ;
//}
//
//void mavlink_set_rollkd(float setting,  unsigned char i)
//{
//	if (( mavlink_parameters_list[i].readonly == true ) || 
//			( mavlink_parameter_out_of_bounds( setting, i ) == true )) return ;							
//	rollkd = (int) ( setting * ( SCALEGYRO * 16384.0 ) ) ;
//	return ;
//}
//
//void mavlink_send_param_yawkpail( unsigned char i )
//{
//	mavlink_msg_param_value_send( MAVLINK_COMM_0, mavlink_parameters_list[i].name ,
//		(float) (yawkpail / 16384.0 ), count_of_parameters_list, 0 ) ; // 16384.0 is RMAX defined as a float.	
//	return ;
//} 
//
//void mavlink_set_yawkpail(float setting,  unsigned char i ) 
//{
//	if (( mavlink_parameters_list[i].readonly == true ) || 
//			( mavlink_parameter_out_of_bounds( setting, i ) == true )) return ;							
//	yawkpail = (int) ( setting * 16384.0 ) ;
//	return ;
//}
//
//void mavlink_send_param_yawkdail( unsigned char i ) 
//{
//	mavlink_msg_param_value_send( MAVLINK_COMM_0, mavlink_parameters_list[i].name ,
//		(float) (yawkdail / ( SCALEGYRO * 16384.0 )) , count_of_parameters_list, 0 ) ; // 16384.0 is RMAX defined as a float.	
//	return ;
//}
//
//void mavlink_set_yawkdail(float setting,  unsigned char i)
//{
//	if (( mavlink_parameters_list[i].readonly == true ) || 
//			( mavlink_parameter_out_of_bounds( setting, i ) == true )) return ;							
//	yawkdail = (int) ( setting * ( SCALEGYRO * 16384.0 ) ) ;
//	return ;
//}
//
/*
void uart1_send(uint8_t buf[], uint16_t len)
// len is the number of bytes in the buffer
{
	int start_index = end_index ;
	int remaining = SERIAL_BUFFER_SIZE - start_index ;
	if ( len > remaining ) 	len = remaining ;
	if (remaining > 1)
	{
		memcpy(&serial_buffer[start_index], buf, len);
		end_index = start_index + len ;
	}	
	if (sb_index == 0)
	{
		udb_serial_start_sending();
	}
	return ;
}

void uart1_transmit(uint8_t ch) 
// routine to send a single character used by MAVlink standard include routines.
// We forward to multi-byte sending routine so that firmware can interleave
// ascii debug messages with MAVLink binary messages without them overwriting each other.
{
	uart1_send(&ch, 1);
}

void send_text(uint8_t text[])
{
	uint16_t index = 0;
	while ( text[index++] != 0 && index < 80)
	{
		; // Do nothing, just putting length of text in index.
	}
	uart1_send(text, index - 1) ;
}
*/
//#if ( RECORD_FREE_STACK_SPACE ==  1)
//void mavlink_send_param_maxstack( unsigned char i ) ;
//void mavlink_set_maxstack(float setting, unsigned char i ) ;
//#endif
//void mavlink_send_param_rollkp( unsigned char i ) ;
//void mavlink_set_rollkp( float setting, unsigned char i) ;
//void mavlink_send_param_rollkd( unsigned char i ) ;
//void mavlink_set_rollkd(float setting,  unsigned char i)  ;
//void mavlink_send_param_yawkpail( unsigned char i ) ;
//void mavlink_set_yawkpail(float setting, unsigned char i ) ;
//void mavlink_send_param_yawkdail( unsigned char i ) ;
//void mavlink_set_yawkdail(float setting, unsigned char i ) ;
//
//boolean mavlink_parameter_out_of_bounds( float parm, unsigned char i ) ;
//
