#ifndef __GLOBAL_H
#define __GLOBAL_H

#include "stm32f1xx_hal.h"
#include "tim.h"
#include "gpio.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

//typedef volatile unsigned char  vu8;        ///< Define 8-bit unsigned volatile data type
//typedef volatile unsigned short vu16;       ///< Define 16-bit unsigned volatile data type
//typedef volatile unsigned long  vu32;       ///< Define 32-bit unsigned volatile data type

uint32_t get_tick_delay(uint32_t last_tick);
uint16_t floatToInt(float f);


#endif
