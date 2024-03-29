// MESSAGE MID_LVL_CMDS PACKING

#define MAVLINK_MSG_ID_MID_LVL_CMDS 180
#define MAVLINK_MSG_ID_MID_LVL_CMDS_LEN 13
#define MAVLINK_MSG_180_LEN 13

typedef struct __mavlink_mid_lvl_cmds_t 
{
	uint8_t target; ///< The system setting the commands
	float hCommand; ///< Commanded Airspeed
	float uCommand; ///< Log value 2 
	float rCommand; ///< Log value 3 
} mavlink_mid_lvl_cmds_t;


/**
 * @brief Pack a mid_lvl_cmds message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param target The system setting the commands
 * @param hCommand Commanded Airspeed
 * @param uCommand Log value 2 
 * @param rCommand Log value 3 
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_mid_lvl_cmds_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, uint8_t target, float hCommand, float uCommand, float rCommand)
{
	mavlink_mid_lvl_cmds_t *p = (mavlink_mid_lvl_cmds_t *)&msg->payload[0];
	msg->msgid = MAVLINK_MSG_ID_MID_LVL_CMDS;

	p->target = target; // uint8_t:The system setting the commands
	p->hCommand = hCommand; // float:Commanded Airspeed
	p->uCommand = uCommand; // float:Log value 2 
	p->rCommand = rCommand; // float:Log value 3 

	return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_MID_LVL_CMDS_LEN);
}

/**
 * @brief Pack a mid_lvl_cmds message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message was sent over
 * @param msg The MAVLink message to compress the data into
 * @param target The system setting the commands
 * @param hCommand Commanded Airspeed
 * @param uCommand Log value 2 
 * @param rCommand Log value 3 
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_mid_lvl_cmds_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, uint8_t target, float hCommand, float uCommand, float rCommand)
{
	mavlink_mid_lvl_cmds_t *p = (mavlink_mid_lvl_cmds_t *)&msg->payload[0];
	msg->msgid = MAVLINK_MSG_ID_MID_LVL_CMDS;

	p->target = target; // uint8_t:The system setting the commands
	p->hCommand = hCommand; // float:Commanded Airspeed
	p->uCommand = uCommand; // float:Log value 2 
	p->rCommand = rCommand; // float:Log value 3 

	return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_MID_LVL_CMDS_LEN);
}

/**
 * @brief Encode a mid_lvl_cmds struct into a message
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param mid_lvl_cmds C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_mid_lvl_cmds_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_mid_lvl_cmds_t* mid_lvl_cmds)
{
	return mavlink_msg_mid_lvl_cmds_pack(system_id, component_id, msg, mid_lvl_cmds->target, mid_lvl_cmds->hCommand, mid_lvl_cmds->uCommand, mid_lvl_cmds->rCommand);
}

/**
 * @brief Send a mid_lvl_cmds message
 * @param chan MAVLink channel to send the message
 *
 * @param target The system setting the commands
 * @param hCommand Commanded Airspeed
 * @param uCommand Log value 2 
 * @param rCommand Log value 3 
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS
static inline void mavlink_msg_mid_lvl_cmds_send(mavlink_channel_t chan, uint8_t target, float hCommand, float uCommand, float rCommand)
{
	mavlink_message_t msg;
	uint16_t checksum;
	mavlink_mid_lvl_cmds_t *p = (mavlink_mid_lvl_cmds_t *)&msg.payload[0];

	p->target = target; // uint8_t:The system setting the commands
	p->hCommand = hCommand; // float:Commanded Airspeed
	p->uCommand = uCommand; // float:Log value 2 
	p->rCommand = rCommand; // float:Log value 3 

	msg.STX = MAVLINK_STX;
	msg.len = MAVLINK_MSG_ID_MID_LVL_CMDS_LEN;
	msg.msgid = MAVLINK_MSG_ID_MID_LVL_CMDS;
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
static inline void mavlink_msg_mid_lvl_cmds_send(mavlink_channel_t chan, uint8_t target, float hCommand, float uCommand, float rCommand)
{
	mavlink_header_t hdr;
	mavlink_mid_lvl_cmds_t payload;
	uint16_t checksum;
	mavlink_mid_lvl_cmds_t *p = &payload;

	p->target = target; // uint8_t:The system setting the commands
	p->hCommand = hCommand; // float:Commanded Airspeed
	p->uCommand = uCommand; // float:Log value 2 
	p->rCommand = rCommand; // float:Log value 3 

	hdr.STX = MAVLINK_STX;
	hdr.len = MAVLINK_MSG_ID_MID_LVL_CMDS_LEN;
	hdr.msgid = MAVLINK_MSG_ID_MID_LVL_CMDS;
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
// MESSAGE MID_LVL_CMDS UNPACKING

/**
 * @brief Get field target from mid_lvl_cmds message
 *
 * @return The system setting the commands
 */
static inline uint8_t mavlink_msg_mid_lvl_cmds_get_target(const mavlink_message_t* msg)
{
	mavlink_mid_lvl_cmds_t *p = (mavlink_mid_lvl_cmds_t *)&msg->payload[0];
	return (uint8_t)(p->target);
}

/**
 * @brief Get field hCommand from mid_lvl_cmds message
 *
 * @return Commanded Airspeed
 */
static inline float mavlink_msg_mid_lvl_cmds_get_hCommand(const mavlink_message_t* msg)
{
	mavlink_mid_lvl_cmds_t *p = (mavlink_mid_lvl_cmds_t *)&msg->payload[0];
	return (float)(p->hCommand);
}

/**
 * @brief Get field uCommand from mid_lvl_cmds message
 *
 * @return Log value 2 
 */
static inline float mavlink_msg_mid_lvl_cmds_get_uCommand(const mavlink_message_t* msg)
{
	mavlink_mid_lvl_cmds_t *p = (mavlink_mid_lvl_cmds_t *)&msg->payload[0];
	return (float)(p->uCommand);
}

/**
 * @brief Get field rCommand from mid_lvl_cmds message
 *
 * @return Log value 3 
 */
static inline float mavlink_msg_mid_lvl_cmds_get_rCommand(const mavlink_message_t* msg)
{
	mavlink_mid_lvl_cmds_t *p = (mavlink_mid_lvl_cmds_t *)&msg->payload[0];
	return (float)(p->rCommand);
}

/**
 * @brief Decode a mid_lvl_cmds message into a struct
 *
 * @param msg The message to decode
 * @param mid_lvl_cmds C-struct to decode the message contents into
 */
static inline void mavlink_msg_mid_lvl_cmds_decode(const mavlink_message_t* msg, mavlink_mid_lvl_cmds_t* mid_lvl_cmds)
{
	memcpy( mid_lvl_cmds, msg->payload, sizeof(mavlink_mid_lvl_cmds_t));
}
