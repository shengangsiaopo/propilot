// MESSAGE DEBUG PACKING

#define MAVLINK_MSG_ID_DEBUG 255

typedef struct __mavlink_debug_t 
{
	uint8_t ind; ///< index of debug variable
	float value; ///< DEBUG value

} mavlink_debug_t;



/**
 * @brief Pack a debug message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param ind index of debug variable
 * @param value DEBUG value
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_debug_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, uint8_t ind, float value)
{
	mavlink_debug_t *p = (mavlink_debug_t *)&msg->payload[0];
	msg->msgid = MAVLINK_MSG_ID_DEBUG;

	p->ind = ind; // uint8_t:index of debug variable
	p->value = value; // float:DEBUG value

	return mavlink_finalize_message(msg, system_id, component_id, sizeof(mavlink_debug_t));
}

/**
 * @brief Pack a debug message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message was sent over
 * @param msg The MAVLink message to compress the data into
 * @param ind index of debug variable
 * @param value DEBUG value
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_debug_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, uint8_t ind, float value)
{
	mavlink_debug_t *p = (mavlink_debug_t *)&msg->payload[0];
	msg->msgid = MAVLINK_MSG_ID_DEBUG;

	p->ind = ind; // uint8_t:index of debug variable
	p->value = value; // float:DEBUG value

	return mavlink_finalize_message_chan(msg, system_id, component_id, chan, sizeof(mavlink_debug_t));
}

/**
 * @brief Encode a debug struct into a message
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param debug C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_debug_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_debug_t* debug)
{
	return mavlink_msg_debug_pack(system_id, component_id, msg, debug->ind, debug->value);
}

/**
 * @brief Send a debug message
 * @param chan MAVLink channel to send the message
 *
 * @param ind index of debug variable
 * @param value DEBUG value
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_debug_send(mavlink_channel_t chan, uint8_t ind, float value)
{
	mavlink_message_t msg;
	uint16_t checksum;
	mavlink_debug_t *p = (mavlink_debug_t *)&msg.payload[0];

	msg.msgid = MAVLINK_MSG_ID_DEBUG;
	msg.len = sizeof(mavlink_debug_t);
	p->ind = ind; // uint8_t:index of debug variable
	p->value = value; // float:DEBUG value

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
// MESSAGE DEBUG UNPACKING

/**
 * @brief Get field ind from debug message
 *
 * @return index of debug variable
 */
static inline uint8_t mavlink_msg_debug_get_ind(const mavlink_message_t* msg)
{
	mavlink_debug_t *p = (mavlink_debug_t *)&msg->payload[0];
	return (uint8_t)(p->ind);
}

/**
 * @brief Get field value from debug message
 *
 * @return DEBUG value
 */
static inline float mavlink_msg_debug_get_value(const mavlink_message_t* msg)
{
	mavlink_debug_t *p = (mavlink_debug_t *)&msg->payload[0];
	return (float)(p->value);
}

/**
 * @brief Decode a debug message into a struct
 *
 * @param msg The message to decode
 * @param debug C-struct to decode the message contents into
 */
static inline void mavlink_msg_debug_decode(const mavlink_message_t* msg, mavlink_debug_t* debug)
{
	memcpy( debug, msg->payload, sizeof(mavlink_debug_t));
}
