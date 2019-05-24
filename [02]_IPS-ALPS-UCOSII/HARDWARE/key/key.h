#ifndef __KEY_H
#define __KEY_H	 
#include "sys.h" 
//////////////////////////////////////////////////////////////////////////////////	 
//ALIENTEK STM32F407������
//����������������	   								  
////////////////////////////////////////////////////////////////////////////////// 	 

/*����ķ�ʽ��ͨ��ֱ�Ӳ����⺯����ʽ��ȡIO*/
#define KEY0 		GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4) //PE4
#define KEY1 		GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_3)	//PE3 
#define KEY2 		GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_2) //PE2
//#define WK_UP 	    GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)	//PA0

#define PIN_A 		GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_1) //GPIOA1��������ת������PinA
#define PIN_B		GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_2) //GPIOA2��������ת������PinB


/*���淽ʽ��ͨ��λ��������ʽ��ȡIO*/
/*
#define KEY0 		PEin(4)   	//PE4
#define KEY1 		PEin(3)		//PE3 
#define KEY2 		PEin(2)		//P32
#define WK_UP 	PAin(0)		//PA0
*/


#define KEY0_PRES 	1
#define KEY1_PRES	2
#define KEY2_PRES	3
#define WKUP_PRES   4



enum KeyCmdOption
{
	Rotary_Clock=1,
	Rotary_AntiClock,
	Key_Left_Pres,
	Key_Right_Pres,
	Style,//5
	Menu,
	Value,
	StyleA,//8
	StyleB,
	StyleC,
	MenuA,//11
	MenuB,
	MenuC
};


void KEY_Init(void);	//IO��ʼ��
void EXTI_PORTE_Configuration(void);

u8 KEY_Scan(u8);  		//����ɨ�躯��	
u8 Rotary_Encoder_Scan(void);  		//��ťɨ�躯��
u8 KEY_LeftAndRight(u8 current_level,u32 key);
u8 Get_Brightness(u8 rotary_state);
u8 Get_Style(u8 current_style,u8 rotary_state);
u8 Get_Menu(u8 current_menu, u8 rotary_state);
void Tuning_Value_Rotary(float *value,u8 rotary_state,float step,float min, float max);


#endif
