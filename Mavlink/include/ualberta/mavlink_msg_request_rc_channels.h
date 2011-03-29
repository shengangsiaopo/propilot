// MESSAGE REQUEST_RC_CHANNELS PACKING

#define MAVLINK_MSG_ID_REQUEST_RC_CHANNELS 221
#define MAVLINK_MSG_221_LEN 1

typedef struct __mavlink_request_rc_channels_t 
{
	uint8_t enabled; ///< True: start sending data; False: stop sending data
} mavlink_request_rc_channels_t;

//#if sizeof(mavlink_request_rc_channels_t) != 1 // sadly this fails 
//#warning struct and size do not match
//#endif


/**
 * @brief Pack a request_rc_channels message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param enabled True: start sending data; False: stop sending data
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_request_rc_channels_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, uint8_t enabled)
{
	mavlink_request_rc_channels_t *p = (mavlink_request_rc_channels_t *)&msg->payload[0];
	msg->msgid = MAVLINK_MSG_ID_REQUEST_RC_CHANNELS;

	p->enabled = enabled; // uint8_t:True: start sending data; False: stop sending data

	return mavlink_finalize_message(msg, system_id, component_id, sizeof(mavlink_request_rc_channels_t));
}

/**
 * @brief Pack a request_rc_channels message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message was sent over
 * @param msg The MAVLink message to compress the data into
 * @param enabled True: start sending data; False: stop sending data
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_request_rc_channels_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, uint8_t enabled)
{
	mavlink_request_rc_channels_t *p = (mavlink_request_rc_channels_t *)&msg->payload[0];
	msg->msgid = MAVLINK_MSG_ID_REQUEST_RC_CHANNELS;

	p->enabled = enabled; // uint8_t:True: start sending data; False: stop sending data

	return mavlink_finalize_message_chan(msg, system_id, component_id, chan, sizeof(mavlink_request_rc_channels_t));
}

/**
 * @brief Encode a request_rc_channels struct into a message
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param request_rc_channels C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_request_rc_channels_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_request_rc_channels_t* request_rc_channels)
{
	return mavlink_msg_request_rc_channels_pack(system_id, component_id, msg, request_rc_channels->enabled);
}

/**
 * @brief Send a request_rc_channels message
 * @param chan MAVLink channel to send the message
 *
 * @param enabled True: start sending data; False: stop sending data
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_request_rc_channels_send(mavlink_channel_t chan, uint8_t enabled)
{
	mavlink_message_t msg;
	uint16_t checksum;
	mavlink_request_rc_channels_t *p = (mavlink_request_rc_channels_t *)&msg.payload[0];

	msg.msgid = MAVLINK_MSG_ID_REQUEST_RC_CHANNELS;
	msg.len = sizeof(mavlink_request_rc_channels_t);
	p->enabled = enabled; // uint8_t:True: start sending data; False: stop sending data

	msg.sysid = mavlink_system.sysid;
	msg.compid = mavlink_system.compid;
	msg.seq = mavlink_get_channel_status(chan)->current_tx_seq;
	mavlink_get_channel_status(chan)->current_tx_seq = mavlink_get_channel_status(chan)->current_tx_seq+1;
	checksum = crc_calculate_msg(&msg, msg.len + MAVLINK_CORE_HEADER_LEN);
	msg.ck_a = (uint8_t)(checksum & 0xFF); ///< High byte
	msg.ck_b = (uint8_t)(checksum >> 8); ///< Low byte

	mavlink_send_uart(chan, &msg);
}

#endif
// MESSAGE REQUEST_RC_CHANNELS UNPACKING

/**
 * @brief Get field enabled from request_rc_channels message
 *
 * @return True: start sending data; False: stop sending data
 */
static inline uint8_t mavlink_msg_request_rc_channels_get_enabled(const mavlink_message_t* msg)
{
	mavlink_request_rc_channels_t *p = (mavlink_request_rc_channels_t *)&msg->payload[0];
	return (uint8_t)(p->enabled);
}

/**
 * @brief Decode a request_rc_channels message into a struct
 *
 * @param msg The message to decode
 * @param request_rc_channels C-struct to decode the message contents into
 */
static inline void mavlink_msg_request_rc_channels_decode(const mavlink_message_t* msg, mavlink_request_rc_channels_t* request_rc_channels)
{
	memcpy( request_rc_channels, msg->payload, sizeof(mavlink_request_rc_channels_t));
}
