
#ifndef ELEPHANT_H_
#define ELEPHANT_H_

#ifndef F_CPU                   
#define F_CPU                   16000000
#endif

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <math.h>

#include "style.h"
#include "config.h"
#include "i2c.h"
#include "serial.h"
#include "pcf8574.h"

#endif