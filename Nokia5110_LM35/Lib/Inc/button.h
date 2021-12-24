
#ifndef BUTTON_H_
#define BUTTON_H_
#include "config.h"

typedef enum BUTTON {
    NONE_bt         = -1,
    UP_bt           = 0,
    MAIN_bt         = 1,
    DOWN_bt         = 2
} But;

extern void button_init(void);
extern But button_get(void);

#endif