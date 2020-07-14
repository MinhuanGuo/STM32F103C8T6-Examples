#ifndef PWM_OUT_H
#define PWM_OUT_H

#include "tim.h"

typedef struct _BLDC
{
	int step_counter;
	int stalling_count;
}BLDC;

extern TIM_OC_InitTypeDef     sPWMConfig1,sPWMConfig2,sPWMConfig3;
void setPWM(TIM_HandleTypeDef timer, uint32_t channel, uint16_t period,uint16_t pulse);
void setUVW_PWM(uint16_t period,uint16_t pulseU,uint16_t pulseV,uint16_t pulseW);


void setBLDC_Phase1(uint16_t pulseU, uint16_t pulseV, uint16_t pulseW);
void setBLDC_Phase2(uint16_t pulseU, uint16_t pulseV, uint16_t pulseW);
void setBLDC_Phase3(uint16_t pulseU, uint16_t pulseV, uint16_t pulseW);
void setBLDC_Phase4(uint16_t pulseU, uint16_t pulseV, uint16_t pulseW);
void setBLDC_Phase5(uint16_t pulseU, uint16_t pulseV, uint16_t pulseW);
void setBLDC_Phase6(uint16_t pulseU, uint16_t pulseV, uint16_t pulseW);

void stopBLDC(void);


#endif

