#include "exti.h"
#include "led.h"
#include "key.h"
#include "delay.h"
#include "usart.h"
#include "includes.h"
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK��ӢSTM32������
//�ⲿ�ж� ��������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2012/9/3
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2009-2019
//All rights reserved									  
//////////////////////////////////////////////////////////////////////////////////   
//�ⲿ�ж�0�������
void EXTIX_Init(void)
{
	EXTI_InitTypeDef EXTI_InitStructure_LINE1;
	EXTI_InitTypeDef EXTI_InitStructure_LINE2;
 	NVIC_InitTypeDef NVIC_InitStructure;

  	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);	//ʹ�ܸ��ù���ʱ��
	
	//GPIOA.1,2�������������غ��½����жϣ�
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource1); 
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource2); 
	
	/* Configure EXTI Line1 to generate aninterrupt on Rising_Falling edge */
	EXTI_InitStructure_LINE1.EXTI_Line=EXTI_Line1;
	EXTI_InitStructure_LINE1.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure_LINE1.EXTI_Trigger = EXTI_Trigger_Rising_Falling;
	EXTI_InitStructure_LINE1.EXTI_LineCmd=ENABLE; 
	EXTI_Init(&EXTI_InitStructure_LINE1);

	/* Configure EXTI Line2 to generate aninterrupt on Rising_Falling edge */
	EXTI_InitStructure_LINE2.EXTI_Line=EXTI_Line2;
	EXTI_InitStructure_LINE2.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure_LINE2.EXTI_Trigger = EXTI_Trigger_Rising_Falling;
	EXTI_InitStructure_LINE2.EXTI_LineCmd=ENABLE; 
	EXTI_Init(&EXTI_InitStructure_LINE2);
	
	/* ================ NVIC-EXTI-PORTE================= */
	/* Configure one bit for preemption priority*/
  	NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQn;			//ʹ�ܰ���WK_UP���ڵ��ⲿ�ж�ͨ��
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;	//��ռ���ȼ�2�� 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;					//�����ȼ�3
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//ʹ���ⲿ�ж�ͨ��
  	NVIC_Init(&NVIC_InitStructure); 
	
  	NVIC_InitStructure.NVIC_IRQChannel = EXTI2_IRQn;			//ʹ�ܰ���WK_UP���ڵ��ⲿ�ж�ͨ��
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;	//��ռ���ȼ�2�� 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;					//�����ȼ�3
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//ʹ���ⲿ�ж�ͨ��
  	NVIC_Init(&NVIC_InitStructure); 
}

//�ⲿ�ж�1������� 
void EXTI1_IRQHandler(void)
{
	OSIntEnter();
	//if(EXTI_GetITStatus(EXTI_Line1) == SET) // ��ȡ�ж�״̬
	{
		//delay_ms(10);//����
		LED = !LED;
		EXTI_ClearITPendingBit(EXTI_Line1); //���LINE0�ϵ��жϱ�־λ  
	}
	OSIntExit();
}
 

//�ⲿ�ж�2�������
void EXTI2_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line2) == SET) // ��ȡ�ж�״̬
	{
		delay_ms(10);//����
		if(1)	 	 //WK_UP����
		{				 
			;
		}
		EXTI_ClearITPendingBit(EXTI_Line2); //���LINE0�ϵ��жϱ�־λ  
	}
}
 
