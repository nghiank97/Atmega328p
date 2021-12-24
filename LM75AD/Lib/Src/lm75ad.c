
#include "../Inc/lm75ad.h"

extern LM75_STATUS lm75_write_configuration(uint8_t config_byte){
	LM75_STATUS status = i2c_start();
	if (status != LM75_SUCCESS){
		return LM75_ERROR;
	}

	status = i2c_put(LM75_ADDRESS_WRITE);
	if (status != LM75_SUCCESS){
		return LM75_ERROR;
	}

	status = i2c_put(config_byte);
	if (status != LM75_SUCCESS){
		return LM75_ERROR;
	}
	i2c_stop();
	return LM75_SUCCESS;
}

extern LM75_STATUS lm75_init(void){
	LM75_STATUS status = lm75_write_configuration(0x00);
	if (status != LM75_SUCCESS){
		return LM75_ERROR;
	}
	return LM75_SUCCESS;
}

extern LM75_STATUS lm75_read_temp_register(uint8_t pointer, uint8_t *ms_byte, uint8_t *ls_byte){
    
	LM75_STATUS status = i2c_start();
	if (status != LM75_SUCCESS){
		return LM75_ERROR;
	}

	status = i2c_put(LM75_ADDRESS_WRITE);
	if (status != LM75_SUCCESS){
		return LM75_ERROR;
	}

	status = i2c_put(pointer);
	if (status != LM75_SUCCESS){
		return LM75_ERROR;
	}

	status = i2c_start();
	if (status != LM75_SUCCESS){
		return LM75_ERROR;
	}

	status = i2c_put(LM75_ADDRESS_READ);
	if (status != LM75_SUCCESS){
		return LM75_ERROR;
	}

	*ms_byte = i2c_get(0);
	*ls_byte = i2c_get(1);
	i2c_stop();

	return LM75_SUCCESS;
}


extern float32_t cvt_temp(enum POINTER_REGISTER type ,uint8_t ms_byte, uint8_t ls_byte){
	float result = 0.0;
	switch (type)
	{
	case TEMP:{
		ls_byte = ls_byte>>4;
		if ((ms_byte&(1<<B7)) ==0){
			result = ms_byte;
			result += ls_byte*0.125;
			return result;
		}
		else{
			result = 0xff-ms_byte;
			result += ls_byte*0.125;
			result *= -1;
			return result;
		}
	}
	case TOS:
	case THYST:{
		ls_byte = ls_byte>>6;
		if ((ms_byte&(1<<B7)) ==0){
			result = ms_byte;
			result += ls_byte*0.5;
			return result;
		}
		else{
			result = 0xff-ms_byte;
			result += ls_byte*0.5;
			result *= -1;
			return result;
		}
	}
	default:
		break;
	}
	return 0.0;
}
