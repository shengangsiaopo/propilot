// MESSAGE ENCAPSULATED_DATA PACKING

#define MAVLINK_MSG_ID_ENCAPSULATED_DATA 171
#define MAVLINK_MSG_ID_ENCAPSULATED_DATA_LEN 255
#define MAVLINK_MSG_171_LEN 255

typedef struct __mavlink_encapsulated_data_t 
{
	uint16_t seqnr; ///< sequence number (starting with 0 on every transmission)
	uint8_t data[253]; ///< image data bytes
} mavlink_encapsulated_data_t;

#define MAVLINK_MSG_ENCAPSULATED_DATA_FIELD_DATA_LEN 253

/**
 * @brief Pack a encapsulated_data message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param seqnr sequence number (starting with 0 on every transmission)
 * @param data image data bytes
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_encapsulated_data_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, uint16_t seqnr, const uint8_t* data)
{
	mavlink_encapsulated_data_t *p = (mavlink_encapsulated_data_t *)&msg->payload[0];
	msg->msgid = MAVLINK_MSG_ID_ENCAPSULATED_DATA;

	p->seqnr = seqnr; // uint16_t:sequence number (starting with 0 on every transmission)
	memcpy(p->data, data, sizeof(p->data)); // uint8_t[253]:image data bytes

	return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_ENCAPSULATED_DATA_LEN);
}

/**
 * @brief Pack a encapsulated_data message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message was sent over
 * @param msg The MAVLink message to compress the data into
 * @param seqnr sequence number (starting with 0 on every transmission)
 * @param data image data bytes
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_encapsulated_data_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, uint16_t seqnr, const uint8_t* data)
{
	mavlink_encapsulated_data_t *p = (mavlink_encapsulated_data_t *)&msg->payload[0];
	msg->msgid = MAVLINK_MSG_ID_ENCAPSULATED_DATA;

	p->seqnr = seqnr; // uint16_t:sequence number (starting with 0 on every transmission)
	memcpy(p->data, data, sizeof(p->data)); // uint8_t[253]:image data bytes

	return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_ENCAPSULATED_DATA_LEN);
}

/**
 * @brief Encode a encapsulated_data struct into a message
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param encapsulated_data C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_encapsulated_data_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_encapsulated_data_t* encapsulated_data)
{
	return mavlink_msg_encapsulated_data_pack(system_id, component_id, msg, encapsulated_data->seqnr, encapsulated_data->data);
}

/**
 * @brief Send a encapsulated_data message
 * @param chan MAVLink channel to send the message
 *
 * @param seqnr sequence number (starting with 0 on every transmission)
 * @param data image data bytes
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS
static inline void mavlink_msg_encapsulated_data_send(mavlink_channel_t chan, uint16_t seqnr, const uint8_t* data)
{
	mavlink_message_t msg;
	uint16_t checksum;
	mavlink_encapsulated_data_t *p = (mavlink_encapsulated_data_t *)&msg.payload[0];

	p->seqnr = seqnr; // uint16_t:sequence number (starting with 0 on every transmission)
	memcpy(p->data, data, sizeof(p->data)); // uint8_t[253]:image data bytes

	msg.STX = MAVLINK_STX;
	msg.len = MAVLINK_MSG_ID_ENCAPSULATED_DATA_LEN;
	msg.msgid = MAVLINK_MSG_ID_ENCAPSULATED_DATA;
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
static inline void mavlink_msg_encapsulated_data_send(mavlink_channel_t chan, uint16_t seqnr, const uint8_t* data)
{
	mavlink_header_t hdr;
	mavlink_encapsulated_data_t payload;
	uint16_t checksum;
	mavlink_encapsulated_data_t *p = &payload;

	p->seqnr = seqnr; // uint16_t:sequence number (starting with 0 on every transmission)
	memcpy(p->data, data, sizeof(p->data)); // uint8_t[253]:image data bytes

	hdr.STX = MAVLINK_STX;
	hdr.len = MAVLINK_MSG_ID_ENCAPSULATED_DATA_LEN;
	hdr.msgid = MAVLINK_MSG_ID_ENCAPSULATED_DATA;
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
// MESSAGE ENCAPSULATED_DATA UNPACKING

/**
 * @brief Get field seqnr from encapsulated_data message
 *
 * @return sequence number (starting with 0 on every transmission)
 */
static inline uint16_t mavlink_msg_encapsulated_data_get_seqnr(const mavlink_message_t* msg)
{
	mavlink_encapsulated_data_t *p = (mavlink_encapsulated_data_t *)&msg->payload[0];
	return (uint16_t)(p->seqnr);
}

/**
 * @brief Get field data from encapsulated_data message
 *
 * @return image data bytes
 */
static inline uint16_t mavlink_msg_encapsulated_data_get_data(const mavlink_message_t* msg, uint8_t* data)
{
	mavlink_encapsulated_data_t *p = (mavlink_encapsulated_data_t *)&msg->payload[0];

	memcpy(data, p->data, sizeof(p->data));
	return sizeof(p->data);
}

/**
 * @brief Decode a encapsulated_data message into a struct
 *
 * @param msg The message to decode
 * @param encapsulated_data C-struct to decode the message contents into
 */
static inline void mavlink_msg_encapsulated_data_decode(const mavlink_message_t* msg, mavlink_encapsulated_data_t* encapsulated_data)
{
	memcpy( encapsulated_data, msg->payload, sizeof(mavlink_encapsulated_data_t));
}
