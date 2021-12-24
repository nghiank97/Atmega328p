
#include "../Inc/i2c.h"

extern void i2c_init(void){
    TWSR = I2C_PRESCALER_4;
    TWBR = 38;
    TWCR = I2C_ENABLE;
}

extern I2C_ERROR i2c_start(void){
    TWCR = I2C_ENABLE|START_CONDITION|I2C_FLAG;
    while((TWCR&I2C_FLAG)== 0);
    
    if ((I2C_STATUS != I2C_START_ACK) && (I2C_STATUS != I2C_REP_START_ACK)) {
        return I2C_STATUS;
    }
    return I2C_SUCCESS;
}

extern I2C_ERROR i2c_put(uint8_t Data){
    TWDR = Data;
    TWCR = I2C_ENABLE|I2C_FLAG;
    while((TWCR&I2C_FLAG) == 0);
    // test if data acknowledged
    if ((I2C_STATUS != I2C_MT_SLAW_ACK) && (I2C_STATUS != I2C_MT_DATA_ACK) && (I2C_STATUS != I2C_MT_DATA_NACK) && (I2C_STATUS != I2C_MR_SLAR_ACK)) {
        // return status
        return I2C_STATUS;
    }
    return I2C_SUCCESS;
}

extern I2C_ERROR i2c_puts(uint8_t *Data, int len){
    int i;
    for(i=0;i<len;i++){
        TWDR = Data[i];
        TWCR = I2C_ENABLE|I2C_FLAG;
        while((TWCR&I2C_FLAG) == 0);
        // test if data acknowledged
        if (I2C_STATUS != I2C_MT_DATA_ACK) {
            // return status
            return I2C_STATUS;
        }
    }
    return I2C_SUCCESS;
}

extern uint8_t i2c_get(enum BIT_AK islast){
    if(islast == NOAK){
        TWCR = I2C_ENABLE|I2C_FLAG;
    }
    else{
        TWCR = I2C_ENABLE|I2C_FLAG|ENABLE_ACK;
    }
    while((TWCR&I2C_FLAG) == 0);
    return TWDR;
}                    

extern void i2c_stop(void){
    TWCR = I2C_ENABLE|I2C_FLAG|STOP_CONDITION;
}
