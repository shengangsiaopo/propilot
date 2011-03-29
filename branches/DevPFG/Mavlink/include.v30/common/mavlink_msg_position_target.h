// MESSAGE POSITION_TARGET PACKING

#define MAVLINK_MSG_ID_POSITION_TARGET 63

typedef struct __mavlink_position_target_t 
{
	float x; ///< x position
	float y; ///< y position
	float z; ///< z position
	float yaw; ///< yaw orientation in radians, 0 = NORTH

} mavlink_position_target_t;



/**
 * @brief Pack a position_target message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param x x position
 * @param y y position
 * @param z z position
 * @param yaw yaw orientation in radians, 0 = NORTH
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_position_target_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, float x, float y, float z, float yaw)
{
	mavlink_position_target_t *p = (mavlink_position_target_t *)&msg->payload[0];
	msg->msgid = MAVLINK_MSG_ID_POSITION_TARGET;

	p->x = x; // float:x position
	p->y = y; // float:y position
	p->z = z; // float:z position
	p->yaw = yaw; // float:yaw orientation in radians, 0 = NORTH

	return mavlink_finalize_message(msg, system_id, component_id, sizeof(mavlink_position_target_t));
}

/**
 * @brief Pack a position_target message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message was sent over
 * @param msg The MAVLink message to compress the data into
 * @param x x position
 * @param y y position
 * @param z z position
 * @param yaw yaw orientation in radians, 0 = NORTH
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_position_target_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, float x, float y, float z, float yaw)
{
	mavlink_position_target_t *p = (mavlink_position_target_t *)&msg->payload[0];
	msg->msgid = MAVLINK_MSG_ID_POSITION_TARGET;

	p->x = x; // float:x position
	p->y = y; // float:y position
	p->z = z; // float:z position
	p->yaw = yaw; // float:yaw orientation in radians, 0 = NORTH

	return mavlink_finalize_message_chan(msg, system_id, component_id, chan, sizeof(mavlink_position_target_t));
}

/**
 * @brief Encode a position_target struct into a message
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param position_target C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_position_target_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_position_target_t* position_target)
{
	return mavlink_msg_position_target_pack(system_id, component_id, msg, position_target->x, position_target->y, position_target->z, position_target->yaw);
}

/**
 * @brief Send a position_target message
 * @param chan MAVLink channel to send the message
 *
 * @param x x position
 * @param y y position
 * @param z z position
 * @param yaw yaw orientation in radians, 0 = NORTH
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_position_target_send(mavlink_channel_t chan, float x, float y, float z, float yaw)
{
	mavlink_message_t msg;
	uint16_t checksum;
	mavlink_position_target_t *p = (mavlink_position_target_t *)&msg.payload[0];

	msg.msgid = MAVLINK_MSG_ID_POSITION_TARGET;
	msg.len = sizeof(mavlink_position_target_t);
	p->x = x; // float:x position
	p->y = y; // float:y position
	p->z = z; // float:z position
	p->yaw = yaw; // float:yaw orientation in radians, 0 = NORTH

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
// MESSAGE POSITION_TARGET UNPACKING

/**
 * @brief Get field x from position_target message
 *
 * @return x position
 */
static inline float mavlink_msg_position_target_get_x(const mavlink_message_t* msg)
{
	mavlink_position_target_t *p = (mavlink_position_target_t *)&msg->payload[0];
	return (float)(p->x);
}

/**
 * @brief Get field y from position_target message
 *
 * @return y position
 */
static inline float mavlink_msg_position_target_get_y(const mavlink_message_t* msg)
{
	mavlink_position_target_t *p = (mavlink_position_target_t *)&msg->payload[0];
	return (float)(p->y);
}

/**
 * @brief Get field z from position_target message
 *
 * @return z position
 */
static inline float mavlink_msg_position_target_get_z(const mavlink_message_t* msg)
{
	mavlink_position_target_t *p = (mavlink_position_target_t *)&msg->payload[0];
	return (float)(p->z);
}

/**
 * @brief Get field yaw from position_target message
 *
 * @return yaw orientation in radians, 0 = NORTH
 */
static inline float mavlink_msg_position_target_get_yaw(const mavlink_message_t* msg)
{
	mavlink_position_target_t *p = (mavlink_position_target_t *)&msg->payload[0];
	return (float)(p->yaw);
}

/**
 * @brief Decode a position_target message into a struct
 *
 * @param msg The message to decode
 * @param position_target C-struct to decode the message contents into
 */
static inline void mavlink_msg_position_target_decode(const mavlink_message_t* msg, mavlink_position_target_t* position_target)
{
	memcpy( position_target, msg->payload, sizeof(mavlink_position_target_t));
}
