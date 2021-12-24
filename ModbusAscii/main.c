/*
 * main.c
 *
 * Created: 2/10/2020 7:41:10 PM
 * Author: khacnghia
 */
#include "Lib/Inc/config.h"
#include "Lib/Inc/modbus_ascii.h"
#include "Lib/Inc/adc.h"
#include "Lib/Inc/lcd4.h"

uint16_t temp_1,temp_2,temp_3,temp_4;
char temp_txt[4];

uint8_t input_0=1,input_1=1;
uint8_t led_0=0,led_1=0,led_2=0,led_3=0;

uint8_t frame_1[4] = {MODBUS_ADDRESS, MODBUS_FUNC_01, 0x01, 0x00};

uint8_t frame_2[4] = {MODBUS_ADDRESS, MODBUS_FUNC_02, 0x01, 0x00};

uint8_t frame_3[11] = {MODBUS_ADDRESS, MODBUS_FUNC_03, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

uint8_t frame_5[6] = {MODBUS_ADDRESS, MODBUS_FUNC_05, 0x00, 0x00, 0x00, 0x00};

int local = -1;
char ascii_data[30];

void mma_function_05(uint8_t address,uint8_t value){
    int status = value==0xff? 1:0;
    switch (address){
        case 0x00:{
            led_0 = status;
            _write(PORT_COIL,COIL_0,status);
            break;
        }
        case 0x01:{
            led_1 = status;
            _write(PORT_COIL,COIL_1,status);
            break;
        }
        case 0x02:{
            led_2 = status;
            _write(PORT_COIL,COIL_2,status);
            break;
        }
        case 0x03:{
            led_3 = status;
            _write(PORT_COIL,COIL_3,status);
            break;
        }
        default:
            break;
    }
}

void mma_handling(char frame_data[],int len){
    char add_mb = merge_to_hex(frame_data[0],frame_data[1]);
    char func = merge_to_hex(frame_data[2],frame_data[3]);
    if (add_mb != MODBUS_ADDRESS){
        return;
    }
    switch (func){
        case 0x01:{
            mma_put(frame_1,4);
            break;
        }
        case 0x02:{
            mma_put(frame_2,4);
            break;
        }
        case 0x03:{
            mma_put(frame_3,11);
            break;
        }
        case 0x05:{
            uint8_t add = merge_to_hex(frame_data[6],frame_data[7]);
            uint8_t value = merge_to_hex(frame_data[8],frame_data[9]);
            frame_5[3] = add;
            frame_5[4] = value;
            mma_function_05(add,value);
            mma_put(frame_5,6);
            break;
        }
        default:
            break;
    }
}

ISR (USART_RX_vect){
    char data = UDR0;
    if ((data == ':') && (local == -1)) {
		local = 0;
        return;
	}
	if ((data != (char)(13)) && (local>=0)) {
		ascii_data[local] = data;
		local += 1;
	}
	if ((data == (char)13) && (local>=0)) {
		mma_handling(ascii_data,local);
		local = -1;
	}
}

static void gpio_init(void){
    DIR_COIL |= (1<<COIL_0)|(1<<COIL_1)|(1<<COIL_2)|(1<<COIL_3);
    DIR_BUTTON |= (0<<BUTTON_0)|(0<<BUTTON_1);
}

static void load_register_modbus(void){
    frame_3[3] = temp_1>>8;
    frame_3[4] = temp_1&0xff;

    frame_3[5] = temp_2>>8;
    frame_3[6] = temp_2&0xff;

    frame_3[7] = temp_3>>8;
    frame_3[8] = temp_3&0xff;

    frame_3[9] = temp_4>>8;
    frame_3[10] = temp_4&0xff;

    frame_1[3] = (led_0<<COIL_0)|(led_1<<COIL_1)|(led_2<<COIL_2)|(led_3<<COIL_3);
    frame_2[3] = (input_0<<0)|(input_1<<1);
}

int main(void)
{
    CONFIG_CLOCK();

    lcd4_init();
    lcd4_printf(0,0,"Vol 0: "); 
    lcd4_printf(1,0,"Vol 1: ");
    lcd4_printf(2,0,"Vol 2: ");
    lcd4_printf(3,0,"Vol 3: ");

    gpio_init();
    adc_init();
    serial_init(1);
    
	while (1){ 

        input_0 = _read(PIN_BUTTON,BUTTON_0);
        input_1 = _read(PIN_BUTTON,BUTTON_1);

        temp_1 = adc_get(CHANNEL_0);
        sprintf(temp_txt,"%d",temp_1);
        lcd4_printf(0,7,temp_txt); 
        delay_ms(10); 
        
        temp_2 = adc_get(CHANNEL_1);
        sprintf(temp_txt,"%d",temp_2);
        lcd4_printf(1,7,temp_txt);
        delay_ms(10);
        
        temp_3 = adc_get(CHANNEL_2);
        sprintf(temp_txt,"%d",temp_3);
        lcd4_printf(2,7,temp_txt);
        delay_ms(10);
        
        temp_4 = adc_get(CHANNEL_3);
        sprintf(temp_txt,"%d",temp_4);
        lcd4_printf(3,7,temp_txt);
        delay_ms(10);

        load_register_modbus();
	}
}
