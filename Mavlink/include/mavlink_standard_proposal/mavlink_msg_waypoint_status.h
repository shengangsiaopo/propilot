// MESSAGE WAYPOINT_STATUS PACKING

#define MAVLINK_MSG_ID_WAYPOINT_STATUS 38
#define MAVLINK_MSG_38_LEN 3

typedef struct __mavlink_waypoint_status_t 
{
	uint16_t wp_id; ///< Waypoint ID
	uint8_t wp_status; ///< Waypoint status: 0: Ok, 1: Reached, 2: Orbit time expired, 254: Error
} mavlink_waypoint_status_t;

//#if sizeof(mavlink_waypoint_status_t) != 3 // sadly this fails 
//#warning struct and size do not match
//#endif


/**
 * @brief Pack a waypoint_status message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param wp_id Waypoint ID
 * @param wp_status Waypoint status: 0: Ok, 1: Reached, 2: Orbit time expired, 254: Error
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_waypoint_status_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, uint16_t wp_id, uint8_t wp_status)
{
	mavlink_waypoint_status_t *p = (mavlink_waypoint_status_t *)&msg->payload[0];
	msg->msgid = MAVLINK_MSG_ID_WAYPOINT_STATUS;

	p->wp_id = wp_id; // uint16_t:Waypoint ID
	p->wp_status = wp_status; // uint8_t:Waypoint status: 0: Ok, 1: Reached, 2: Orbit time expired, 254: Error

	return mavlink_finalize_message(msg, system_id, component_id, sizeof(mavlink_waypoint_status_t));
}

/**
 * @brief Pack a waypoint_status message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message was sent over
 * @param msg The MAVLink message to compress the data into
 * @param wp_id Waypoint ID
 * @param wp_status Waypoint status: 0: Ok, 1: Reached, 2: Orbit time expired, 254: Error
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_waypoint_status_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, uint16_t wp_id, uint8_t wp_status)
{
	mavlink_waypoint_status_t *p = (mavlink_waypoint_status_t *)&msg->payload[0];
	msg->msgid = MAVLINK_MSG_ID_WAYPOINT_STATUS;

	p->wp_id = wp_id; // uint16_t:Waypoint ID
	p->wp_status = wp_status; // uint8_t:Waypoint status: 0: Ok, 1: Reached, 2: Orbit time expired, 254: Error

	return mavlink_finalize_message_chan(msg, system_id, component_id, chan, sizeof(mavlink_waypoint_status_t));
}

/**
 * @brief Encode a waypoint_status struct into a message
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param waypoint_status C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_waypoint_status_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_waypoint_status_t* waypoint_status)
{
	return mavlink_msg_waypoint_status_pack(system_id, component_id, msg, waypoint_status->wp_id, waypoint_status->wp_status);
}

/**
 * @brief Send a waypoint_status message
 * @param chan MAVLink channel to send the message
 *
 * @param wp_id Waypoint ID
 * @param wp_status Waypoint status: 0: Ok, 1: Reached, 2: Orbit time expired, 254: Error
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_waypoint_status_send(mavlink_channel_t chan, uint16_t wp_id, uint8_t wp_status)
{
	mavlink_message_t msg;
	uint16_t checksum;
	mavlink_waypoint_status_t *p = (mavlink_waypoint_status_t *)&msg.payload[0];

	msg.msgid = MAVLINK_MSG_ID_WAYPOINT_STATUS;
	msg.len = sizeof(mavlink_waypoint_status_t);
	p->wp_id = wp_id; // uint16_t:Waypoint ID
	p->wp_status = wp_status; // uint8_t:Waypoint status: 0: Ok, 1: Reached, 2: Orbit time expired, 254: Error

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
// MESSAGE WAYPOINT_STATUS UNPACKING

/**
 * @brief Get field wp_id from waypoint_status message
 *
 * @return Waypoint ID
 */
static inline uint16_t mavlink_msg_waypoint_status_get_wp_id(const mavlink_message_t* msg)
{
	mavlink_waypoint_status_t *p = (mavlink_waypoint_status_t *)&msg->payload[0];
	return (uint16_t)(p->wp_id);
}

/**
 * @brief Get field wp_status from waypoint_status message
 *
 * @return Waypoint status: 0: Ok, 1: Reached, 2: Orbit time expired, 254: Error
 */
static inline uint8_t mavlink_msg_waypoint_status_get_wp_status(const mavlink_message_t* msg)
{
	mavlink_waypoint_status_t *p = (mavlink_waypoint_status_t *)&msg->payload[0];
	return (uint8_t)(p->wp_status);
}

/**
 * @brief Decode a waypoint_status message into a struct
 *
 * @param msg The message to decode
 * @param waypoint_status C-struct to decode the message contents into
 */
static inline void mavlink_msg_waypoint_status_decode(const mavlink_message_t* msg, mavlink_waypoint_status_t* waypoint_status)
{
	memcpy( waypoint_status, msg->payload, sizeof(mavlink_waypoint_status_t));
}
