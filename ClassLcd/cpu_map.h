
#ifndef DEFINE_H_
#define DEFINE_H_

/* LCD */

#define LCD16x4

#define RS_LCD                                      0
//#define RW_LCD                                      1
#define EN_LCD                                      1
#define PORT_CONTROL_LCD                            PORTB
#define DIR_CONTROL_LCD                             DDRB

#define FIR_LCD                                     2
#define SEC_LCD                                     3
#define THI_LCD                                     4
#define FOR_LCD                                     5
#define PORT_DATA_LCD                               PORTB
#define DIR_DATA_LCD                                DDRB

#endif