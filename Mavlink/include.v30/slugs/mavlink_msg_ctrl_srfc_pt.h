// MESSAGE CTRL_SRFC_PT PACKING

#define MAVLINK_MSG_ID_CTRL_SRFC_PT 181

typedef struct __mavlink_ctrl_srfc_pt_t 
{
	uint8_t target; ///< The system setting the commands
	uint16_t bitfieldPt; ///< Bitfield containing the PT configuration

} mavlink_ctrl_srfc_pt_t;



/**
 * @brief Pack a ctrl_srfc_pt message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param target The system setting the commands
 * @param bitfieldPt Bitfield containing the PT configuration
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_ctrl_srfc_pt_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, uint8_t target, uint16_t bitfieldPt)
{
	mavlink_ctrl_srfc_pt_t *p = (mavlink_ctrl_srfc_pt_t *)&msg->payload[0];
	msg->msgid = MAVLINK_MSG_ID_CTRL_SRFC_PT;

	p->target = target; // uint8_t:The system setting the commands
	p->bitfieldPt = bitfieldPt; // uint16_t:Bitfield containing the PT configuration

	return mavlink_finalize_message(msg, system_id, component_id, sizeof(mavlink_ctrl_srfc_pt_t));
}

/**
 * @brief Pack a ctrl_srfc_pt message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message was sent over
 * @param msg The MAVLink message to compress the data into
 * @param target The system setting the commands
 * @param bitfieldPt Bitfield containing the PT configuration
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_ctrl_srfc_pt_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, uint8_t target, uint16_t bitfieldPt)
{
	mavlink_ctrl_srfc_pt_t *p = (mavlink_ctrl_srfc_pt_t *)&msg->payload[0];
	msg->msgid = MAVLINK_MSG_ID_CTRL_SRFC_PT;

	p->target = target; // uint8_t:The system setting the commands
	p->bitfieldPt = bitfieldPt; // uint16_t:Bitfield containing the PT configuration

	return mavlink_finalize_message_chan(msg, system_id, component_id, chan, sizeof(mavlink_ctrl_srfc_pt_t));
}

/**
 * @brief Encode a ctrl_srfc_pt struct into a message
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param ctrl_srfc_pt C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_ctrl_srfc_pt_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_ctrl_srfc_pt_t* ctrl_srfc_pt)
{
	return mavlink_msg_ctrl_srfc_pt_pack(system_id, component_id, msg, ctrl_srfc_pt->target, ctrl_srfc_pt->bitfieldPt);
}

/**
 * @brief Send a ctrl_srfc_pt message
 * @param chan MAVLink channel to send the message
 *
 * @param target The system setting the commands
 * @param bitfieldPt Bitfield containing the PT configuration
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_ctrl_srfc_pt_send(mavlink_channel_t chan, uint8_t target, uint16_t bitfieldPt)
{
	mavlink_message_t msg;
	uint16_t checksum;
	mavlink_ctrl_srfc_pt_t *p = (mavlink_ctrl_srfc_pt_t *)&msg.payload[0];

	msg.msgid = MAVLINK_MSG_ID_CTRL_SRFC_PT;
	msg.len = sizeof(mavlink_ctrl_srfc_pt_t);
	p->target = target; // uint8_t:The system setting the commands
	p->bitfieldPt = bitfieldPt; // uint16_t:Bitfield containing the PT configuration

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
// MESSAGE CTRL_SRFC_PT UNPACKING

/**
 * @brief Get field target from ctrl_srfc_pt message
 *
 * @return The system setting the commands
 */
static inline uint8_t mavlink_msg_ctrl_srfc_pt_get_target(const mavlink_message_t* msg)
{
	mavlink_ctrl_srfc_pt_t *p = (mavlink_ctrl_srfc_pt_t *)&msg->payload[0];
	return (uint8_t)(p->target);
}

/**
 * @brief Get field bitfieldPt from ctrl_srfc_pt message
 *
 * @return Bitfield containing the PT configuration
 */
static inline uint16_t mavlink_msg_ctrl_srfc_pt_get_bitfieldPt(const mavlink_message_t* msg)
{
	mavlink_ctrl_srfc_pt_t *p = (mavlink_ctrl_srfc_pt_t *)&msg->payload[0];
	return (uint16_t)(p->bitfieldPt);
}

/**
 * @brief Decode a ctrl_srfc_pt message into a struct
 *
 * @param msg The message to decode
 * @param ctrl_srfc_pt C-struct to decode the message contents into
 */
static inline void mavlink_msg_ctrl_srfc_pt_decode(const mavlink_message_t* msg, mavlink_ctrl_srfc_pt_t* ctrl_srfc_pt)
{
	memcpy( ctrl_srfc_pt, msg->payload, sizeof(mavlink_ctrl_srfc_pt_t));
}
