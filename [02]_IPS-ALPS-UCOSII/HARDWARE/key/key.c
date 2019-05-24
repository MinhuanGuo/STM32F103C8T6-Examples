#include "key.h"
#include "delay.h" 
//////////////////////////////////////////////////////////////////////////////////	 
//ALIENTEK STM32F407开发板
//按键输入驱动代码	   		  
////////////////////////////////////////////////////////////////////////////////// 	 

//按键初始化函数
void KEY_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	// PA0: Key Initial:
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE); //开启按键端口PA的时钟
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0; 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //端口配置为上拉输入
	GPIO_Init(GPIOA, &GPIO_InitStructure);	//初始化端口
	
	// PA1,PA2: Key Initial:
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE); //开启按键端口PA的时钟
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1|GPIO_Pin_2; 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; //端口配置为上拉输入
	GPIO_Init(GPIOA, &GPIO_InitStructure);	//初始化端口

	
	//PB7,PB8 定时器配置，读取旋转编码器
	GPIO_InitTypeDef GPIO_InitStruct;
    // Step 1: Initialize GPIO as input for rotary encoder
    // PB7 (TIM4_CH2) (encoder pin A), PB6 (TIM4_CH1) (encoder pin B)
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_7 | GPIO_Pin_6;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_Init(GPIOB, &GPIO_InitStruct);

    // Step 2: Setup TIM4 for encoder input
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
    TIM_EncoderInterfaceConfig(TIM4, TIM_EncoderMode_TI12, 
        TIM_ICPolarity_Rising, TIM_ICPolarity_Falling);
    TIM_Cmd(TIM4, ENABLE);
	
	/*
	// PB8,PB9: Key Initial:
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOB, ENABLE );//PORTB时钟使能

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8|GPIO_Pin_9; 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //端口配置为上拉输入
	GPIO_Init(GPIOB, &GPIO_InitStructure);//初始化GPIOB8,9
	*/
}


//按键处理函数
//返回按键值
//mode:0,不支持连续按;1,支持连续按;
//0，没有任何按键按下
//1，KEY0按下
//2，KEY1按下
//3，KEY2按下 
//4，WKUP按下 WK_UP
//注意此函数有响应优先级,KEY0>KEY1>KEY2>WK_UP!!
u8 KEY_Scan(u8 mode)
{	 
	static u8 key_up=1;//按键按松开标志
	if(mode)key_up=1;  //支持连按		  
	if(key_up&&(KEY0==0||KEY2==0))
	{
		delay_ms(10);//去抖动 
		key_up=0;
		if(KEY0==0)return Key_Right_Pres;
		else if(KEY2==0)return Key_Left_Pres;
	}else if(KEY0==1&&KEY2==1)key_up=1; 	    
 	return 0;// 无按键按下
}


//旋钮编码器处理函数
u8 Rotary_Encoder_Scan(void)
{
	static u8 encoder0PinALast = 0; //前一时刻，编码器PinA的电位
	
	if((encoder0PinALast == 0)&&PIN_A)//PinA是上升沿
	{
		delay_ms(1);//去抖动 
		if(PIN_A&&PIN_B) 
		{
			encoder0PinALast = PIN_A;
			return Rotary_Clock; //顺时针
		}
		if(PIN_A&&(PIN_B==0))
		{
			encoder0PinALast = PIN_A;
			return Rotary_AntiClock; //逆时针
		}
	}
	
	if((encoder0PinALast == 1)&& (PIN_A ==0))//PinA是下降沿
	{
		delay_ms(1);//去抖动 
		if((PIN_A ==0)&&PIN_B)
		{
			encoder0PinALast = PIN_A;
			return Rotary_AntiClock; //逆时针
		}
		if((PIN_A ==0)&&(PIN_B==0))
		{
			encoder0PinALast = PIN_A;
			return Rotary_Clock; //顺时针
		}
	}
	
	return 0;//没有
}

//左右按钮函数，实现设定、确定和返回功能
u8 KEY_LeftAndRight(u8 current_level,u32 key)
{
	u8 new_level;
	switch(current_level)
	{
		case Style:
			if(key == Key_Left_Pres) new_level = Menu;
			break;
		case Menu:
			if(key == Key_Left_Pres) new_level = Value;
		    if(key == Key_Right_Pres) new_level = Style;
			break;
		case Value:
		    if(key == Key_Right_Pres) new_level = Menu;
			break;
	}
	return new_level;
}
// 通过旋钮设定亮度
u8 Get_Brightness(u8 rotary_state)
{
	static int brightness = 0xff;
	if(rotary_state == Rotary_Clock) brightness += 30;
	if(rotary_state == Rotary_AntiClock) brightness -= 30;
	if(brightness>250) brightness=255;
	if(brightness<1) brightness=1;
	return (u8)brightness;
}


// 通过旋钮设定Style
u8 Get_Style(u8 current_style, u8 rotary_state)
{
	u8 new_style;
	switch(current_style)
	{
		case StyleA:
			if(rotary_state == Rotary_Clock) new_style = StyleB;
		    if(rotary_state == Rotary_AntiClock) new_style = StyleC;
		    break;
		case StyleB:
			if(rotary_state == Rotary_Clock) new_style = StyleC;
		    if(rotary_state == Rotary_AntiClock) new_style = StyleA;
		    break;
		case StyleC:
			if(rotary_state == Rotary_Clock) new_style = StyleA;
		    if(rotary_state == Rotary_AntiClock) new_style = StyleB;
		    break;
	}
	return new_style;
}

// 通过旋钮切换Menu
u8 Get_Menu(u8 current_menu, u8 rotary_state)
{
	u8 new_menu;
	switch(current_menu)
	{
		case MenuA:
			if(rotary_state == Rotary_Clock) new_menu = MenuB;
		    if(rotary_state == Rotary_AntiClock) new_menu = MenuC;
		    break;
		case MenuB:
			if(rotary_state == Rotary_Clock) new_menu = MenuC;
		    if(rotary_state == Rotary_AntiClock) new_menu = MenuA;
		    break;
		case MenuC:
			if(rotary_state == Rotary_Clock) new_menu = MenuA;
		    if(rotary_state == Rotary_AntiClock) new_menu = MenuB;
		    break;
	}
	return new_menu;
}

void Tuning_Value_Rotary(float *value,u8 rotary_state,float step,float min, float max)
{
	if(rotary_state == Rotary_Clock) *value += step;
	if(rotary_state == Rotary_AntiClock) *value -= step;
	if(*value>max) *value = max;
	if(*value<min) *value = min;
}

















