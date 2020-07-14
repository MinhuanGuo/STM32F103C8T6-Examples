#include "master_Control.h"





extern  uint32_t pwmD;
extern  MH_Hardware::_oled0561 oled;
extern  MH_Hardware::_bldc_motor bldcMotor;
extern  MH_Hardware::_gpio_key gpio_key;


void Encoder_Key1(void * arg)
{
		static bool tmp = true;
		tmp  = !tmp;
		
		bldcMotor.setDir(tmp);//�ı䷽��
		bldcMotor.updateHallValue();
		bldcMotor.setSpeed(pwmD);	
}

void Encoder_Key2(void * arg)
{
		static bool tmp = true;
		tmp  = !tmp;
		
		bldcMotor.setRun(tmp);//����/ͣ��
		bldcMotor.updateHallValue();
		bldcMotor.setSpeed(pwmD);		
}

//����ɨ����صı���������ָ�룺
typedef void (*FUNC)(void * arg);
FUNC KeyFunction[KEYNUMBER]={
	// Register for Key Function
	// Key0
	Encoder_Key1,
	// Key1
	Encoder_Key2,
	// Add your Key Function
};

////////////////////////////////////
void Task_Manipulate(void)
{
	static uint32_t enc_tim2;
	static uint32_t enc_tim2_last;
	
	//Step1: ������
	gpio_key.scan();
	if(gpio_key.GetKeyStatus(0))
	{
		Encoder_Key1(NULL);	
	}
	
	//Step2: ��ť������������TIM2_Encoder��ֵ������PWMռ�ձȣ�
	enc_tim2 = (uint32_t)(__HAL_TIM_GET_COUNTER(&htim2));//��ȡ��������ֵ
	if(enc_tim2_last != enc_tim2)
	{
			enc_tim2 %=50;	
			enc_tim2_last = enc_tim2;
	}
	pwmD = enc_tim2+2;	
}


void Task_Sensor(void)
{
	
}


void Task_Master(void)
{
	
}


void Task_Show(void)//��ʾOLED��
{
		static char res[20];
	
	//�ڶ��У���ʾPWMռ�ձ�D
		sprintf(res,"D: %2d%%\0",pwmD);
		oled.DISPLAY_8x16_BUFFER(2,(u8*)res);
	

	//�����У���ʾ�ٶȣ�
		sprintf(res,"Vel(Hall): %4d\0",bldcMotor.getHallCount());
		oled.DISPLAY_8x16_BUFFER(4,(u8*)res); 
		bldcMotor.clearHallCount();
	
		//�����У���ʾClockWise��
		sprintf(res,"CW: %1d\0",bldcMotor.getDir());
		oled.DISPLAY_8x16_BUFFER(6,(u8*)res); 	
}



