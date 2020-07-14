#ifndef __GPIO_KEY_H
#define __GPIO_KEY_H

#include "stm32f1xx_hal.h"
#include "bldc_motor.h"
#include "tim.h"
#include "gpio.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>



#define KEYUP		0L
#define KEYDOWN		1L

#define KEYNUMBER	2
#define LIMITCOUNT_VALUE	20
#define MAXCOUNT_VALUE		50

#define KEY1_PRESSED  (HAL_GPIO_ReadPin(Encoder_Key_GPIO_Port,Encoder_Key_Pin)==GPIO_PIN_RESET)
#define KEY2_PRESSED 0

namespace MH_Hardware{
	
	class _gpio_key{
		private:
			unsigned long _KeyFlag;//�̰���־
			unsigned long _KeyFlagLongPressed;//������־
			unsigned short _KeyCount[KEYNUMBER];
			//ɨ��GPIO״̬�����ر����°�������ţ�������0��ʾû�а���������
			unsigned char GetKeyValue(void);
		
		public:
			_gpio_key(unsigned long KeyFlag);	
			//����_KeyFlag��_KeyCount;
			void scan(void);	
			//��ѯ�����ذ���״̬��Ϣ
			unsigned char GetKeyStatus(unsigned char KeyNumber);

			
	};
}


#endif
