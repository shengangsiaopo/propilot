// MESSAGE RAW_IMU PACKING

#define MAVLINK_MSG_ID_RAW_IMU 50
#define MAVLINK_MSG_ID_RAW_IMU_LEN 18
#define MAVLINK_MSG_50_LEN 18

typedef struct __mavlink_raw_imu_t 
{
	int16_t xacc; ///< X acceleration (adc units)
	int16_t yacc; ///< Y acceleration (adc units)
	int16_t zacc; ///< Z acceleration (adc units)
	int16_t xgyro; ///< Angular speed around X axis (adc units)
	int16_t ygyro; ///< Angular speed around Y axis (adc units)
	int16_t zgyro; ///< Angular speed around Z axis (adc units)
	int16_t xmag; ///< X Magnetic field (adc units)
	int16_t ymag; ///< Y Magnetic field (adc units)
	int16_t zmag; ///< Z Magnetic field (adc units)
} mavlink_raw_imu_t;


/**
 * @brief Pack a raw_imu message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param xacc X acceleration (adc units)
 * @param yacc Y acceleration (adc units)
 * @param zacc Z acceleration (adc units)
 * @param xgyro Angular speed around X axis (adc units)
 * @param ygyro Angular speed around Y axis (adc units)
 * @param zgyro Angular speed around Z axis (adc units)
 * @param xmag X Magnetic field (adc units)
 * @param ymag Y Magnetic field (adc units)
 * @param zmag Z Magnetic field (adc units)
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_raw_imu_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, int16_t xacc, int16_t yacc, int16_t zacc, int16_t xgyro, int16_t ygyro, int16_t zgyro, int16_t xmag, int16_t ymag, int16_t zmag)
{
	mavlink_raw_imu_t *p = (mavlink_raw_imu_t *)&msg->payload[0];
	msg->msgid = MAVLINK_MSG_ID_RAW_IMU;

	p->xacc = xacc; // int16_t:X acceleration (adc units)
	p->yacc = yacc; // int16_t:Y acceleration (adc units)
	p->zacc = zacc; // int16_t:Z acceleration (adc units)
	p->xgyro = xgyro; // int16_t:Angular speed around X axis (adc units)
	p->ygyro = ygyro; // int16_t:Angular speed around Y axis (adc units)
	p->zgyro = zgyro; // int16_t:Angular speed around Z axis (adc units)
	p->xmag = xmag; // int16_t:X Magnetic field (adc units)
	p->ymag = ymag; // int16_t:Y Magnetic field (adc units)
	p->zmag = zmag; // int16_t:Z Magnetic field (adc units)

	return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_RAW_IMU_LEN);
}

/**
 * @brief Pack a raw_imu message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message was sent over
 * @param msg The MAVLink message to compress the data into
 * @param xacc X acceleration (adc units)
 * @param yacc Y acceleration (adc units)
 * @param zacc Z acceleration (adc units)
 * @param xgyro Angular speed around X axis (adc units)
 * @param ygyro Angular speed around Y axis (adc units)
 * @param zgyro Angular speed around Z axis (adc units)
 * @param xmag X Magnetic field (adc units)
 * @param ymag Y Magnetic field (adc units)
 * @param zmag Z Magnetic field (adc units)
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_raw_imu_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, int16_t xacc, int16_t yacc, int16_t zacc, int16_t xgyro, int16_t ygyro, int16_t zgyro, int16_t xmag, int16_t ymag, int16_t zmag)
{
	mavlink_raw_imu_t *p = (mavlink_raw_imu_t *)&msg->payload[0];
	msg->msgid = MAVLINK_MSG_ID_RAW_IMU;

	p->xacc = xacc; // int16_t:X acceleration (adc units)
	p->yacc = yacc; // int16_t:Y acceleration (adc units)
	p->zacc = zacc; // int16_t:Z acceleration (adc units)
	p->xgyro = xgyro; // int16_t:Angular speed around X axis (adc units)
	p->ygyro = ygyro; // int16_t:Angular speed around Y axis (adc units)
	p->zgyro = zgyro; // int16_t:Angular speed around Z axis (adc units)
	p->xmag = xmag; // int16_t:X Magnetic field (adc units)
	p->ymag = ymag; // int16_t:Y Magnetic field (adc units)
	p->zmag = zmag; // int16_t:Z Magnetic field (adc units)

	return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_RAW_IMU_LEN);
}

/**
 * @brief Encode a raw_imu struct into a message
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param raw_imu C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_raw_imu_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_raw_imu_t* raw_imu)
{
	return mavlink_msg_raw_imu_pack(system_id, component_id, msg, raw_imu->xacc, raw_imu->yacc, raw_imu->zacc, raw_imu->xgyro, raw_imu->ygyro, raw_imu->zgyro, raw_imu->xmag, raw_imu->ymag, raw_imu->zmag);
}

/**
 * @brief Send a raw_imu message
 * @param chan MAVLink channel to send the message
 *
 * @param xacc X acceleration (adc units)
 * @param yacc Y acceleration (adc units)
 * @param zacc Z acceleration (adc units)
 * @param xgyro Angular speed around X axis (adc units)
 * @param ygyro Angular speed around Y axis (adc units)
 * @param zgyro Angular speed around Z axis (adc units)
 * @param xmag X Magnetic field (adc units)
 * @param ymag Y Magnetic field (adc units)
 * @param zmag Z Magnetic field (adc units)
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS
static inline void mavlink_msg_raw_imu_send(mavlink_channel_t chan, int16_t xacc, int16_t yacc, int16_t zacc, int16_t xgyro, int16_t ygyro, int16_t zgyro, int16_t xmag, int16_t ymag, int16_t zmag)
{
	mavlink_message_t msg;
	uint16_t checksum;
	mavlink_raw_imu_t *p = (mavlink_raw_imu_t *)&msg.payload[0];

	p->xacc = xacc; // int16_t:X acceleration (adc units)
	p->yacc = yacc; // int16_t:Y acceleration (adc units)
	p->zacc = zacc; // int16_t:Z acceleration (adc units)
	p->xgyro = xgyro; // int16_t:Angular speed around X axis (adc units)
	p->ygyro = ygyro; // int16_t:Angular speed around Y axis (adc units)
	p->zgyro = zgyro; // int16_t:Angular speed around Z axis (adc units)
	p->xmag = xmag; // int16_t:X Magnetic field (adc units)
	p->ymag = ymag; // int16_t:Y Magnetic field (adc units)
	p->zmag = zmag; // int16_t:Z Magnetic field (adc units)

	msg.STX = MAVLINK_STX;
	msg.len = MAVLINK_MSG_ID_RAW_IMU_LEN;
	msg.msgid = MAVLINK_MSG_ID_RAW_IMU;
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
static inline void mavlink_msg_raw_imu_send(mavlink_channel_t chan, int16_t xacc, int16_t yacc, int16_t zacc, int16_t xgyro, int16_t ygyro, int16_t zgyro, int16_t xmag, int16_t ymag, int16_t zmag)
{
	mavlink_header_t hdr;
	mavlink_raw_imu_t payload;
	uint16_t checksum;
	mavlink_raw_imu_t *p = &payload;

	p->xacc = xacc; // int16_t:X acceleration (adc units)
	p->yacc = yacc; // int16_t:Y acceleration (adc units)
	p->zacc = zacc; // int16_t:Z acceleration (adc units)
	p->xgyro = xgyro; // int16_t:Angular speed around X axis (adc units)
	p->ygyro = ygyro; // int16_t:Angular speed around Y axis (adc units)
	p->zgyro = zgyro; // int16_t:Angular speed around Z axis (adc units)
	p->xmag = xmag; // int16_t:X Magnetic field (adc units)
	p->ymag = ymag; // int16_t:Y Magnetic field (adc units)
	p->zmag = zmag; // int16_t:Z Magnetic field (adc units)

	hdr.STX = MAVLINK_STX;
	hdr.len = MAVLINK_MSG_ID_RAW_IMU_LEN;
	hdr.msgid = MAVLINK_MSG_ID_RAW_IMU;
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
// MESSAGE RAW_IMU UNPACKING

/**
 * @brief Get field xacc from raw_imu message
 *
 * @return X acceleration (adc units)
 */
static inline int16_t mavlink_msg_raw_imu_get_xacc(const mavlink_message_t* msg)
{
	mavlink_raw_imu_t *p = (mavlink_raw_imu_t *)&msg->payload[0];
	return (int16_t)(p->xacc);
}

/**
 * @brief Get field yacc from raw_imu message
 *
 * @return Y acceleration (adc units)
 */
static inline int16_t mavlink_msg_raw_imu_get_yacc(const mavlink_message_t* msg)
{
	mavlink_raw_imu_t *p = (mavlink_raw_imu_t *)&msg->payload[0];
	return (int16_t)(p->yacc);
}

/**
 * @brief Get field zacc from raw_imu message
 *
 * @return Z acceleration (adc units)
 */
static inline int16_t mavlink_msg_raw_imu_get_zacc(const mavlink_message_t* msg)
{
	mavlink_raw_imu_t *p = (mavlink_raw_imu_t *)&msg->payload[0];
	return (int16_t)(p->zacc);
}

/**
 * @brief Get field xgyro from raw_imu message
 *
 * @return Angular speed around X axis (adc units)
 */
static inline int16_t mavlink_msg_raw_imu_get_xgyro(const mavlink_message_t* msg)
{
	mavlink_raw_imu_t *p = (mavlink_raw_imu_t *)&msg->payload[0];
	return (int16_t)(p->xgyro);
}

/**
 * @brief Get field ygyro from raw_imu message
 *
 * @return Angular speed around Y axis (adc units)
 */
static inline int16_t mavlink_msg_raw_imu_get_ygyro(const mavlink_message_t* msg)
{
	mavlink_raw_imu_t *p = (mavlink_raw_imu_t *)&msg->payload[0];
	return (int16_t)(p->ygyro);
}

/**
 * @brief Get field zgyro from raw_imu message
 *
 * @return Angular speed around Z axis (adc units)
 */
static inline int16_t mavlink_msg_raw_imu_get_zgyro(const mavlink_message_t* msg)
{
	mavlink_raw_imu_t *p = (mavlink_raw_imu_t *)&msg->payload[0];
	return (int16_t)(p->zgyro);
}

/**
 * @brief Get field xmag from raw_imu message
 *
 * @return X Magnetic field (adc units)
 */
static inline int16_t mavlink_msg_raw_imu_get_xmag(const mavlink_message_t* msg)
{
	mavlink_raw_imu_t *p = (mavlink_raw_imu_t *)&msg->payload[0];
	return (int16_t)(p->xmag);
}

/**
 * @brief Get field ymag from raw_imu message
 *
 * @return Y Magnetic field (adc units)
 */
static inline int16_t mavlink_msg_raw_imu_get_ymag(const mavlink_message_t* msg)
{
	mavlink_raw_imu_t *p = (mavlink_raw_imu_t *)&msg->payload[0];
	return (int16_t)(p->ymag);
}

/**
 * @brief Get field zmag from raw_imu message
 *
 * @return Z Magnetic field (adc units)
 */
static inline int16_t mavlink_msg_raw_imu_get_zmag(const mavlink_message_t* msg)
{
	mavlink_raw_imu_t *p = (mavlink_raw_imu_t *)&msg->payload[0];
	return (int16_t)(p->zmag);
}

/**
 * @brief Decode a raw_imu message into a struct
 *
 * @param msg The message to decode
 * @param raw_imu C-struct to decode the message contents into
 */
static inline void mavlink_msg_raw_imu_decode(const mavlink_message_t* msg, mavlink_raw_imu_t* raw_imu)
{
	memcpy( raw_imu, msg->payload, sizeof(mavlink_raw_imu_t));
}
