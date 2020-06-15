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
	HAL_TIM_Encoder_Start(&htim2, TIM_CHANNEL_ALL);//��������ʼ��
	
	
	/*##-1- Start the TIM Base generation in interrupt mode ####################*/
  HAL_TIM_Base_Start_IT(&htim4);//��ͨ��ʱ����ʼ��
	
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
		
	//���ڷ������ݣ���������ֵ��PWM�Ŀ��
		sprintf(res,"%d,%d\r\n",enc_tim2,PWM_Width_Out);
		HAL_UART_Transmit(&huart2,(uint8_t*)res,std::strlen(res),10);	
		
		HAL_GPIO_TogglePin(LED0_GPIO_Port,LED0_Pin);
		HAL_Delay(50);
}

////////////////
void user_Timer_fun()
{
	//100Hz����ȡTim2��ת�����������룬��Χ��0~100
		enc_tim2 = (uint32_t)(__HAL_TIM_GET_COUNTER(&htim2));//��ȡ��������ֵ��0~100
		PWM_Width_Out = enc_tim2*4; //PWM����0~400��
	//�ö����ı�����ֵ���趨PWM��������LED�������ȡ�
		setPWM(htim3, TIM_CHANNEL_4, 999, (int)PWM_Width_Out); //TIM3_CH4��PWM�����1KHz
		/* Toggle LED */								
}
