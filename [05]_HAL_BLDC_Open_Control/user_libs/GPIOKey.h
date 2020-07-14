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
			unsigned long _KeyFlag;//短按标志
			unsigned long _KeyFlagLongPressed;//长按标志
			unsigned short _KeyCount[KEYNUMBER];
			//扫描GPIO状态，返回被按下按键的序号，若返回0表示没有按键被按下
			unsigned char GetKeyValue(void);
		
		public:
			_gpio_key(unsigned long KeyFlag);	
			//更新_KeyFlag，_KeyCount;
			void scan(void);	
			//查询并返回按键状态信息
			unsigned char GetKeyStatus(unsigned char KeyNumber);

			
	};
}


#endif
