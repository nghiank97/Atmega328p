
#ifndef I2C_H_
#define I2C_H_
#include "config.h"

#define I2C_FLAG                            (1<<TWINT)
#define START_CONDITION                     (1<<TWSTA)
#define STOP_CONDITION                      (1<<TWSTO)
#define I2C_ENABLE                          (1<<TWEN)
#define ENABLE_ACK                          (1<<TWEA)
#define I2C_STATUS                          (TWSR&0xF8)

  // Master Mode - Transmitter / Receiver
#define I2C_START_ACK                       0x08  // A START condition has been transmitted
#define I2C_REP_START_ACK                   0x10  // A repeated START condition has been transmitted
#define I2C_FLAG_ARB_LOST                   0x38  // Arbitration lost in SLA+W or NOT ACK bit
  // Master Transmitter Mode
#define I2C_MT_SLAW_ACK                     0x18  // SLA+W has been transmitted; ACK has been received
#define I2C_MT_SLAW_NACK                    0x20  // SLA+W has been transmitted; NOT ACK has been received
#define I2C_MT_DATA_ACK                     0x28  // Data byte has been transmitted; ACK has been received
#define I2C_MT_DATA_NACK                    0x30  // Data byte has been transmitted; NOT ACK has been received  
  // Master Receiver Mode
#define I2C_MR_SLAR_ACK                     0x40  // SLA+R has been transmitted; ACK has been received
#define I2C_MR_SLAR_NACK                    0x48  // SLA+R has been transmitted; NOT ACK has been received
#define I2C_MR_DATA_ACK                     0x50  // Data byte has been received; ACK has been received
#define I2C_MR_DATA_NACK                    0x58  // Data byte has been received; NOT ACK has been received

#ifndef I2C_SUCCESS
    #define I2C_SUCCESS                     0
#endif

#define I2C_PRESCALER_1                     (0<<TWPS1)|(0<<TWPS0)
#define I2C_PRESCALER_4                     (0<<TWPS1)|(1<<TWPS0)
#define I2C_PRESCALER_16                    (1<<TWPS1)|(0<<TWPS0)
#define I2C_PRESCALER_64                    (1<<TWPS1)|(1<<TWPS0)
typedef uint8_t                             I2C_ERROR;

enum BIT_AK {AK = 0, NOAK = 1};

extern void i2c_init(void);
extern I2C_ERROR i2c_start(void);
extern void i2c_stop(void);
extern uint8_t i2c_get(enum BIT_AK islast);
extern I2C_ERROR i2c_put(uint8_t Data);
extern I2C_ERROR i2c_puts(uint8_t* Data,int len);

#endif
