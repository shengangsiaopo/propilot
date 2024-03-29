// MESSAGE CTRL_SRFC_PT PACKING

#define MAVLINK_MSG_ID_CTRL_SRFC_PT 181
#define MAVLINK_MSG_ID_CTRL_SRFC_PT_LEN 3
#define MAVLINK_MSG_181_LEN 3

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

	return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_CTRL_SRFC_PT_LEN);
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

	return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_CTRL_SRFC_PT_LEN);
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

	p->target = target; // uint8_t:The system setting the commands
	p->bitfieldPt = bitfieldPt; // uint16_t:Bitfield containing the PT configuration

	msg.STX = MAVLINK_STX;
	msg.len = MAVLINK_MSG_ID_CTRL_SRFC_PT_LEN;
	msg.msgid = MAVLINK_MSG_ID_CTRL_SRFC_PT;
	msg.sysid = mavlink_system.sysid;
	msg.compid = mavlink_system.compid;
	msg.seq = mavlink_get_channel_status(chan)->current_tx_seq;
	mavlink_get_channel_status(chan)->current_tx_seq = msg.seq + 1;
	checksum = crc_calculate_msg(&msg, msg.len + MAVLINK_CORE_HEADER_LEN);
	msg.ck_a = (uint8_t)(checksum & 0xFF); ///< Low byte
	msg.ck_b = (uint8_t)(checksum >> 8); ///< High byte

	mavlink_send_msg(chan, &msg);
}

#endif

#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS_SMALL
static inline void mavlink_msg_ctrl_srfc_pt_send(mavlink_channel_t chan, uint8_t target, uint16_t bitfieldPt)
{
	mavlink_header_t hdr;
	mavlink_ctrl_srfc_pt_t payload;
	uint16_t checksum;
	mavlink_ctrl_srfc_pt_t *p = &payload;

	p->target = target; // uint8_t:The system setting the commands
	p->bitfieldPt = bitfieldPt; // uint16_t:Bitfield containing the PT configuration

	hdr.STX = MAVLINK_STX;
	hdr.len = MAVLINK_MSG_ID_CTRL_SRFC_PT_LEN;
	hdr.msgid = MAVLINK_MSG_ID_CTRL_SRFC_PT;
	hdr.sysid = mavlink_system.sysid;
	hdr.compid = mavlink_system.compid;
	hdr.seq = mavlink_get_channel_status(chan)->current_tx_seq;
	mavlink_get_channel_status(chan)->current_tx_seq = hdr.seq + 1;
	mavlink_send_mem(chan, (uint8_t *)&hdr.STX, MAVLINK_NUM_HEADER_BYTES );

	crc_init(&checksum);
	checksum = crc_calculate_mem((uint8_t *)&hdr.len, &checksum, MAVLINK_CORE_HEADER_LEN);
	checksum = crc_calculate_mem((uint8_t *)&payload, &checksum, hdr.len );
	hdr.ck_a = (uint8_t)(checksum & 0xFF); ///< Low byte
	hdr.ck_b = (uint8_t)(checksum >> 8); ///< High byte

	mavlink_send_mem(chan, (uint8_t *)&payload, hdr.len);
	mavlink_send_mem(chan, (uint8_t *)&hdr.ck_a, MAVLINK_NUM_CHECKSUM_BYTES);
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
