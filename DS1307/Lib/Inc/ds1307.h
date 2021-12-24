
#ifndef __DS1307_h__
#define __DS1307_h__

#include "config.h"
#include "i2c.h"

enum DS1307_ADD{
	DS1307_WRI      = 0xd0,
	DS1307_REA      = 0xd1,
	DS1307_SEC      = 0x00,
	DS1307_MIN      = 0x01,
	DS1307_HOU      = 0x02,
	DS1307_WEK      = 0x03,
	DS1307_DAT      = 0x04,
	DS1307_MON      = 0x05,
	DS1307_YEA      = 0x06,
    DS1307_CONTROL  = 0x07
};

enum DS1307_CONTROL_REGISTER{
    OUT = 7,
    SQW = 4,
    RS1 = 1,
    RS0 = 0
};

typedef enum{
    PLUSE_1_Hz      = 0x00,
    PLUSE_4096_Hz   = 0x01,
    PLUSE_8192_Hz   = 0x02,
    PLUSE_32768_Hz  = 0x03
}WIDTH_PLUSE;


extern int cvt_num_r(uint8_t num);
extern int cvt_hou_r(uint8_t hou);

extern void ds1307_init(void);

extern void ds1307_put(uint8_t add,uint8_t dat);
extern void ds1307_setime(uint8_t hou, uint8_t min, uint8_t sec);
extern void ds1307_setdate(uint8_t yea, uint8_t mon, uint8_t day, uint8_t wek);

extern uint8_t ds1307_get(uint8_t add);
extern void ds1307_getime(uint8_t* hou, uint8_t* min, uint8_t* sec);
extern void ds1307_getdate(uint8_t* yea, uint8_t* mon, uint8_t* day, uint8_t* wek);

extern void ds1307_sout_level(level status);
extern void ds1307_sout_pluse(WIDTH_PLUSE width);

//void mlcd4_time(uint8_t hou, uint8_t min, uint8_t sec);
//void mlcd4_date(uint8_t yea, uint8_t mon, uint8_t dat, uint8_t wek);

#endif
