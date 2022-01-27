
#include "elephant.h"

extern uint8_t rmd_get_crc(uint8_t* line,int head,int tail){
    uint8_t crc = 0x00;
    for(int i=head;i<tail;i++){
        crc += line[i];
    }
    crc = (crc % 256);
    return crc;
}

extern bool rmd_check_crc(uint8_t* line,int head,int tail){
    uint8_t crc = rmd_get_crc(line,head,tail);
    if (crc == line[tail]){
        return True;
    }
    return False;
}

extern bool rmd_check_crc_by_function(uint8_t* line,int len){
    uint8_t command = line[1];
    switch (command)
    {
        case RMD_START_COMMAND:{
            return rmd_check_crc(line,0,len-1);
            break;
        }
        case RMD_SPEED_LOOP_COMMAND:{
            bool first_check = rmd_check_crc(line,0,4);
            if (first_check == True){
                return rmd_check_crc(line,5,len-1);
            }
            else{
                return False;
            }
            break;
        }
        default:
            return False;
            break;
    }
    return False;
}

extern void rmd_write_respone_command(uint8_t id,uint8_t command){

    switch (command)
    {
        case RMD_START_COMMAND:{
            uint8_t responce[4] = {RMD_HEADER, command, id, 0x02};
            uint8_t header_crc = rmd_get_crc(responce,0,4);

            uint8_t data_responce[2] = {0x02, 0x01};
            uint8_t data_crc = rmd_get_crc(data_responce,0,2);

            for(int i=0;i<4;i++){
                serial_write(responce[i]);
            }
            serial_write(header_crc);
            for(int i=0;i<2;i++){
                serial_write(data_responce[i]);
            }
            serial_write(data_crc);
            break;
        }

        case RMD_SPEED_LOOP_COMMAND:{
            uint8_t responce[4] = {RMD_HEADER, command, id, 0x07};
            uint8_t header_crc = rmd_get_crc(responce,0,4);

            uint8_t data_responce[7] = {0x55, 0x15, 0x25, 0x35, 0x05, 0x25, 0x25};
            uint8_t data_crc = rmd_get_crc(data_responce,0,7);
            
            for(int i=0;i<4;i++){
                serial_write(responce[i]);
            }
            serial_write(header_crc);
            for(int i=0;i<7;i++){
                serial_write(data_responce[i]);
            }
            serial_write(data_crc);
            break;
        }
        default:
            break;
    }
}

extern bool rmd_excute_line(uint8_t* line,int len){
    if (rmd_check_crc_by_function(line,len) == True){
        uint8_t command = line[1];
        uint8_t id = line[2];
        rmd_write_respone_command(id,command);
        serial_write('a');
        return True;
    }
    else{
        return False;
    }
}