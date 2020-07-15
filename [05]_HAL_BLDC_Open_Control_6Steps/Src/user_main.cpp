#include "main.h"
#include "i2c.h"
#include "tim.h"
#include "gpio.h"
#include "oled0561.h"
#include "bldc_motor.h"
#include "GPIOKey.h"
#include "global.h"
#include "TSK_STM_core.h"  
#include "master_Control.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>


/////////////////////////////////////////////////////
//硬件结构体对象
MH_Hardware::_oled0561 oled(0x78); //OLED屏
MH_Hardware::_bldc_motor bldcMotor(0x00);//BLDC
MH_Hardware::_gpio_key gpio_key(0x00);//按键

/////////////////////////////////////////////////////
//用户任务函数
extern void Task_Manipulate(void);//更新输入：按键、旋钮编码器
extern void Task_Sensor(void);//更新传感器
extern void Task_Master(void);//主任务
extern void Task_Show(void);//显示OLED屏

TASK_COMPONENTS TaskComps[TASK_MAX] = 
{
		//{Status, Run, Timer, ItvTime, *TaskHook}
		{TASK_ON, 0, 100, 5, Task_Manipulate}, //
		{TASK_ON, 0, 1, 20, Task_Sensor}, //
    {TASK_ON, 0, 100, 20, Task_Master}, //
		{TASK_ON, 0, 100, 250, Task_Show}, //
}; 

/////////////////////////////////////////////////////
//用户设置函数：
void user_setup()
{
	//等待一会儿
	HAL_Delay(1000);
	//============================================================
	//Step1：液晶屏初始化
	oled.Init();
	oled.DISPLAY_8x16_BUFFER(0,(u8*)"Testing..."); //显示字符串

	if(HAL_I2C_IsDeviceReady(&hi2c1,0x78,5,10)!=HAL_OK)
		return;
	//============================================================
	//Step2：TIM4通用定时器初始化
	/*##-1- Start the TIM Base generation in interrupt mode ####################*/
	//普通定时器初始化，TIM4，50Hz？
  HAL_TIM_Base_Start_IT(&htim4);
	//============================================================
	//Step3：ABZ编码器初始化
	HAL_TIM_Encoder_Start(&htim2, TIM_CHANNEL_ALL);
	//============================================================
	//Step4：TIM3_Channel1、2、3通道：UVW霍尔传感器初始化
	//			 TIM3_Channel4：无输出的输出比较，作为定时器
	bldcMotor.enableRun(true);
	bldcMotor.setClockWise(true); 
	
	HAL_TIMEx_HallSensor_Start(&htim3);
	__HAL_TIM_ENABLE_IT(&htim3,TIM_IT_TRIGGER|TIM_IT_CC4);	
	
	//BLDC初步启动
	bldcMotor.updateHallValue();
	bldcMotor.updatePWMD(10);
	bldcMotor.setSpeed();//调用一次，启动电机
}


///////////////////////////////////////////////////
//用户循环函数
void user_loop()
{
		TaskProcess();
}


///////////////////////////////////////////////////
//滴答定时器：
void user_systick_fun()
{
		uint8_t i;
		
    for (i=0; i<TASK_MAX; i++)   // 逐个任务时间处理        
    {
			if ( TaskComps[i].Status)   //任务开启：TASK_ON       
			{
					TaskComps[i].Timer--;     // 减去一个节拍    
					if (TaskComps[i].Timer <= 0)  // 计时器时间到
					{
							 TaskComps[i].Timer = TaskComps[i].ItvTime;   // 恢复计时器值，重新下一次 
							 TaskComps[i].Run = 1;    // 任务可以运行
					}
			}
		}
}

/////////////////////////////////////////////////////
//TIM3霍尔传感器核心函数：
void user_TIM3_HALL_fun()
{
		bldcMotor.updateHallValue();//更新霍尔传感器的值
		bldcMotor.setSpeed();	//根据霍尔传感器的值，进行六步换相，并通过调节PWM占空比来调速
}


