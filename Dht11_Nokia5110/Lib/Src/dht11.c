#include "../Inc/dht11.h"

extern void dht11_start(){  
    _set(DP_DIR,DP_DHT11);              // set output 
	_set(DP_PORT,DP_DHT11); 

	_clr(DP_PORT,DP_DHT11); 
	delay_ms(18);
	_set(DP_PORT,DP_DHT11);
	delay_us(40);

    _clr(DP_DIR,DP_DHT11);              // set input 
    while(_read(DP_PIN,DP_DHT11)==0);
    while(_read(DP_PIN,DP_DHT11)==1);
}

extern uint8_t dht11_read(void){
	int i;
	uint8_t data = 0;
    _clr(DP_DIR,DP_DHT11);
	for(i=0;i<8;i++){
		while(_read(DP_PIN,DP_DHT11)==0);
		delay_us(28);
		data<<=1; 
		if(_read(DP_PIN,DP_DHT11)==1){
			data|=0x01;
		}
		while(_read(DP_PIN,DP_DHT11)==1);
	}
	return data;
}

extern bool dht11_get(uint8_t* humi,uint8_t* part_humi,uint8_t* temp,uint8_t* part_temp,uint8_t* check_sum){
    dht11_start();
    *humi = dht11_read();
	*part_humi = dht11_read();
	*temp = dht11_read();
	*part_temp = dht11_read();
	*check_sum = dht11_read();
	if ((*humi+ *part_humi+ *temp+ *part_temp) != *check_sum){
        return False;
	}
    else{
        return True;
    }
}