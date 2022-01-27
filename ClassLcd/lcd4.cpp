
#include "squid.h"

LCD4::LCD4(int rs,int rw,int d4,int d5,int d6,int d7){
    set_input(PORT_CONTROL_LCD,RS_LCD);
    set_input(PORT_CONTROL_LCD,EN_LCD);

    set_output(PORT_CONTROL_LCD,D4_LCD);
    set_output(PORT_CONTROL_LCD,D5_LCD);
    set_output(PORT_CONTROL_LCD,D6_LCD);
    set_output(PORT_CONTROL_LCD,D7_LCD);
}


