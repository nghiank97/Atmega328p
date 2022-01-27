
#include "elephant.h"

uint8_t line[LINE_BUFFER_SIZE];

extern void protocol_main_loop(void)
{
    uint8_t c;
    int char_counter = -1;
    uint8_t current_command = RMD_NONE_COMMEND;
    for (;;) {
        while ((c = serial_read()) != SERIAL_NO_DATA)
        {
            if ((c == RMD_HEADER) && (char_counter == -1)){
                char_counter = 0;
                line[char_counter++] = RMD_HEADER;
                continue;
            }
            else if (char_counter == -1){
                continue;
            }

            if (char_counter == 1){
                switch (c)
                {
                case RMD_START_COMMAND:
                    current_command = RMD_START_COMMAND;
                    line[char_counter++] = RMD_START_COMMAND;
                    break;
                case RMD_SPEED_LOOP_COMMAND:
                    current_command = RMD_SPEED_LOOP_COMMAND;
                    line[char_counter++] = RMD_SPEED_LOOP_COMMAND;
                    break;
                default:
                    break;
                }
                continue;
            }
            switch (current_command)
            {
                case RMD_START_COMMAND:{
                    if (char_counter < LENGHT_REQUEST_RMD_START_COMMAND){
                        line[char_counter++] = c;
                    }
                    if (char_counter == LENGHT_REQUEST_RMD_START_COMMAND){
                        line[char_counter] = 0;
                        rmd_excute_line(line,char_counter);
                        char_counter    =-1;
                        current_command = RMD_NONE_COMMEND;
                    }
                    break;
                }
                case RMD_SPEED_LOOP_COMMAND:{
                    if (char_counter < LENGHT_REQUEST_RMD_SPEED_LOOP_COMMAND){
                        line[char_counter++] = c;
                    }
                    if (char_counter == LENGHT_REQUEST_RMD_SPEED_LOOP_COMMAND){
                        line[char_counter] = 0;
                        rmd_excute_line(line,char_counter);
                        char_counter    =-1;
                        current_command = RMD_NONE_COMMEND;
                    }
                    break;
                }
                default:
                    break;
            }
        }
    }
}
