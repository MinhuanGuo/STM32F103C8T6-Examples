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

			uint8_t _pwmPercent;//20~80����ʾPWM�ɵ�ռ�ձ���20%~80%֮��
			uint8_t _hallStep;//Hall��������ֵ
			uint16_t _hallStepCount;//Hall���������´����ۼ�ֵ���̶�ʱ���ȡ������
			float _rpm;			//ת��(ת/����)
			bool _isEnable; //True:���У�False��ͣ��
			bool _isClockWise; //True:˳ʱ�룬False����ʱ��

		
			void setBLDC_Phase1(uint8_t pwmPercent);//B+ C-
			void setBLDC_Phase2(uint8_t pwmPercent);//A+ B-
			void setBLDC_Phase3(uint8_t pwmPercent);//A+ C-
			void setBLDC_Phase4(uint8_t pwmPercent);//A- C+
			void setBLDC_Phase5(uint8_t pwmPercent);//B+ A-
			void setBLDC_Phase6(uint8_t pwmPercent);//B- C+
			void BLDC_PHASE_CHANGE(uint8_t hallStep, uint8_t pwmPercent);
		
		public:		
			_bldc_motor(uint8_t hall);//���캯������ʼ��		
			void enableRun(bool isRUN);//����orֹͣ
			void setClockWise(bool isCW);//˳ʱ��or��ʱ��
			void updatePWMD(uint8_t userPWMPercent);//����PWMռ�ձ�	
			void setSpeed();//PWMռ�ձ���Ч��ת��Ϊת��
			uint16_t getPWMD();//��ȡPWMռ�ձ�
		
			void updateHallValue(void);//���� Hall��ֵ��
			uint8_t getHallValue(void);//���� Hall��ֵ��
		
		  uint16_t getHallCount(void);//���� Hall�仯�ۼ�ֵ
			void clearHallCount(void);
			bool getDir(void);
			void calculateRPM(uint16_t delayMS);
			float getRPM(void);
	};

	
}







#endif
