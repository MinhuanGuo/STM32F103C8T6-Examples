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
static char res[20];
static uint32_t enc_tim2 = 0;
static int PWM_Width_Out = 0;
void user_loop()
{
		
	//串口发送数据：编码器的值，PWM的宽度
		sprintf(res,"%d,%d\r\n",enc_tim2,PWM_Width_Out);
		HAL_UART_Transmit(&huart2,(uint8_t*)res,std::strlen(res),10);	
		
		HAL_GPIO_TogglePin(LED0_GPIO_Port,LED0_Pin);
		HAL_Delay(50);
}

////////////////
void user_Timer_fun()
{
	//100Hz，读取Tim2旋转编码器的输入，范围：0~100
		enc_tim2 = (uint32_t)(__HAL_TIM_GET_COUNTER(&htim2));//获取编码器的值：0~100
		PWM_Width_Out = enc_tim2*4; //PWM脉宽：0~400；
	//用读到的编码器值，设定PWM脉宽，调节LED的明暗度。
		setPWM(htim3, TIM_CHANNEL_4, 999, (int)PWM_Width_Out); //TIM3_CH4：PWM输出，1KHz
		/* Toggle LED */								
}
