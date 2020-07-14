#include "master_Control.h"





extern  uint32_t pwmD;
extern  MH_Hardware::_oled0561 oled;
extern  MH_Hardware::_bldc_motor bldcMotor;
extern  MH_Hardware::_gpio_key gpio_key;


void Encoder_Key1(void * arg)
{
		static bool tmp = true;
		tmp  = !tmp;
		
		bldcMotor.setDir(tmp);//改变方向
		bldcMotor.updateHallValue();
		bldcMotor.setSpeed(pwmD);	
}

void Encoder_Key2(void * arg)
{
		static bool tmp = true;
		tmp  = !tmp;
		
		bldcMotor.setRun(tmp);//启动/停机
		bldcMotor.updateHallValue();
		bldcMotor.setSpeed(pwmD);		
}

//按键扫描相关的变量、函数指针：
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
	
	//Step1: 按键：
	gpio_key.scan();
	if(gpio_key.GetKeyStatus(0))
	{
		Encoder_Key1(NULL);	
	}
	
	//Step2: 旋钮编码器，更新TIM2_Encoder的值，调节PWM占空比：
	enc_tim2 = (uint32_t)(__HAL_TIM_GET_COUNTER(&htim2));//获取编码器的值
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


void Task_Show(void)//显示OLED屏
{
		static char res[20];
	
	//第二行，显示PWM占空比D
		sprintf(res,"D: %2d%%\0",pwmD);
		oled.DISPLAY_8x16_BUFFER(2,(u8*)res);
	

	//第三行，显示速度：
		sprintf(res,"Vel(Hall): %4d\0",bldcMotor.getHallCount());
		oled.DISPLAY_8x16_BUFFER(4,(u8*)res); 
		bldcMotor.clearHallCount();
	
		//第四行，显示ClockWise：
		sprintf(res,"CW: %1d\0",bldcMotor.getDir());
		oled.DISPLAY_8x16_BUFFER(6,(u8*)res); 	
}



