/* Adding an offset to enums cause it to start
   with a value that represents an ASCII character,
   so the communication is readable through serial terminal */
#ifndef FOLLOW_PROTOCOL_DEF_H
#define FOLLOW_PROTOCOL_DEF_H

#define ENUM_OFFSET	0x21 // Adding an offset to enums
#define FOLLOW_PROTOCOL_CMD_MAX_SIZE (FOLLOW_OPCODE_EOF - ENUM_OFFSET)

typedef enum followOpcode
{
	FOLLOW_OPCODE_INC = ENUM_OFFSET,
	FOLLOW_OPCODE_DEC,
	FOLLOW_OPCODE_SET,
	FOLLOW_OPCODE_CONFIG,
	FOLLOW_OPCODE_START,
	FOLLOW_OPCODE_STOP,
	FOLLOW_OPCODE_SAVE,
	FOLLOW_OPCODE_EOF  //!< Marks the largest value for opcode
}followOpcode_t;

typedef enum followCtrlVar
{
	FOLLOW_VAR_KP = ENUM_OFFSET,
	FOLLOW_VAR_KI,
	FOLLOW_VAR_KD,
	FOLLOW_VAR_EOF,
}followCtrlVar_t;

typedef struct __attribute__((__packed__)) followConfig
{
	uint32_t kp;
	uint32_t ki;
	uint32_t kd;
}followConfig_t;

// todo: define a better name for this.
typedef struct __attribute__((__packed__)) followVarSet
{
	followCtrlVar_t var;
	uint32_t value;
}followVarSet_t;

/*  Defining a type for the structure of a command. */
typedef struct __attribute__((__packed__)) followCmd
{
	followOpcode_t 		cmd;
	union
	{
		followVarSet_t  variable;
		followConfig_t	config;
	};
	// uint16_t crc; // for now we dont need CRC
}followCmd_t;

#endif // FOLLOW_PROTOCOL_DEF_H
