
#ifndef LM75AD_H_
#define LM75AD_H_
#include "config.h"
#include "i2c.h"

/* address of lm75ad: setup with A0,A1,A2 pin */

#define A0						1
#define A1						0
#define A2						0
#define LM75_ADDRESS			(0x48|(A0<<0)|(A1<<1)|(A2<<2))
#define LM75_ADDRESS_WRITE		(LM75_ADDRESS<<1)
#define LM75_ADDRESS_READ		(LM75_ADDRESS<<1|(1<<0))

/* register list */

enum REGISTER_LIST{
	REGISTER_CONF 				= 0x01,
	REGISTER_TEMP 				= 0x00,
	REGISTER_TOS 				= 0x03,
	REGISTER_THYST 				= 0x02
};


enum DATA_BYTE{
	B0 							= 0,
	B1 							= 1,
	B2 							= 2,
	B3 							= 3,
	B4 							= 4,
	B5 							= 5,
	B6 							= 6,
	B7 							= 7
};

enum POINTER_REGISTER{
	TEMP						= (0<<B0)|(0<<B1), 	/*Temperature register*/
	CONF						= (1<<B0)|(0<<B1),	/*Configuration register*/
	THYST						= (0<<B0)|(1<<B1),	/*Hysteresis register*/
	TOS							= (1<<B0)|(1<<B1)	/*Overtemerature shutdown register*/
};

enum CONFIGURATION_REGISTER{
	DOMS_NORMAL					= (0<<B0), /*device operation mode select - normal*/					/*default*/
	DOMS_SHUTDOWN				= (1<<B0), /*device operation mode select - shutdown*/

	OS_COMPARATOR				= (0<<B1), /*OS operation mode select - comparator*/					/*default*/
	OS_INTERRUPT				= (1<<B1), /*OS operation mode select - interrupt*/

	OS_POL_HIGH					= (0<<B2), /*OS polarity select - low*/									/*default*/
	OS_POL_LOW					= (1<<B2), /*OS polarity select - high*/

	OS_F_QUE_0					= (0<<B3)|(0<<B4), /*OS fault queue propramming - queue value = 1*/		/*default*/
	OS_F_QUE_1					= (1<<B3)|(0<<B4), /*OS fault queue propramming - queue value = 2*/
	OS_F_QUE_2					= (0<<B3)|(1<<B4), /*OS fault queue propramming - queue value = 4*/
	OS_F_QUE_3					= (1<<B3)|(1<<B4)  /*OS fault queue propramming - queue value = 6*/
};

#ifndef LM75_SUCCESS
    #define LM75_SUCCESS        0
#endif


#ifndef LM75_ERROR
    #define LM75_ERROR          1
#endif

typedef uint8_t                 LM75_STATUS;
/*
	description : write configuration register - send include; address, pointer byte (0x01), configuration (user)
	para 		: uint8_t config_byte - configuration byte
	return 		: LM75_STATUS
*/

extern LM75_STATUS lm75_write_configuration(uint8_t config_byte);

/*
	description : lm75_write_configuration(0x00) - write configuration by defalut
	para 		: void 
	return 		: LM75_STATUS
*/

extern LM75_STATUS lm75_init(void);

/*
	description : read temperature - Temp,Tos,Thyst register config by POINTER_REGISTER
	para 		: uint8_t pointer - select temperature register 
				  uint8_t *ms_byte - high byte register
				  uint8_t *ls_byte - low byte register
	return 		: LM75_STATUS
*/

extern LM75_STATUS lm75_read_temp_register(uint8_t pointer, uint8_t *ms_byte, uint8_t *ls_byte);

/*
	description : convert to float temp
	para 		: enum POINTER_REGISTER type
				  uint8_t ms_byte - high byte register
				  uint8_t ls_byte - low byte register
	return 		: float temp
*/

extern float32_t cvt_temp(enum POINTER_REGISTER type ,uint8_t ms_byte, uint8_t ls_byte);

#endif
