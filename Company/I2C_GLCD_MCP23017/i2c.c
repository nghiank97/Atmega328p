
#include "elephant.h"

extern void i2c_init(void){
    TWSR = (0<<TWPS1)|(1<<TWPS0);
    TWBR = 38;
    TWCR = (1<<TWEN);
}

extern uint8_t i2c_start(void){
    TWCR = (1<<TWEN)|(1<<TWSTA)|(1<<TWINT);
    while((TWCR&(1<<TWINT))== 0);
    
    if ((I2C_STATUS != I2C_START_ACK) && (I2C_STATUS != I2C_REP_START_ACK)) {
        return I2C_STATUS;
    }
    return I2C_SUCCESS;
}

extern uint8_t i2c_put(uint8_t Data){
    TWDR = Data;
    TWCR = (1<<TWEN)|(1<<TWINT);
    while((TWCR&(1<<TWINT)) == 0);
    // test if data acknowledged
    if (I2C_STATUS != I2C_MT_DATA_ACK) {
        // return status
        return I2C_STATUS;
    }
    return I2C_SUCCESS;
}

extern uint8_t i2c_puts(uint8_t* Data, int len){
    int i;
    uint8_t error;
    for(i=0;i<len;i++){
        error = i2c_put(Data[i]);
        if (error != I2C_SUCCESS){
            return error;
        }
        len+=1;
    }
    return I2C_SUCCESS;
}

extern uint8_t i2c_get(enum BIT_AK islast){
    if(islast == NOAK){
        TWCR = (1<<TWEN)|(1<<TWINT);
    }
    else{
        TWCR = (1<<TWEN)|(1<<TWINT)|(1<<TWEA);
    }
    while((TWCR&(1<<TWINT)) == 0);
    return TWDR;
}


extern void i2c_stop(void){
    TWCR = (1<<TWEN)|(1<<TWINT)|(1<<TWSTO);
}