
#ifndef RMD_MOTOR_H_
#define RMD_MOTOR_H_

#define RMD_HEADER                                          0x3E
#define RMD_START_COMMAND                                   0x1F
#define LENGHT_REQUEST_RMD_START_COMMAND                    5
#define RMD_SPEED_LOOP_COMMAND                              0xA2
#define LENGHT_REQUEST_RMD_SPEED_LOOP_COMMAND               10
#define RMD_NONE_COMMEND                                    0xFF

extern uint8_t rmd_get_crc(uint8_t* line,int head,int tail);
extern bool rmd_check_crc(uint8_t* line,int head,int tail);
extern bool rmd_check_crc_by_function(uint8_t* line,int len);
extern void rmd_write_respone_command(uint8_t id,uint8_t command);
extern bool rmd_excute_line(uint8_t* line,int len);

#endif