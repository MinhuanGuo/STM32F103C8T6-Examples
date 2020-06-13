#include "main.h"
#include "usart.h"
#include "gpio.h"
#include "pwmOut.h"
#include <string.h>
#include	<stdlib.h>
#include	<stdio.h>
#include <math.h>

////////////////
void user_setup()
{
	HAL_Delay(1000);
	HAL_TIM_Encoder_Start(&htim2, TIM_CHANNEL_ALL);//编码器初始化
	
	
	/*##-1- Start the TIM Base generation in interrupt mode ####################*/
  HAL_TIM_Base_Start_IT(&htim4);//普通定时器初始化
	
	HAL_GPIO_WritePin(LED0_GPIO_Port,LED0_Pin,GPIO_PIN_SET);

	{
		HAL_GPIO_WritePin(LED0_GPIO_Port,LED0_Pin,GPIO_PIN_RESET);
		HAL_Delay(100);
		HAL_GPIO_WritePin(LED0_GPIO_Port,LED0_Pin,GPIO_PIN_SET);
		HAL_Delay(100);
	}
}


////////////////
void user_loop()
{
		static uint32_t enc1;
		enc1 = (uint32_t)(__HAL_TIM_GET_COUNTER(&htim2));//获取编码器的值：0~100
	
	
		static char res[10];
		static int out=0.0f;
		out = enc1 * 4; //PWM脉宽：0~400；
	  
		sprintf(res,"%d\r\n",out);
		HAL_UART_Transmit(&huart2,(uint8_t*)res,std::strlen(res),10);	
		
		
	  setPWM(htim3, TIM_CHANNEL_4, 999, (int)out); //TIM3_CH4：PWM输出，1KHz
	
		HAL_Delay(5);
}

////////////////
void user_Timer_fun()
{
	
		/* Toggle LED */				
					
}
