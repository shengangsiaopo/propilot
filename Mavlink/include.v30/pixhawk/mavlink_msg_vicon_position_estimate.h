// MESSAGE VICON_POSITION_ESTIMATE PACKING

#define MAVLINK_MSG_ID_VICON_POSITION_ESTIMATE 112

typedef struct __mavlink_vicon_position_estimate_t 
{
	uint64_t usec; ///< Timestamp (milliseconds)
	float x; ///< Global X position
	float y; ///< Global Y position
	float z; ///< Global Z position
	float roll; ///< Roll angle in rad
	float pitch; ///< Pitch angle in rad
	float yaw; ///< Yaw angle in rad

} mavlink_vicon_position_estimate_t;



/**
 * @brief Pack a vicon_position_estimate message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param usec Timestamp (milliseconds)
 * @param x Global X position
 * @param y Global Y position
 * @param z Global Z position
 * @param roll Roll angle in rad
 * @param pitch Pitch angle in rad
 * @param yaw Yaw angle in rad
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_vicon_position_estimate_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, uint64_t usec, float x, float y, float z, float roll, float pitch, float yaw)
{
	mavlink_vicon_position_estimate_t *p = (mavlink_vicon_position_estimate_t *)&msg->payload[0];
	msg->msgid = MAVLINK_MSG_ID_VICON_POSITION_ESTIMATE;

	p->usec = usec; // uint64_t:Timestamp (milliseconds)
	p->x = x; // float:Global X position
	p->y = y; // float:Global Y position
	p->z = z; // float:Global Z position
	p->roll = roll; // float:Roll angle in rad
	p->pitch = pitch; // float:Pitch angle in rad
	p->yaw = yaw; // float:Yaw angle in rad

	return mavlink_finalize_message(msg, system_id, component_id, sizeof(mavlink_vicon_position_estimate_t));
}

/**
 * @brief Pack a vicon_position_estimate message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message was sent over
 * @param msg The MAVLink message to compress the data into
 * @param usec Timestamp (milliseconds)
 * @param x Global X position
 * @param y Global Y position
 * @param z Global Z position
 * @param roll Roll angle in rad
 * @param pitch Pitch angle in rad
 * @param yaw Yaw angle in rad
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_vicon_position_estimate_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, uint64_t usec, float x, float y, float z, float roll, float pitch, float yaw)
{
	mavlink_vicon_position_estimate_t *p = (mavlink_vicon_position_estimate_t *)&msg->payload[0];
	msg->msgid = MAVLINK_MSG_ID_VICON_POSITION_ESTIMATE;

	p->usec = usec; // uint64_t:Timestamp (milliseconds)
	p->x = x; // float:Global X position
	p->y = y; // float:Global Y position
	p->z = z; // float:Global Z position
	p->roll = roll; // float:Roll angle in rad
	p->pitch = pitch; // float:Pitch angle in rad
	p->yaw = yaw; // float:Yaw angle in rad

	return mavlink_finalize_message_chan(msg, system_id, component_id, chan, sizeof(mavlink_vicon_position_estimate_t));
}

/**
 * @brief Encode a vicon_position_estimate struct into a message
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param vicon_position_estimate C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_vicon_position_estimate_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_vicon_position_estimate_t* vicon_position_estimate)
{
	return mavlink_msg_vicon_position_estimate_pack(system_id, component_id, msg, vicon_position_estimate->usec, vicon_position_estimate->x, vicon_position_estimate->y, vicon_position_estimate->z, vicon_position_estimate->roll, vicon_position_estimate->pitch, vicon_position_estimate->yaw);
}

/**
 * @brief Send a vicon_position_estimate message
 * @param chan MAVLink channel to send the message
 *
 * @param usec Timestamp (milliseconds)
 * @param x Global X position
 * @param y Global Y position
 * @param z Global Z position
 * @param roll Roll angle in rad
 * @param pitch Pitch angle in rad
 * @param yaw Yaw angle in rad
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_vicon_position_estimate_send(mavlink_channel_t chan, uint64_t usec, float x, float y, float z, float roll, float pitch, float yaw)
{
	mavlink_message_t msg;
	uint16_t checksum;
	mavlink_vicon_position_estimate_t *p = (mavlink_vicon_position_estimate_t *)&msg.payload[0];

	msg.msgid = MAVLINK_MSG_ID_VICON_POSITION_ESTIMATE;
	msg.len = sizeof(mavlink_vicon_position_estimate_t);
	p->usec = usec; // uint64_t:Timestamp (milliseconds)
	p->x = x; // float:Global X position
	p->y = y; // float:Global Y position
	p->z = z; // float:Global Z position
	p->roll = roll; // float:Roll angle in rad
	p->pitch = pitch; // float:Pitch angle in rad
	p->yaw = yaw; // float:Yaw angle in rad

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
// MESSAGE VICON_POSITION_ESTIMATE UNPACKING

/**
 * @brief Get field usec from vicon_position_estimate message
 *
 * @return Timestamp (milliseconds)
 */
static inline uint64_t mavlink_msg_vicon_position_estimate_get_usec(const mavlink_message_t* msg)
{
	mavlink_vicon_position_estimate_t *p = (mavlink_vicon_position_estimate_t *)&msg->payload[0];
	return (uint64_t)(p->usec);
}

/**
 * @brief Get field x from vicon_position_estimate message
 *
 * @return Global X position
 */
static inline float mavlink_msg_vicon_position_estimate_get_x(const mavlink_message_t* msg)
{
	mavlink_vicon_position_estimate_t *p = (mavlink_vicon_position_estimate_t *)&msg->payload[0];
	return (float)(p->x);
}

/**
 * @brief Get field y from vicon_position_estimate message
 *
 * @return Global Y position
 */
static inline float mavlink_msg_vicon_position_estimate_get_y(const mavlink_message_t* msg)
{
	mavlink_vicon_position_estimate_t *p = (mavlink_vicon_position_estimate_t *)&msg->payload[0];
	return (float)(p->y);
}

/**
 * @brief Get field z from vicon_position_estimate message
 *
 * @return Global Z position
 */
static inline float mavlink_msg_vicon_position_estimate_get_z(const mavlink_message_t* msg)
{
	mavlink_vicon_position_estimate_t *p = (mavlink_vicon_position_estimate_t *)&msg->payload[0];
	return (float)(p->z);
}

/**
 * @brief Get field roll from vicon_position_estimate message
 *
 * @return Roll angle in rad
 */
static inline float mavlink_msg_vicon_position_estimate_get_roll(const mavlink_message_t* msg)
{
	mavlink_vicon_position_estimate_t *p = (mavlink_vicon_position_estimate_t *)&msg->payload[0];
	return (float)(p->roll);
}

/**
 * @brief Get field pitch from vicon_position_estimate message
 *
 * @return Pitch angle in rad
 */
static inline float mavlink_msg_vicon_position_estimate_get_pitch(const mavlink_message_t* msg)
{
	mavlink_vicon_position_estimate_t *p = (mavlink_vicon_position_estimate_t *)&msg->payload[0];
	return (float)(p->pitch);
}

/**
 * @brief Get field yaw from vicon_position_estimate message
 *
 * @return Yaw angle in rad
 */
static inline float mavlink_msg_vicon_position_estimate_get_yaw(const mavlink_message_t* msg)
{
	mavlink_vicon_position_estimate_t *p = (mavlink_vicon_position_estimate_t *)&msg->payload[0];
	return (float)(p->yaw);
}

/**
 * @brief Decode a vicon_position_estimate message into a struct
 *
 * @param msg The message to decode
 * @param vicon_position_estimate C-struct to decode the message contents into
 */
static inline void mavlink_msg_vicon_position_estimate_decode(const mavlink_message_t* msg, mavlink_vicon_position_estimate_t* vicon_position_estimate)
{
	memcpy( vicon_position_estimate, msg->payload, sizeof(mavlink_vicon_position_estimate_t));
}
