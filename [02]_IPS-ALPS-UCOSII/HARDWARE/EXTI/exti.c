#include "exti.h"
#include "led.h"
#include "key.h"
#include "delay.h"
#include "usart.h"
#include "includes.h"
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK精英STM32开发板
//外部中断 驱动代码	   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//修改日期:2012/9/3
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2009-2019
//All rights reserved									  
//////////////////////////////////////////////////////////////////////////////////   
//外部中断0服务程序
void EXTIX_Init(void)
{
	EXTI_InitTypeDef EXTI_InitStructure_LINE1;
	EXTI_InitTypeDef EXTI_InitStructure_LINE2;
 	NVIC_InitTypeDef NVIC_InitStructure;

  	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);	//使能复用功能时钟
	
	//GPIOA.1,2：上拉、上升沿和下降沿中断：
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
  	NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQn;			//使能按键WK_UP所在的外部中断通道
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;	//抢占优先级2， 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;					//子优先级3
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//使能外部中断通道
  	NVIC_Init(&NVIC_InitStructure); 
	
  	NVIC_InitStructure.NVIC_IRQChannel = EXTI2_IRQn;			//使能按键WK_UP所在的外部中断通道
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;	//抢占优先级2， 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;					//子优先级3
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//使能外部中断通道
  	NVIC_Init(&NVIC_InitStructure); 
}

//外部中断1服务程序 
void EXTI1_IRQHandler(void)
{
	OSIntEnter();
	//if(EXTI_GetITStatus(EXTI_Line1) == SET) // 读取中断状态
	{
		//delay_ms(10);//消抖
		LED = !LED;
		EXTI_ClearITPendingBit(EXTI_Line1); //清除LINE0上的中断标志位  
	}
	OSIntExit();
}
 

//外部中断2服务程序
void EXTI2_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line2) == SET) // 读取中断状态
	{
		delay_ms(10);//消抖
		if(1)	 	 //WK_UP按键
		{				 
			;
		}
		EXTI_ClearITPendingBit(EXTI_Line2); //清除LINE0上的中断标志位  
	}
}
 
