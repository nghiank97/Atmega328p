
#include "Lib/Inc/config.h"
#include "Lib/Inc/ssd1306.h"
#include "Lib/Inc/logo.h"
#include "Lib/Inc/eint.h"
#include "Lib/Inc/adc.h"

static void ssd1306_load_slide(uint8_t value,enum SIGNAL color){
    ssd1306_line(25,value,29,value,color);
}

static void ssd1306_main(void){
    ssd1306_clear_display();
    ssd1306_print_stringXY("Main Page",0,0,NORMAL);
    ssd1306_print_string_4x6_XY("ROTARY CONTROL ON MENU",2,0,NORMAL);
    
    ssd1306_box(24,0,30,127,ON_PIXEL);
    
    ssd1306_line(42,0,42,127,ON_PIXEL);
    ssd1306_box_fill(46,0,55,26,ON_PIXEL);
    ssd1306_print_stringXY("MAIN",6,2,INVERT);
    ssd1306_print_stringXY("NETWORK",6,40,NORMAL);
    ssd1306_print_stringXY("SETUP",6,96,NORMAL);
}

static void ssd1306_begin(void){
    ssd1306_init();
	ssd1306_logo(mylogo,NORMAL);
    delay_ms(1000);
    ssd1306_main();
}

int origin_local_main = 0;
int local_main = 0;
uint16_t adc_value = 0;
int slide_value = 0;
int past_slide_value = 0;
char text_adc_value[5];
int go_out = 0;

bool check_main_page = False;
bool check_setup_page = False;
bool check_network_page = False;
bool check_run_main_page = True;

int local_setup_page = 0;
enum LOCAL_SETUP_PAGE{
    EXIT = 0,
    PID_VALUE = 1,
    VERSION_INFO = 2,
};


#define MAIN_PAGE       0
#define NETWORK_PAGE    1
#define SETUP_PAGE      2

static void reload_glcd(int local,int dir){
    switch (local){
        case MAIN_PAGE:{
            if (dir == 1){
                ssd1306_box(46,94,55,127,OFF_PIXEL);
                ssd1306_box(46,0,55,26,ON_PIXEL);
            }
            else{
                ssd1306_box(46,0,55,26,ON_PIXEL);
                ssd1306_box(46,38,55,82,OFF_PIXEL);
            }
            break;
        }
        case NETWORK_PAGE:{
            if (dir == 1){
                ssd1306_box(46,0,55,26,OFF_PIXEL);
                ssd1306_box(46,38,55,82,ON_PIXEL);
            }
            else{
                ssd1306_box(46,38,55,82,ON_PIXEL);
                ssd1306_box(46,94,55,127,OFF_PIXEL);
            }
            break;
        }
        case SETUP_PAGE:{
            if (dir == 1){
                ssd1306_box(46,38,55,82,OFF_PIXEL);
                ssd1306_box(46,94,55,127,ON_PIXEL);
            }
            else{
                ssd1306_box(46,0,55,26,OFF_PIXEL);
                ssd1306_box(46,94,55,127,ON_PIXEL);
            }
            break;
        }
        default:
            break;
    }
}

static void reload_setup_page(int local){
    switch (local){
        case EXIT:{
            ssd1306_clear_display();
            ssd1306_line(20,0,20,127,ON_PIXEL);
            ssd1306_box_fill(6,50,16,76,ON_PIXEL);
            ssd1306_print_stringXY("EXIT",1,52,INVERT);

            ssd1306_print_string_4x6_XY("DEMO MODE",3,0,NORMAL);
            ssd1306_print_string_4x6_XY("PRESS BUTTON TO EXIT",4,0,NORMAL);

            ssd1306_load_arrow(1,122,RIGHT_ARROW,ON_PIXEL);
            ssd1306_line(60,0,60,127,ON_PIXEL);
            break;
        }
        case PID_VALUE:{
            ssd1306_clear_display();
            ssd1306_box_fill(6,30,16,88,ON_PIXEL);
            ssd1306_line(20,0,20,127,ON_PIXEL);
            ssd1306_print_stringXY("PID VALUE",1,32,INVERT);

            ssd1306_print_string_4x6_XY("Kp : 0000",4,40,NORMAL);
            ssd1306_print_string_4x6_XY("Ki : 0000",5,40,NORMAL);
            ssd1306_print_string_4x6_XY("Kd : 0000",6,40,NORMAL);

            ssd1306_load_arrow(1,0,LEFT_ARROW,ON_PIXEL);
            ssd1306_load_arrow(1,122,RIGHT_ARROW,ON_PIXEL);
            ssd1306_line(60,0,60,127,ON_PIXEL);
            break;
        }
        case VERSION_INFO:{
            ssd1306_clear_display();
            ssd1306_line(20,0,20,127,ON_PIXEL);
            ssd1306_box_fill(6,12,16,102,ON_PIXEL);
            ssd1306_print_stringXY("VERSION & INFO",1,14,INVERT);

            ssd1306_print_string_4x6_XY("OLED MANU PAGE BEE",3,0,NORMAL);
            ssd1306_print_string_4x6_XY("Author  : Nghia",4,0,NORMAL);
            ssd1306_print_string_4x6_XY("Version : 0.1",6,0,NORMAL);

            ssd1306_load_arrow(1,0,LEFT_ARROW,ON_PIXEL);
            ssd1306_line(60,0,60,127,ON_PIXEL);
            break;
        }
        default:
            break;
    }
}

ISR(INT0_vect){
    if (check_run_main_page == True){
        local_main+=1;
        local_main = (local_main>2)?0:local_main;
        reload_glcd(local_main,1);
    }
    if (check_setup_page == True){
        local_setup_page+=1;
        local_setup_page = (local_setup_page>2)?2:local_setup_page;
        reload_setup_page(local_setup_page);
    }
}

ISR(INT1_vect){
    if (check_run_main_page == True){
        local_main-=1;
        local_main = (local_main<0)?2:local_main;
        reload_glcd(local_main,0);
    }
    if (check_setup_page == True){
        local_setup_page-=1;
        local_setup_page = (local_setup_page<0)?0:local_setup_page;
        reload_setup_page(local_setup_page);
    }
}

ISR (TIMER1_OVF_vect){

    if (check_network_page == True){
        if ((past_slide_value == 0) || (past_slide_value == 127)){
            ssd1306_load_slide(past_slide_value,ON_PIXEL);
        }
        else{
            ssd1306_load_slide(past_slide_value,OFF_PIXEL);
        }
        adc_value = adc_get(CHANNEL_0);
        slide_value = (int)adc_value/8;
        ssd1306_load_slide(slide_value,ON_PIXEL);

        sprintf(text_adc_value,"%4d",adc_value);
        ssd1306_print_stringXY(text_adc_value,5,35,NORMAL);
        past_slide_value = slide_value;
    }
    RESET_TIMER_1();
}

int main(void){
    CONFIG_CLOCK();

    ssd1306_begin();
    eint_init();
    adc_init();

    while(1){
        if (_read(PIN_BT,MAIN_BT) == 0){
            delay_ms(100);
            if (_read(PIN_BT,MAIN_BT) == 0){
                if (origin_local_main == local_main){
                    switch (origin_local_main){
                        case MAIN_PAGE:{
                            if (go_out == 0){
                                
                                check_main_page = True;
                                check_network_page = False;  
                                check_setup_page = False;  
                                check_run_main_page = False;

                                ssd1306_scrool(5,10);
                                go_out = 1;
                                break;
                            }
                            else{
                                check_main_page = False;
                                check_network_page = False;  
                                check_setup_page = False;
                                check_run_main_page = True;

                                ssd1306_clear_row(5);
                                ssd1306_clear_row(6);
                                ssd1306_clear_row(7);

                                ssd1306_line(42,0,42,127,ON_PIXEL);
                                ssd1306_box_fill(46,0,55,26,ON_PIXEL);
                                ssd1306_print_stringXY("MAIN",6,2,INVERT);
                                ssd1306_print_stringXY("NETWORK",6,40,NORMAL);
                                ssd1306_print_stringXY("SETUP",6,96,NORMAL);
                                go_out = 0;
                                break;
                            }
                        }
                        case NETWORK_PAGE:{
                            if (go_out == 0){
                                ssd1306_scrool(5,10);
                                ssd1306_print_stringXY("Value 0",5,0,NORMAL);
                                
                                check_main_page = False;
                                check_network_page = True;  
                                check_setup_page = False;
                                check_run_main_page = False;

                                go_out = 1;
                                break;
                            }
                            else{
                                check_main_page = False;
                                check_network_page = False;  
                                check_setup_page = False;    
                                check_run_main_page = True;

                                ssd1306_clear_row(3);
                                ssd1306_clear_row(5);
                                ssd1306_clear_row(6);
                                ssd1306_clear_row(7);

                                ssd1306_box(24,0,30,127,ON_PIXEL);

                                ssd1306_line(42,0,42,127,ON_PIXEL);
                                ssd1306_print_stringXY("MAIN",6,2,NORMAL);
                                ssd1306_box_fill(46,38,55,82,ON_PIXEL);
                                ssd1306_print_stringXY("NETWORK",6,40,INVERT);
                                ssd1306_print_stringXY("SETUP",6,96,NORMAL);
                                go_out = 0;
                                break;
                            }
                        }
                        case SETUP_PAGE:{
                            if (go_out == 0){
                                check_main_page = False;
                                check_network_page = False;  
                                check_setup_page = True;    
                                check_run_main_page = False;

                                local_setup_page = EXIT;
                                reload_setup_page(0);
                                go_out = 1;
                                break;
                            }
                            else{
                                check_main_page = False;
                                check_network_page = False;  
                                check_setup_page = False; 
                                check_run_main_page = True;

                                ssd1306_clear_display();
                                ssd1306_print_stringXY("Setup Page  ",0,0,NORMAL);
                                ssd1306_print_string_4x6_XY("PRESS BUTTON FOR SUBMENU",2,0,NORMAL);
                                ssd1306_line(42,0,42,127,ON_PIXEL);
                                ssd1306_print_stringXY("MAIN",6,2,NORMAL);
                                ssd1306_print_stringXY("NETWORK",6,40,NORMAL);
                                ssd1306_box_fill(46,94,55,127,ON_PIXEL);
                                ssd1306_print_stringXY("SETUP",6,96,INVERT);
                                go_out = 0;
                                break;
                            }
                        }
                        default:
                            break;
                    }
                }
                else{
                    switch (origin_local_main){
                        case MAIN_PAGE:{
                            ssd1306_box_fill(46,0,55,26,OFF_PIXEL);
                            ssd1306_print_stringXY("MAIN",6,2,NORMAL);
                            break;
                        }
                        case NETWORK_PAGE:{
                            ssd1306_box_fill(46,38,55,82,OFF_PIXEL);
                            ssd1306_print_stringXY("NETWORK",6,40,NORMAL);
                            break;
                        }
                        case SETUP_PAGE:{
                            ssd1306_box_fill(46,94,55,127,OFF_PIXEL);
                            ssd1306_print_stringXY("SETUP",6,96,NORMAL);
                            break;
                        }
                        default:
                            break;
                    }
                    switch (local_main){
                        case MAIN_PAGE:{
                            ssd1306_print_stringXY("Main Page   ",0,0,NORMAL);
                            ssd1306_print_string_4x6_XY("ROTARY CONTROL ON MENU",2,0,NORMAL);
                            ssd1306_box(24,0,30,127,ON_PIXEL);
                            ssd1306_box_fill(46,0,55,26,ON_PIXEL);
                            ssd1306_print_stringXY("MAIN",6,2,INVERT);
                            break;
                        }
                        case NETWORK_PAGE:{
                            ssd1306_print_stringXY("Network Page",0,0,NORMAL);
                            ssd1306_print_string_4x6_XY("ROTARY CONTROL ON MENU",2,0,NORMAL);
                            ssd1306_box(24,0,30,127,ON_PIXEL);
                            ssd1306_box_fill(46,38,55,82,ON_PIXEL);
                            ssd1306_print_stringXY("NETWORK",6,40,INVERT);
                            break;
                        }
                        case SETUP_PAGE:{
                            ssd1306_print_stringXY("Setup Page  ",0,0,NORMAL);
                            ssd1306_print_string_4x6_XY("PRESS BUTTON FOR SUBMENU",2,0,NORMAL);
                            ssd1306_clear_row(3);
                            ssd1306_box_fill(46,94,55,127,ON_PIXEL);
                            ssd1306_print_stringXY("SETUP",6,96,INVERT);
                            break;
                        }
                        default:
                            break;
                    }
                origin_local_main = local_main;
                }
            }
        }
    }
    return 0;
}