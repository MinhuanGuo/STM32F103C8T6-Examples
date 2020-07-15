#ifndef __BLDC_MOTOR_H
#define __BLDC_MOTOR_H


#include "stm32f1xx_hal.h"
#include "tim.h"
#include "gpio.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>



#define TIM1_PERIOD_DEFAULT 3600


namespace MH_Hardware{
	
	class _bldc_motor{
		private:
			TIM_HandleTypeDef *_tim1_handle;
			TIM_OC_InitTypeDef     sPWMConfig1,sPWMConfig2,sPWMConfig3;

			uint8_t _pwmPercent;//20~80：表示PWM可调占空比在20%~80%之间
			uint8_t _hallStep;//Hall传感器的值
			uint16_t _hallStepCount;//Hall传感器更新次数累加值，固定时间读取并清零
			float _rpm;			//转速(转/分钟)
			bool _isEnable; //True:运行；False：停机
			bool _isClockWise; //True:顺时针，False：逆时针

		
			void setBLDC_Phase1(uint8_t pwmPercent);//B+ C-
			void setBLDC_Phase2(uint8_t pwmPercent);//A+ B-
			void setBLDC_Phase3(uint8_t pwmPercent);//A+ C-
			void setBLDC_Phase4(uint8_t pwmPercent);//A- C+
			void setBLDC_Phase5(uint8_t pwmPercent);//B+ A-
			void setBLDC_Phase6(uint8_t pwmPercent);//B- C+
			void BLDC_PHASE_CHANGE(uint8_t hallStep, uint8_t pwmPercent);
		
		public:		
			_bldc_motor(uint8_t hall);//构造函数，初始化		
			void enableRun(bool isRUN);//启动or停止
			void setClockWise(bool isCW);//顺时针or逆时针
			void updatePWMD(uint8_t userPWMPercent);//更新PWM占空比	
			void setSpeed();//PWM占空比生效，转变为转速
			uint16_t getPWMD();//获取PWM占空比
		
			void updateHallValue(void);//更新 Hall的值：
			uint8_t getHallValue(void);//返回 Hall的值：
		
		  uint16_t getHallCount(void);//返回 Hall变化累加值
			void clearHallCount(void);
			bool getDir(void);
			void calculateRPM(uint16_t delayMS);
			float getRPM(void);
	};

	
}







#endif
