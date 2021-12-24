#include "../Inc/ds1307.h"

extern int cvt_num_r(uint8_t num){
    int one_n = num&0x0f;
    int ten_n = (num>>4)&0x0f;
    return (ten_n*10 + one_n);
}

extern int cvt_hou_r(uint8_t hou){
    uint8_t dec_hou = (hou)&0x0f;
    uint8_t nibble = (hou>>4)&0x0f;
    // 12h
    if(((hou>>6)&0x01) == 1){
        int ap_m = (hou>>5)&0x01;
        int ten = (hou>>4)&0x01;
        return (12*ap_m+ten*10+dec_hou);
    }
    // 24h
    return (10*nibble+dec_hou);
}

extern void ds1307_init(void){
    i2c_init();
}

extern void ds1307_put(uint8_t add,uint8_t dat){
    i2c_start();
	i2c_put(DS1307_WRI);
	i2c_put(add);
	i2c_put(dat);
	i2c_stop();
}

extern void ds1307_setime(uint8_t hou, uint8_t min, uint8_t sec){
    i2c_start();
	i2c_put(DS1307_WRI);
	i2c_put(DS1307_SEC);
	i2c_put(sec);
	i2c_put(min);
	i2c_put(hou);
	i2c_stop();    
}

extern void ds1307_setdate(uint8_t yea, uint8_t mon, uint8_t day, uint8_t wek){
    i2c_start();
	i2c_put(DS1307_WRI);
	i2c_put(DS1307_WEK);
	i2c_put(wek);
	i2c_put(day);
	i2c_put(mon);
	i2c_put(yea);
	i2c_stop();
}

extern uint8_t ds1307_get(uint8_t add){
    uint8_t dat;
	i2c_start();
	i2c_put(DS1307_WRI);
	i2c_put(add);
    i2c_start();
	
	i2c_put(DS1307_REA);
	dat = i2c_get(1);
	i2c_stop();
	return dat;
}

extern void ds1307_getime(uint8_t* hou, uint8_t* min, uint8_t* sec){
    i2c_start();
	i2c_put(DS1307_WRI);
	i2c_put(DS1307_SEC);
	i2c_start();
	
	i2c_put(DS1307_REA);
	*sec = i2c_get(0);
	*min = i2c_get(0); 
	*hou = i2c_get(1);
    
	i2c_stop();
}

extern void ds1307_getdate(uint8_t* yea, uint8_t* mon, uint8_t* day, uint8_t* wek){
    i2c_start();
	i2c_put(DS1307_WRI);
	i2c_put(DS1307_WEK);
    i2c_start();
    
	i2c_put(DS1307_REA);
    *wek = i2c_get(0);
	*day = i2c_get(0);
	*mon = i2c_get(0); 
	*yea = i2c_get(1);
    
	i2c_stop();
}

//void mlcd4_time(uint8_t hou, uint8_t min, uint8_t sec){
//    char num[2];
//    mlcd4_cursor(0,6);      
    
//	sprintf(num,"%2d",cvt_hou_r(hou)); 
//    mlcd4_puts(num);    
//	mlcd4_put('-');  
    
//	sprintf(num,"%2d",cvt_num_r(min));  
//    mlcd4_puts(num);
//	mlcd4_put('-'); 
      
//	sprintf(num,"%2d",cvt_num_r(sec)); 
//    mlcd4_puts(num);
//}

// void mlcd4_date(uint8_t yea, uint8_t mon, uint8_t dat, uint8_t wek){
    // char num[2];
    // mlcd4_cursor(1,2);
	// switch (wek){
		// case 0x01:{
			// mlcd4_puts("Su: ");
			// break;
		// }
		// case 0x02:{
			// mlcd4_puts("Mo: ");
			// break;
		// }
		// case 0x03:{
			// mlcd4_puts("Tu: ");
			// break;
		// }
		// case 0x04:{
			// mlcd4_puts("We: ");
			// break;
		// }
		// case 0x05:{
			// mlcd4_puts("Th: ");
			// break;
		// }
		// case 0x06:{
			// mlcd4_puts("Fr: ");
			// break;
		// }
		// case 0x07:{
			// mlcd4_puts("Su: ");
			// break;
		// }
		// default:{
			// break;
		// }
	// }
    
    // sprintf(num,"%2d",cvt_num_r(dat)); 
    // mlcd4_puts(num);
	// mlcd4_put('/'); 
    
	// sprintf(num,"%2d",cvt_num_r(mon)); 
    // mlcd4_puts(num);
	// mlcd4_put('/');
    
	// sprintf(num,"%2d",cvt_num_r(yea)); 
    // mlcd4_puts(num);
// }


extern void ds1307_sout_level(level status){
    uint8_t control_register = 0x00;
    switch (status)
    {
    case HIGH:{
        control_register &= ~(1<<SQW);
        control_register |= (1<<OUT);
        ds1307_put(DS1307_CONTROL,control_register);
        break;
    }
    default:
        control_register &= ~(1<<SQW);
        control_register &= ~(1<<OUT);
        ds1307_put(DS1307_CONTROL,control_register);
        break;
    }
}

extern void ds1307_sout_pluse(WIDTH_PLUSE width){
    uint8_t control_register = 0x00;
    control_register = ds1307_get(DS1307_CONTROL);
    switch (width)
    {
    case PLUSE_1_Hz:{
        control_register |= (1<<SQW);
        control_register |= PLUSE_1_Hz;
        ds1307_put(DS1307_CONTROL,control_register);
        break;
    }
    case PLUSE_8192_Hz:{
        control_register |= (1<<SQW);
        control_register |= PLUSE_8192_Hz;
        ds1307_put(DS1307_CONTROL,control_register);
        break;
    }
    case PLUSE_4096_Hz:{
        control_register |= (1<<SQW);
        control_register |= PLUSE_4096_Hz;
        ds1307_put(DS1307_CONTROL,control_register);
        break;
    }
    case PLUSE_32768_Hz:{
        control_register |= (1<<SQW);
        control_register |= PLUSE_32768_Hz;
        ds1307_put(DS1307_CONTROL,control_register);
        break;
    }
    default:
        break;
    }
}