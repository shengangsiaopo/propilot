// MESSAGE WAYPOINT_REQUEST PACKING

#define MAVLINK_MSG_ID_WAYPOINT_REQUEST 40

typedef struct __mavlink_waypoint_request_t 
{
	uint8_t target_system; ///< System ID
	uint8_t target_component; ///< Component ID
	uint16_t seq; ///< Sequence

} mavlink_waypoint_request_t;



/**
 * @brief Pack a waypoint_request message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param target_system System ID
 * @param target_component Component ID
 * @param seq Sequence
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_waypoint_request_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, uint8_t target_system, uint8_t target_component, uint16_t seq)
{
	mavlink_waypoint_request_t *p = (mavlink_waypoint_request_t *)&msg->payload[0];
	msg->msgid = MAVLINK_MSG_ID_WAYPOINT_REQUEST;

	p->target_system = target_system; // uint8_t:System ID
	p->target_component = target_component; // uint8_t:Component ID
	p->seq = seq; // uint16_t:Sequence

	return mavlink_finalize_message(msg, system_id, component_id, sizeof(mavlink_waypoint_request_t));
}

/**
 * @brief Pack a waypoint_request message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message was sent over
 * @param msg The MAVLink message to compress the data into
 * @param target_system System ID
 * @param target_component Component ID
 * @param seq Sequence
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_waypoint_request_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, uint8_t target_system, uint8_t target_component, uint16_t seq)
{
	mavlink_waypoint_request_t *p = (mavlink_waypoint_request_t *)&msg->payload[0];
	msg->msgid = MAVLINK_MSG_ID_WAYPOINT_REQUEST;

	p->target_system = target_system; // uint8_t:System ID
	p->target_component = target_component; // uint8_t:Component ID
	p->seq = seq; // uint16_t:Sequence

	return mavlink_finalize_message_chan(msg, system_id, component_id, chan, sizeof(mavlink_waypoint_request_t));
}

/**
 * @brief Encode a waypoint_request struct into a message
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param waypoint_request C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_waypoint_request_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_waypoint_request_t* waypoint_request)
{
	return mavlink_msg_waypoint_request_pack(system_id, component_id, msg, waypoint_request->target_system, waypoint_request->target_component, waypoint_request->seq);
}

/**
 * @brief Send a waypoint_request message
 * @param chan MAVLink channel to send the message
 *
 * @param target_system System ID
 * @param target_component Component ID
 * @param seq Sequence
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_waypoint_request_send(mavlink_channel_t chan, uint8_t target_system, uint8_t target_component, uint16_t seq)
{
	mavlink_message_t msg;
	uint16_t checksum;
	mavlink_waypoint_request_t *p = (mavlink_waypoint_request_t *)&msg.payload[0];

	msg.msgid = MAVLINK_MSG_ID_WAYPOINT_REQUEST;
	msg.len = sizeof(mavlink_waypoint_request_t);
	p->target_system = target_system; // uint8_t:System ID
	p->target_component = target_component; // uint8_t:Component ID
	p->seq = seq; // uint16_t:Sequence

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
// MESSAGE WAYPOINT_REQUEST UNPACKING

/**
 * @brief Get field target_system from waypoint_request message
 *
 * @return System ID
 */
static inline uint8_t mavlink_msg_waypoint_request_get_target_system(const mavlink_message_t* msg)
{
	mavlink_waypoint_request_t *p = (mavlink_waypoint_request_t *)&msg->payload[0];
	return (uint8_t)(p->target_system);
}

/**
 * @brief Get field target_component from waypoint_request message
 *
 * @return Component ID
 */
static inline uint8_t mavlink_msg_waypoint_request_get_target_component(const mavlink_message_t* msg)
{
	mavlink_waypoint_request_t *p = (mavlink_waypoint_request_t *)&msg->payload[0];
	return (uint8_t)(p->target_component);
}

/**
 * @brief Get field seq from waypoint_request message
 *
 * @return Sequence
 */
static inline uint16_t mavlink_msg_waypoint_request_get_seq(const mavlink_message_t* msg)
{
	mavlink_waypoint_request_t *p = (mavlink_waypoint_request_t *)&msg->payload[0];
	return (uint16_t)(p->seq);
}

/**
 * @brief Decode a waypoint_request message into a struct
 *
 * @param msg The message to decode
 * @param waypoint_request C-struct to decode the message contents into
 */
static inline void mavlink_msg_waypoint_request_decode(const mavlink_message_t* msg, mavlink_waypoint_request_t* waypoint_request)
{
	memcpy( waypoint_request, msg->payload, sizeof(mavlink_waypoint_request_t));
}
