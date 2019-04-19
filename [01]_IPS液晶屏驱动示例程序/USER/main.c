#include "stm32f10x.h" //STM header file
#include "led.h"
#include "key.h"
#include "spi.h"
#include "delay.h"
#include "usart.h"

#include "LG_ST7789.h"
#include "graphicstest.h"

//LCD pen color and background color   
u16 POINT_COLOR=0x0000;	//pen color
u16 BACK_COLOR=0xFFFF;  //background color


int main (void)
{
	///////////////////////////////////////
	delay_init();     //初始化延时函数
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置系统中断优先级分组2
	uart_init(115200);	//初始化串口波特率为115200
	LED_GPIO_Config();
	Key_GPIO_Config();
	
	u8 i=0;
	POINT_COLOR = RED;
	
	IPS_TypeDef ips; // 声明一个结构体
	ips_display_Init(&ips,240,240,0);//结构体初始化，配置，使能
	setRotation(&ips, 2);//旋转设定
	
	fillScreen(&ips,BLUE);
	delay_ms(1000);
	
	drawPixel(&ips, ips._width/2, ips._height/2, GREEN);
	delay_ms(1000);
	
	testlines(&ips, YELLOW);
	delay_ms(1000);
	
	testfastlines(&ips,GREEN,RED);
	delay_ms(1000);
	
	testdrawrects(&ips,GREEN);
	delay_ms(1000);
	
	testfillrects(&ips,YELLOW, MAGENTA);
	delay_ms(1000);
	
	fillScreen(&ips,BLACK);
	testfillcircles(&ips,10, BLUE);
	testdrawcircles(&ips,10, WHITE);
	delay_ms(1000);
	
	testroundrects(&ips);
	delay_ms(1000);
	
	testtriangles(&ips);
	delay_ms(1000);
	
	mediabuttons(&ips);
	delay_ms(1000);
	
	while(1)
	{
		if( Key_Scan(GPIOA,GPIO_Pin_0) == KEY_OFF  )
		{
				LED1(ON);
				invertDisplay(ON);
				delay_ms(200);
			
				LED1(OFF);
				invertDisplay(OFF);
				delay_ms(200);		
		}
		
	}
}

