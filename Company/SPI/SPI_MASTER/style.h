
#ifndef STYLE_H_
#define STYLE_H_

#define F_CPU                                       16000000UL

#define SET(PORT,PIN)                               (PORT |= (1<<PIN))
#define CLR(PORT,PIN)                               (PORT &= ~(1<<PIN))
#define WRITE(PORT,PIN,S)                           (S==1 ? SET(PORT,PIN): CLR(PORT,PIN))  
#define READ(PORT,PIN)                              ((PORT&(1<<PIN))==0x00 ? 0:1)
#define TOGGLE(PORT,PIN)                            ((PORT) ^=(1<<PIN))
#define BV(PIN)                                     (1<<PIN)
#define set_output(PORT,PIN)                        SET(PORT,PIN)
#define set_input(PORT,PIN)                         CLR(PORT,PIN)


// typedef signed              char    	            int8_t;
// typedef signed              int     	            int16_t;
// typedef signed long         int    		            int32_t;
// typedef unsigned            char    	            uint8_t;
// typedef uint8_t			                            byte;
// typedef unsigned 			int			            uint16_t;
// typedef uint16_t			                        word;
// typedef unsigned long		int			            uint32_t;
// typedef float							            float32_t;
typedef enum                {False, True}           bool;
typedef enum                {OFF,ON}                flask;
typedef enum                {LOW,HIGH}              level;

#define PI                                          M_PI

#endif