// MESSAGE GPS_LOCAL_ORIGIN_SET PACKING

#define MAVLINK_MSG_ID_GPS_LOCAL_ORIGIN_SET 49

typedef struct __mavlink_gps_local_origin_set_t 
{
	int32_t latitude; ///< Latitude (WGS84), expressed as * 1E7
	int32_t longitude; ///< Longitude (WGS84), expressed as * 1E7
	int32_t altitude; ///< Altitude(WGS84), expressed as * 1000

} mavlink_gps_local_origin_set_t;



/**
 * @brief Pack a gps_local_origin_set message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param latitude Latitude (WGS84), expressed as * 1E7
 * @param longitude Longitude (WGS84), expressed as * 1E7
 * @param altitude Altitude(WGS84), expressed as * 1000
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_gps_local_origin_set_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, int32_t latitude, int32_t longitude, int32_t altitude)
{
	mavlink_gps_local_origin_set_t *p = (mavlink_gps_local_origin_set_t *)&msg->payload[0];
	msg->msgid = MAVLINK_MSG_ID_GPS_LOCAL_ORIGIN_SET;

	p->latitude = latitude; // int32_t:Latitude (WGS84), expressed as * 1E7
	p->longitude = longitude; // int32_t:Longitude (WGS84), expressed as * 1E7
	p->altitude = altitude; // int32_t:Altitude(WGS84), expressed as * 1000

	return mavlink_finalize_message(msg, system_id, component_id, sizeof(mavlink_gps_local_origin_set_t));
}

/**
 * @brief Pack a gps_local_origin_set message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message was sent over
 * @param msg The MAVLink message to compress the data into
 * @param latitude Latitude (WGS84), expressed as * 1E7
 * @param longitude Longitude (WGS84), expressed as * 1E7
 * @param altitude Altitude(WGS84), expressed as * 1000
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_gps_local_origin_set_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, int32_t latitude, int32_t longitude, int32_t altitude)
{
	mavlink_gps_local_origin_set_t *p = (mavlink_gps_local_origin_set_t *)&msg->payload[0];
	msg->msgid = MAVLINK_MSG_ID_GPS_LOCAL_ORIGIN_SET;

	p->latitude = latitude; // int32_t:Latitude (WGS84), expressed as * 1E7
	p->longitude = longitude; // int32_t:Longitude (WGS84), expressed as * 1E7
	p->altitude = altitude; // int32_t:Altitude(WGS84), expressed as * 1000

	return mavlink_finalize_message_chan(msg, system_id, component_id, chan, sizeof(mavlink_gps_local_origin_set_t));
}

/**
 * @brief Encode a gps_local_origin_set struct into a message
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param gps_local_origin_set C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_gps_local_origin_set_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_gps_local_origin_set_t* gps_local_origin_set)
{
	return mavlink_msg_gps_local_origin_set_pack(system_id, component_id, msg, gps_local_origin_set->latitude, gps_local_origin_set->longitude, gps_local_origin_set->altitude);
}

/**
 * @brief Send a gps_local_origin_set message
 * @param chan MAVLink channel to send the message
 *
 * @param latitude Latitude (WGS84), expressed as * 1E7
 * @param longitude Longitude (WGS84), expressed as * 1E7
 * @param altitude Altitude(WGS84), expressed as * 1000
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_gps_local_origin_set_send(mavlink_channel_t chan, int32_t latitude, int32_t longitude, int32_t altitude)
{
	mavlink_message_t msg;
	uint16_t checksum;
	mavlink_gps_local_origin_set_t *p = (mavlink_gps_local_origin_set_t *)&msg.payload[0];

	msg.msgid = MAVLINK_MSG_ID_GPS_LOCAL_ORIGIN_SET;
	msg.len = sizeof(mavlink_gps_local_origin_set_t);
	p->latitude = latitude; // int32_t:Latitude (WGS84), expressed as * 1E7
	p->longitude = longitude; // int32_t:Longitude (WGS84), expressed as * 1E7
	p->altitude = altitude; // int32_t:Altitude(WGS84), expressed as * 1000

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
// MESSAGE GPS_LOCAL_ORIGIN_SET UNPACKING

/**
 * @brief Get field latitude from gps_local_origin_set message
 *
 * @return Latitude (WGS84), expressed as * 1E7
 */
static inline int32_t mavlink_msg_gps_local_origin_set_get_latitude(const mavlink_message_t* msg)
{
	mavlink_gps_local_origin_set_t *p = (mavlink_gps_local_origin_set_t *)&msg->payload[0];
	return (int32_t)(p->latitude);
}

/**
 * @brief Get field longitude from gps_local_origin_set message
 *
 * @return Longitude (WGS84), expressed as * 1E7
 */
static inline int32_t mavlink_msg_gps_local_origin_set_get_longitude(const mavlink_message_t* msg)
{
	mavlink_gps_local_origin_set_t *p = (mavlink_gps_local_origin_set_t *)&msg->payload[0];
	return (int32_t)(p->longitude);
}

/**
 * @brief Get field altitude from gps_local_origin_set message
 *
 * @return Altitude(WGS84), expressed as * 1000
 */
static inline int32_t mavlink_msg_gps_local_origin_set_get_altitude(const mavlink_message_t* msg)
{
	mavlink_gps_local_origin_set_t *p = (mavlink_gps_local_origin_set_t *)&msg->payload[0];
	return (int32_t)(p->altitude);
}

/**
 * @brief Decode a gps_local_origin_set message into a struct
 *
 * @param msg The message to decode
 * @param gps_local_origin_set C-struct to decode the message contents into
 */
static inline void mavlink_msg_gps_local_origin_set_decode(const mavlink_message_t* msg, mavlink_gps_local_origin_set_t* gps_local_origin_set)
{
	memcpy( gps_local_origin_set, msg->payload, sizeof(mavlink_gps_local_origin_set_t));
}
