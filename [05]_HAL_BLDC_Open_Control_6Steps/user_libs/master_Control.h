#ifndef __MASTER_CONTROL_H
#define __MASTER_CONTROL_H

#include "oled0561.h"
#include "bldc_motor.h"
#include "GPIOKey.h"
#include "stm32f1xx_hal.h"
#include "tim.h"
#include "gpio.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>




unsigned char GetKeyValue(void);


#endif
