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


/////////////////////////UCOSII��������//////////////////////////////////
//START ����
//�����������ȼ�
#define START_TASK_PRIO      			10 //��ʼ��������ȼ�����Ϊ���
//���������ջ��С
#define START_STK_SIZE  				64
//�����ջ	
OS_STK START_TASK_STK[START_STK_SIZE];
//������
void start_task(void *pdata);


//������
//�����������ȼ�
#define MAIN_TASK_PRIO       			4 
//���������ջ��С
#define MAIN_STK_SIZE  					128
//�����ջ	
OS_STK MAIN_TASK_STK[MAIN_STK_SIZE];
//������
void main_task(void *pdata);


//LED0����: ����LED��������
//�����������ȼ�
#define LED0_TASK_PRIO       			6 
//���������ջ��С
#define LED0_STK_SIZE  		    		64
//�����ջ	
OS_STK LED0_TASK_STK[LED0_STK_SIZE];
//������
void led0_task(void *pdata);



//LED1���񣺵���IPS����ʾ����
//�����������ȼ�
#define LED1_TASK_PRIO       			7 
//���������ջ��С
#define LED1_STK_SIZE  					128
//�����ջ
OS_STK LED1_TASK_STK[LED1_STK_SIZE];
//������
void led1_task(void *pdata);


//����ɨ������ʶ��ALPS��ť
//�����������ȼ�
#define KEY_TASK_PRIO       			2 
//���������ջ��С
#define KEY_STK_SIZE  					64
//�����ջ	
OS_STK KEY_TASK_STK[KEY_STK_SIZE];
//������
void key_task(void *pdata);


//////////////////////////////////////////////////////////////////////////////
OS_EVENT * msg_key;			   //���������¼���ָ��
OS_EVENT * msg_rotary_encoder; //��ť�����¼���ָ��
OS_EVENT * msg_level;			   //���������¼���ָ��

OS_EVENT * sem_beep;		  //�������ź���ָ��	 
OS_TMR   * tmr1;			  //�����ʱ��1

IPS_TypeDef ips; // ����һ���ṹ��
static float pointer_angle = 0.0;
static int16_t enc_cnt;

//�����ʱ��1�Ļص�����	
//ÿ100msִ��һ��,
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
	
	if(pointer_angle_last != pointer_angle)//ָ��λ�øı�ʱ��Ҫ���»���
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
	ips_display_Init(&ips,240,240,0);//�ṹ���ʼ�������ã�ʹ��
	setRotation(&ips, 2);//��ת�趨

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
	delay_init();     //��ʼ����ʱ����
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//����ϵͳ�ж����ȼ�����2
	uart_init(115200);	//��ʼ�����ڲ�����Ϊ115200
	LED_GPIO_Config();
	KEY_Init();
	//EXTIX_Init();         	//��ʼ���ⲿ�ж����� 	

	
	
	ucos_load_main_ui();		//����������		
	OSInit();   
 	OSTaskCreate(start_task,(void *)0,(OS_STK *)&START_TASK_STK[START_STK_SIZE-1],START_TASK_PRIO );//������ʼ����
	OSStart();	
}


//��ʼ����
void start_task(void *pdata)
{	
    OS_CPU_SR cpu_sr=0;
	pdata = pdata; 
	msg_key=OSMboxCreate((void*)0);	//������Ϣ����
	msg_level=OSMboxCreate((void*)0);	//������Ϣ����
	msg_rotary_encoder=OSMboxCreate((void*)0);	//������Ϣ����
	sem_beep=OSSemCreate(0);		//�����ź���
	OSStatInit();					//��ʼ��ͳ������.�������ʱ1��������	
  	OS_ENTER_CRITICAL();			//�����ٽ���(�޷����жϴ��)

 	OSTaskCreate(led0_task,(void *)0,(OS_STK*)&LED0_TASK_STK[LED0_STK_SIZE-1],LED0_TASK_PRIO);						   
 	//OSTaskCreate(led1_task,(void *)0,(OS_STK*)&LED1_TASK_STK[LED1_STK_SIZE-1],LED1_TASK_PRIO);	
 	OSTaskCreate(main_task,(void *)0,(OS_STK*)&MAIN_TASK_STK[MAIN_STK_SIZE-1],MAIN_TASK_PRIO);	 				   
 	//OSTaskCreate(key_task,(void *)0,(OS_STK*)&KEY_TASK_STK[KEY_STK_SIZE-1],KEY_TASK_PRIO);	 	
	OSTaskSuspend(START_TASK_PRIO);	//������ʼ����.
	OS_EXIT_CRITICAL();				//�˳��ٽ���(���Ա��жϴ��)
}

//LED0����
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

//LED1����: void
void led1_task(void *pdata)
{	  

}

//������
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
	tmr1=OSTmrCreate(10,10,OS_TMR_OPT_PERIODIC,(OS_TMR_CALLBACK)tmr1_callback,0,"tmr1",&err); //100msִ��һ��
	OSTmrStart(tmr1,&err);//���������ʱ��1	

	//extern IPS_TypeDef ips; // ����һ���ṹ��

	while(1)
	{
		key=(u32)OSMboxPend(msg_key,10,&err);  // ��ȡ������Ϣ: Key_Left_Pres�� Key_Right_Pres
		current_level = KEY_LeftAndRight(current_level,key); //�������Ұ�����Ϣ���趨�����ĸ�Level
		rotary_state=(u32)OSMboxPend(msg_rotary_encoder,10,&err);  //��ȡ��ť��Ϣ:Rotary_Clock, Rotary_AntiColock

		//if ((GPIOB->IDR & GPIO_Pin_5))
		//{
			//pointer_angle += 10.0;
		//}
		//Tuning_Value_Rotary(&pointer_angle,rotary_state,10.0,36.0,324.0);
		
		switch(rotary_state)//���ݲ�ͬ��Level�����岻ͬ����ť����
		{
			case Rotary_Clock:
				//if(previous_level!=Style)//�״ν���Ҫ������
				{
					lcd_show_string(&ips, 110, 150, 64, 16, "A" , 32, 0);
				}
				break;
			case Rotary_AntiClock:
				//if(previous_level!=Menu)//�״ν���Ҫ������
				{
					lcd_show_string(&ips, 110, 150, 64, 16, "B" , 32, 0);
				}				
				break;
		}
		previous_level = current_level;
		//OLED_Refresh_Gram();
		
		//printf("Key: %d; Level: %d; Style: %d; Menu: %d; ValueA: %-3.2f; ValueB: %-3.2f; ValueC: %-3.2f; \r\n",key,current_level,current_style,current_menu,valueA,valueB,valueC);
		
		if(tcnt==50)//0.5�����һ��CPUʹ����
		{
			//tcnt=0;
			//POINT_COLOR=BLUE;		  
			//LCD_ShowxNum(192,30,OSCPUUsage,3,16,0);	//��ʾCPUʹ����   
		}
		tcnt++;
		//delay_ms(10);
	}
}
//����ɨ������
void key_task(void *pdata)
{	
	u8 key;
	u8 rotary_state;
	while(1)
	{
		//key=KEY_Scan(0); 
		rotary_state = Rotary_Encoder_Scan();		
		if(key)OSMboxPost(msg_key,(void*)key);//����Ϣ���䷢����Ϣ
		if(rotary_state)OSMboxPost(msg_rotary_encoder,(void*)rotary_state);//����Ϣ���䷢����Ϣ
 		delay_ms(10);
	}
}


