
#ifndef STYLE_H_
#define STYLE_H_

#define SET(PORT,PIN)                               (PORT |= (1<<PIN))
#define CLR(PORT,PIN)                               (PORT &= ~(1<<PIN))
#define WRITE(PORT,PIN,S)                           (S==1 ? SET(PORT,PIN): CLR(PORT,PIN))  
#define READ(PORT,PIN)                              ((PORT&(1<<PIN))==0x00 ? 0:1)
#define TOGGLE(PORT,PIN)                            ((PORT) ^=(1<<PIN))
#define BV(PIN)                                     (1<<PIN)
#define set_output(POTR,PIN)                        SET(PORT,PIN)
#define set_input(POTR,PIN)                         CLR(PORT,PIN)

typedef signed              char    	            int8_t;
typedef signed              int     	            int16_t;
typedef signed long         int    		            int32_t;
typedef unsigned            char    	            uint8_t;
typedef unsigned 			int			            uint16_t;
typedef unsigned long		int			            uint32_t;
typedef float							            float32_t;
typedef enum                {Flase, True}           bool;
typedef enum                {OFF,ON}                flask;
typedef enum                {LOW,HIGH}              level;

#endif 