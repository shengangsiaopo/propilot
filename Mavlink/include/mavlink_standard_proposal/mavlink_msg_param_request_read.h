// MESSAGE PARAM_REQUEST_READ PACKING

#define MAVLINK_MSG_ID_PARAM_REQUEST_READ 31
#define MAVLINK_MSG_31_LEN 18

typedef struct __mavlink_param_request_read_t 
{
	uint8_t target_system; ///< System ID
	uint8_t target_component; ///< Component ID
	int8_t param_id[16]; ///< Onboard parameter id
} mavlink_param_request_read_t;

//#if sizeof(mavlink_param_request_read_t) != 18 // sadly this fails 
//#warning struct and size do not match
//#endif

#define MAVLINK_MSG_PARAM_REQUEST_READ_FIELD_PARAM_ID_LEN 16

/**
 * @brief Pack a param_request_read message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param target_system System ID
 * @param target_component Component ID
 * @param param_id Onboard parameter id
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_param_request_read_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, uint8_t target_system, uint8_t target_component, const int8_t* param_id)
{
	mavlink_param_request_read_t *p = (mavlink_param_request_read_t *)&msg->payload[0];
	msg->msgid = MAVLINK_MSG_ID_PARAM_REQUEST_READ;

	p->target_system = target_system; // uint8_t:System ID
	p->target_component = target_component; // uint8_t:Component ID
	memcpy( p->param_id, param_id, sizeof(p->param_id)); // array[16]:Onboard parameter id

	return mavlink_finalize_message(msg, system_id, component_id, sizeof(mavlink_param_request_read_t));
}

/**
 * @brief Pack a param_request_read message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message was sent over
 * @param msg The MAVLink message to compress the data into
 * @param target_system System ID
 * @param target_component Component ID
 * @param param_id Onboard parameter id
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_param_request_read_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, uint8_t target_system, uint8_t target_component, const int8_t* param_id)
{
	mavlink_param_request_read_t *p = (mavlink_param_request_read_t *)&msg->payload[0];
	msg->msgid = MAVLINK_MSG_ID_PARAM_REQUEST_READ;

	p->target_system = target_system; // uint8_t:System ID
	p->target_component = target_component; // uint8_t:Component ID
	memcpy( p->param_id, param_id, sizeof(p->param_id)); // array[16]:Onboard parameter id

	return mavlink_finalize_message_chan(msg, system_id, component_id, chan, sizeof(mavlink_param_request_read_t));
}

/**
 * @brief Encode a param_request_read struct into a message
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param param_request_read C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_param_request_read_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_param_request_read_t* param_request_read)
{
	return mavlink_msg_param_request_read_pack(system_id, component_id, msg, param_request_read->target_system, param_request_read->target_component, param_request_read->param_id);
}

/**
 * @brief Send a param_request_read message
 * @param chan MAVLink channel to send the message
 *
 * @param target_system System ID
 * @param target_component Component ID
 * @param param_id Onboard parameter id
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_param_request_read_send(mavlink_channel_t chan, uint8_t target_system, uint8_t target_component, const int8_t* param_id)
{
	mavlink_message_t msg;
	uint16_t checksum;
	mavlink_param_request_read_t *p = (mavlink_param_request_read_t *)&msg.payload[0];

	msg.msgid = MAVLINK_MSG_ID_PARAM_REQUEST_READ;
	msg.len = sizeof(mavlink_param_request_read_t);
	p->target_system = target_system; // uint8_t:System ID
	p->target_component = target_component; // uint8_t:Component ID
	memcpy( p->param_id, param_id, sizeof(p->param_id)); // array[16]:Onboard parameter id

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
// MESSAGE PARAM_REQUEST_READ UNPACKING

/**
 * @brief Get field target_system from param_request_read message
 *
 * @return System ID
 */
static inline uint8_t mavlink_msg_param_request_read_get_target_system(const mavlink_message_t* msg)
{
	mavlink_param_request_read_t *p = (mavlink_param_request_read_t *)&msg->payload[0];
	return (uint8_t)(p->target_system);
}

/**
 * @brief Get field target_component from param_request_read message
 *
 * @return Component ID
 */
static inline uint8_t mavlink_msg_param_request_read_get_target_component(const mavlink_message_t* msg)
{
	mavlink_param_request_read_t *p = (mavlink_param_request_read_t *)&msg->payload[0];
	return (uint8_t)(p->target_component);
}

/**
 * @brief Get field param_id from param_request_read message
 *
 * @return Onboard parameter id
 */
static inline uint16_t mavlink_msg_param_request_read_get_param_id(const mavlink_message_t* msg, int8_t* param_id)
{
	mavlink_param_request_read_t *p = (mavlink_param_request_read_t *)&msg->payload[0];

	memcpy(param_id, p->param_id, sizeof(p->param_id));
	return sizeof(p->param_id);
}

/**
 * @brief Decode a param_request_read message into a struct
 *
 * @param msg The message to decode
 * @param param_request_read C-struct to decode the message contents into
 */
static inline void mavlink_msg_param_request_read_decode(const mavlink_message_t* msg, mavlink_param_request_read_t* param_request_read)
{
	memcpy( param_request_read, msg->payload, sizeof(mavlink_param_request_read_t));
}
