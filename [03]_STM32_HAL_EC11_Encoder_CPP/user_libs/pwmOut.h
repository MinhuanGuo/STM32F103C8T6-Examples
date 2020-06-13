#ifndef PWM_OUT_H
#define PWM_OUT_H

#include "tim.h"

void setPWM(TIM_HandleTypeDef timer, uint32_t channel, uint16_t period,uint16_t pulse);



#endif
