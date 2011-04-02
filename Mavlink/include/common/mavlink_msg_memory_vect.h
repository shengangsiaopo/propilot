// MESSAGE MEMORY_VECT PACKING

#define MAVLINK_MSG_ID_MEMORY_VECT 250
#define MAVLINK_MSG_ID_MEMORY_VECT_LEN 36
#define MAVLINK_MSG_250_LEN 36

typedef struct __mavlink_memory_vect_t 
{
	uint16_t address; ///< Starting address of the debug variables
	uint8_t ver; ///< Version code of the type variable. 0=unknown, type ignored and assumed int16_t. 1=as below
	uint8_t type; ///< Type code of the memory variables. for ver = 1: 0=16 x int16_t, 1=16 x uint16_t, 2=16 x Q15, 3=16 x 1Q14
	int8_t value[32]; ///< Memory contents at specified address
} mavlink_memory_vect_t;

//#if sizeof(mavlink_memory_vect_t) != 36 // sadly this fails 
//#warning struct and size do not match
//#endif

#define MAVLINK_MSG_MEMORY_VECT_FIELD_VALUE_LEN 32

/**
 * @brief Pack a memory_vect message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param address Starting address of the debug variables
 * @param ver Version code of the type variable. 0=unknown, type ignored and assumed int16_t. 1=as below
 * @param type Type code of the memory variables. for ver = 1: 0=16 x int16_t, 1=16 x uint16_t, 2=16 x Q15, 3=16 x 1Q14
 * @param value Memory contents at specified address
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_memory_vect_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, uint16_t address, uint8_t ver, uint8_t type, const int8_t* value)
{
	mavlink_memory_vect_t *p = (mavlink_memory_vect_t *)&msg->payload[0];
	msg->msgid = MAVLINK_MSG_ID_MEMORY_VECT;

	p->address = address; // uint16_t:Starting address of the debug variables
	p->ver = ver; // uint8_t:Version code of the type variable. 0=unknown, type ignored and assumed int16_t. 1=as below
	p->type = type; // uint8_t:Type code of the memory variables. for ver = 1: 0=16 x int16_t, 1=16 x uint16_t, 2=16 x Q15, 3=16 x 1Q14
	memcpy( p->value, value, sizeof(p->value)); // array[32]:Memory contents at specified address

	return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_MEMORY_VECT_LEN);
}

/**
 * @brief Pack a memory_vect message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message was sent over
 * @param msg The MAVLink message to compress the data into
 * @param address Starting address of the debug variables
 * @param ver Version code of the type variable. 0=unknown, type ignored and assumed int16_t. 1=as below
 * @param type Type code of the memory variables. for ver = 1: 0=16 x int16_t, 1=16 x uint16_t, 2=16 x Q15, 3=16 x 1Q14
 * @param value Memory contents at specified address
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_memory_vect_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, uint16_t address, uint8_t ver, uint8_t type, const int8_t* value)
{
	mavlink_memory_vect_t *p = (mavlink_memory_vect_t *)&msg->payload[0];
	msg->msgid = MAVLINK_MSG_ID_MEMORY_VECT;

	p->address = address; // uint16_t:Starting address of the debug variables
	p->ver = ver; // uint8_t:Version code of the type variable. 0=unknown, type ignored and assumed int16_t. 1=as below
	p->type = type; // uint8_t:Type code of the memory variables. for ver = 1: 0=16 x int16_t, 1=16 x uint16_t, 2=16 x Q15, 3=16 x 1Q14
	memcpy( p->value, value, sizeof(p->value)); // array[32]:Memory contents at specified address

	return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_MEMORY_VECT_LEN);
}

/**
 * @brief Encode a memory_vect struct into a message
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param memory_vect C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_memory_vect_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_memory_vect_t* memory_vect)
{
	return mavlink_msg_memory_vect_pack(system_id, component_id, msg, memory_vect->address, memory_vect->ver, memory_vect->type, memory_vect->value);
}

/**
 * @brief Send a memory_vect message
 * @param chan MAVLink channel to send the message
 *
 * @param address Starting address of the debug variables
 * @param ver Version code of the type variable. 0=unknown, type ignored and assumed int16_t. 1=as below
 * @param type Type code of the memory variables. for ver = 1: 0=16 x int16_t, 1=16 x uint16_t, 2=16 x Q15, 3=16 x 1Q14
 * @param value Memory contents at specified address
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_memory_vect_send(mavlink_channel_t chan, uint16_t address, uint8_t ver, uint8_t type, const int8_t* value)
{
	mavlink_message_t msg;
	uint16_t checksum;
	mavlink_memory_vect_t *p = (mavlink_memory_vect_t *)&msg.payload[0];

	msg.msgid = MAVLINK_MSG_ID_MEMORY_VECT;
	msg.len = MAVLINK_MSG_ID_MEMORY_VECT_LEN;

	p->address = address; // uint16_t:Starting address of the debug variables
	p->ver = ver; // uint8_t:Version code of the type variable. 0=unknown, type ignored and assumed int16_t. 1=as below
	p->type = type; // uint8_t:Type code of the memory variables. for ver = 1: 0=16 x int16_t, 1=16 x uint16_t, 2=16 x Q15, 3=16 x 1Q14
	memcpy( p->value, value, sizeof(p->value)); // array[32]:Memory contents at specified address

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
// MESSAGE MEMORY_VECT UNPACKING

/**
 * @brief Get field address from memory_vect message
 *
 * @return Starting address of the debug variables
 */
static inline uint16_t mavlink_msg_memory_vect_get_address(const mavlink_message_t* msg)
{
	mavlink_memory_vect_t *p = (mavlink_memory_vect_t *)&msg->payload[0];
	return (uint16_t)(p->address);
}

/**
 * @brief Get field ver from memory_vect message
 *
 * @return Version code of the type variable. 0=unknown, type ignored and assumed int16_t. 1=as below
 */
static inline uint8_t mavlink_msg_memory_vect_get_ver(const mavlink_message_t* msg)
{
	mavlink_memory_vect_t *p = (mavlink_memory_vect_t *)&msg->payload[0];
	return (uint8_t)(p->ver);
}

/**
 * @brief Get field type from memory_vect message
 *
 * @return Type code of the memory variables. for ver = 1: 0=16 x int16_t, 1=16 x uint16_t, 2=16 x Q15, 3=16 x 1Q14
 */
static inline uint8_t mavlink_msg_memory_vect_get_type(const mavlink_message_t* msg)
{
	mavlink_memory_vect_t *p = (mavlink_memory_vect_t *)&msg->payload[0];
	return (uint8_t)(p->type);
}

/**
 * @brief Get field value from memory_vect message
 *
 * @return Memory contents at specified address
 */
static inline uint16_t mavlink_msg_memory_vect_get_value(const mavlink_message_t* msg, int8_t* value)
{
	mavlink_memory_vect_t *p = (mavlink_memory_vect_t *)&msg->payload[0];

	memcpy(value, p->value, sizeof(p->value));
	return sizeof(p->value);
}

/**
 * @brief Decode a memory_vect message into a struct
 *
 * @param msg The message to decode
 * @param memory_vect C-struct to decode the message contents into
 */
static inline void mavlink_msg_memory_vect_decode(const mavlink_message_t* msg, mavlink_memory_vect_t* memory_vect)
{
	memcpy( memory_vect, msg->payload, sizeof(mavlink_memory_vect_t));
}
