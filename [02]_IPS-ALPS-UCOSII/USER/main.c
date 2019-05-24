#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "key.h"
#include "spi.h"
#include "math.h"
#include "exti.h"

#include "LG_ST7789.h"
#include "graphicstest.h"
#include "includes.h"


#include "stm32f10x_conf.h"

//LCD pen color and background color   
u16 POINT_COLOR=0x0000;	//pen color
u16 BACK_COLOR=0xFFFF;  //background color
u16 ringColor[10] = {0x763E,0x5E9E,0x4FDA,0x77F4,0xCFF4,0xE7D5,0xF6AD,0xF589,0xF447,0xF0E3};
u32 RGB32[10] = {0x70C6FC,0x78D3FC,0x79D6D0,0xC2E89D,0xD8DE97,0xD8D163,0xCEB36F,0xC08652,0xBA6855,0xAB5651};
u32 RGB32A[8] = {0xE7A830,0xE6D938,0x9DC54D,0x61A952,0xDB7D2D,0xD5672C,0xCF4429,0xFF0000};
u32 RGB32B[8] = {0xadcbff,0xadf3ff,0xadffd6,0xb7ffad,0xe5ffad,0xffeaad,0xffc1ad,0xff5762};


/////////////////////////UCOSII任务设置//////////////////////////////////
//START 任务
//设置任务优先级
#define START_TASK_PRIO      			10 //开始任务的优先级设置为最低
//设置任务堆栈大小
#define START_STK_SIZE  				64
//任务堆栈	
OS_STK START_TASK_STK[START_STK_SIZE];
//任务函数
void start_task(void *pdata);


//主任务
//设置任务优先级
#define MAIN_TASK_PRIO       			4 
//设置任务堆栈大小
#define MAIN_STK_SIZE  					128
//任务堆栈	
OS_STK MAIN_TASK_STK[MAIN_STK_SIZE];
//任务函数
void main_task(void *pdata);


//LED0任务: 调用LED，调试用
//设置任务优先级
#define LED0_TASK_PRIO       			6 
//设置任务堆栈大小
#define LED0_STK_SIZE  		    		64
//任务堆栈	
OS_STK LED0_TASK_STK[LED0_STK_SIZE];
//任务函数
void led0_task(void *pdata);



//LED1任务：调用IPS，显示表盘
//设置任务优先级
#define LED1_TASK_PRIO       			7 
//设置任务堆栈大小
#define LED1_STK_SIZE  					128
//任务堆栈
OS_STK LED1_TASK_STK[LED1_STK_SIZE];
//任务函数
void led1_task(void *pdata);


//按键扫描任务：识别ALPS旋钮
//设置任务优先级
#define KEY_TASK_PRIO       			2 
//设置任务堆栈大小
#define KEY_STK_SIZE  					64
//任务堆栈	
OS_STK KEY_TASK_STK[KEY_STK_SIZE];
//任务函数
void key_task(void *pdata);


//////////////////////////////////////////////////////////////////////////////
OS_EVENT * msg_key;			   //按键邮箱事件块指针
OS_EVENT * msg_rotary_encoder; //旋钮邮箱事件块指针
OS_EVENT * msg_level;			   //按键邮箱事件块指针

OS_EVENT * sem_beep;		  //蜂鸣器信号量指针	 
OS_TMR   * tmr1;			  //软件定时器1

IPS_TypeDef ips; // 声明一个结构体
static float pointer_angle = 0.0;
static int16_t enc_cnt;

//软件定时器1的回调函数	
//每100ms执行一次,
void tmr1_callback(OS_TMR *ptmr,void *p_arg) 
{
	static int num = 0;
	static u8 err;
	static u32 level=0;
	static u8 i=0;
	static u8 tmp = 0x30;
	static char str[20];

	static float pointer_angle_last = 36.001;
	
	static int Num = 60;
	static float step;
	step = (360.0 - 72.0)/Num;
	u16 pointer_length = 80;

	//invertDisplay(ON);
	//delay_ms(100);
	//drawChar(&ips, 98,88, tmp+i, WHITE, GREY, 10);
	//drawChar(&ips, 109,180, tmp+i, WHITE, GREY, 6);

	//fillCircle(&ips, 120, 120, pointer_length, BLACK);
	
	enc_cnt = TIM_GetCounter(TIM4);
	pointer_angle = enc_cnt*step + 36.0;
	
	if(pointer_angle_last != pointer_angle)//指针位置改变时需要重新绘制
	{
		lcd_show_pointer(&ips, 120, 120, pointer_length,pointer_angle_last ,pointer_angle, WHITE);
		fillCircle(&ips, 120, 120, 10, WHITE);
		pointer_angle_last = pointer_angle;
		BACK_COLOR = BLACK;
		ftoa(pointer_angle, str, 1);
		lcd_show_string(&ips, 85, 200, 64, 16, str , 32, 0);
	}

	
	num++;
	if(num==Num)
	{
		num = 0;
	}
}

void ucos_load_main_ui(void)
{
	int j;
	ips_display_Init(&ips,240,240,0);//结构体初始化，配置，使能
	setRotation(&ips, 2);//旋转设定

	POINT_COLOR = WHITE;
	BACK_COLOR = BLACK;
	fillScreen(&ips,BLACK);

	int seg =36;
	int ring_width = 30;

	for(j = 0;j<8;j++)
	{
		fillArc(&ips,120,120, j*seg+seg, seg , 120, 120, ring_width, RGB24toRGB16(RGB32B[j]));
	}
	fillArc(&ips,120,120, 36, seg*8 , 120, 120, 2, SILVER);
	fillArc(&ips,120,120, 36, seg*8 , 120-ring_width, 120-ring_width, 2, SILVER);
}

int main (void)
{
	///////////////////////////////////////
	delay_init();     //初始化延时函数
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置系统中断优先级分组2
	uart_init(115200);	//初始化串口波特率为115200
	LED_GPIO_Config();
	KEY_Init();
	//EXTIX_Init();         	//初始化外部中断输入 	

	
	
	ucos_load_main_ui();		//加载主界面		
	OSInit();   
 	OSTaskCreate(start_task,(void *)0,(OS_STK *)&START_TASK_STK[START_STK_SIZE-1],START_TASK_PRIO );//创建起始任务
	OSStart();	
}


//开始任务
void start_task(void *pdata)
{	
    OS_CPU_SR cpu_sr=0;
	pdata = pdata; 
	msg_key=OSMboxCreate((void*)0);	//创建消息邮箱
	msg_level=OSMboxCreate((void*)0);	//创建消息邮箱
	msg_rotary_encoder=OSMboxCreate((void*)0);	//创建消息邮箱
	sem_beep=OSSemCreate(0);		//创建信号量
	OSStatInit();					//初始化统计任务.这里会延时1秒钟左右	
  	OS_ENTER_CRITICAL();			//进入临界区(无法被中断打断)

 	OSTaskCreate(led0_task,(void *)0,(OS_STK*)&LED0_TASK_STK[LED0_STK_SIZE-1],LED0_TASK_PRIO);						   
 	//OSTaskCreate(led1_task,(void *)0,(OS_STK*)&LED1_TASK_STK[LED1_STK_SIZE-1],LED1_TASK_PRIO);	
 	OSTaskCreate(main_task,(void *)0,(OS_STK*)&MAIN_TASK_STK[MAIN_STK_SIZE-1],MAIN_TASK_PRIO);	 				   
 	//OSTaskCreate(key_task,(void *)0,(OS_STK*)&KEY_TASK_STK[KEY_STK_SIZE-1],KEY_TASK_PRIO);	 	
	OSTaskSuspend(START_TASK_PRIO);	//挂起起始任务.
	OS_EXIT_CRITICAL();				//退出临界区(可以被中断打断)
}

//LED0任务
void led0_task(void *pdata)
{	 	
	while(1)
	{
		LED1(ON);
		delay_ms(500);
		LED1(OFF);
		delay_ms(500);
	};
}

//LED1任务: void
void led1_task(void *pdata)
{	  

}

//主任务
void main_task(void *pdata)
{	
	static int num = 100;
	static u8 current_level = Style;
	static u8 previous_level;
	static u8 current_style = StyleA;
	static u8 current_menu = MenuA;
	static float valueA = 100.0f;
	static float valueB = 200.0f;
	static float valueC = 300.0f;
	static float temp = 989.2f;
	static u32 key=0;
	static u8 rotary_state=0;
	u8 err;	
	u8 tcnt=0;
	tmr1=OSTmrCreate(10,10,OS_TMR_OPT_PERIODIC,(OS_TMR_CALLBACK)tmr1_callback,0,"tmr1",&err); //100ms执行一次
	OSTmrStart(tmr1,&err);//启动软件定时器1	

	//extern IPS_TypeDef ips; // 声明一个结构体

	while(1)
	{
		key=(u32)OSMboxPend(msg_key,10,&err);  // 读取按键信息: Key_Left_Pres， Key_Right_Pres
		current_level = KEY_LeftAndRight(current_level,key); //根据左右按键信息，设定处于哪个Level
		rotary_state=(u32)OSMboxPend(msg_rotary_encoder,10,&err);  //读取旋钮信息:Rotary_Clock, Rotary_AntiColock

		//if ((GPIOB->IDR & GPIO_Pin_5))
		//{
			//pointer_angle += 10.0;
		//}
		//Tuning_Value_Rotary(&pointer_angle,rotary_state,10.0,36.0,324.0);
		
		switch(rotary_state)//根据不同的Level，定义不同的旋钮功能
		{
			case Rotary_Clock:
				//if(previous_level!=Style)//首次进入要先清屏
				{
					lcd_show_string(&ips, 110, 150, 64, 16, "A" , 32, 0);
				}
				break;
			case Rotary_AntiClock:
				//if(previous_level!=Menu)//首次进入要先清屏
				{
					lcd_show_string(&ips, 110, 150, 64, 16, "B" , 32, 0);
				}				
				break;
		}
		previous_level = current_level;
		//OLED_Refresh_Gram();
		
		//printf("Key: %d; Level: %d; Style: %d; Menu: %d; ValueA: %-3.2f; ValueB: %-3.2f; ValueC: %-3.2f; \r\n",key,current_level,current_style,current_menu,valueA,valueB,valueC);
		
		if(tcnt==50)//0.5秒更新一次CPU使用率
		{
			//tcnt=0;
			//POINT_COLOR=BLUE;		  
			//LCD_ShowxNum(192,30,OSCPUUsage,3,16,0);	//显示CPU使用率   
		}
		tcnt++;
		//delay_ms(10);
	}
}
//按键扫描任务
void key_task(void *pdata)
{	
	u8 key;
	u8 rotary_state;
	while(1)
	{
		//key=KEY_Scan(0); 
		rotary_state = Rotary_Encoder_Scan();		
		if(key)OSMboxPost(msg_key,(void*)key);//向消息邮箱发送消息
		if(rotary_state)OSMboxPost(msg_rotary_encoder,(void*)rotary_state);//向消息邮箱发送消息
 		delay_ms(10);
	}
}


