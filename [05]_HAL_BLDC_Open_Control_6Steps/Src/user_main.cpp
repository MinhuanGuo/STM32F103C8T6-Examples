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
//Ӳ���ṹ�����
MH_Hardware::_oled0561 oled(0x78); //OLED��
MH_Hardware::_bldc_motor bldcMotor(0x00);//BLDC
MH_Hardware::_gpio_key gpio_key(0x00);//����

/////////////////////////////////////////////////////
//�û�������
extern void Task_Manipulate(void);//�������룺��������ť������
extern void Task_Sensor(void);//���´�����
extern void Task_Master(void);//������
extern void Task_Show(void);//��ʾOLED��

TASK_COMPONENTS TaskComps[TASK_MAX] = 
{
		//{Status, Run, Timer, ItvTime, *TaskHook}
		{TASK_ON, 0, 100, 5, Task_Manipulate}, //
		{TASK_ON, 0, 1, 20, Task_Sensor}, //
    {TASK_ON, 0, 100, 20, Task_Master}, //
		{TASK_ON, 0, 100, 250, Task_Show}, //
}; 

/////////////////////////////////////////////////////
//�û����ú�����
void user_setup()
{
	//�ȴ�һ���
	HAL_Delay(1000);
	//============================================================
	//Step1��Һ������ʼ��
	oled.Init();
	oled.DISPLAY_8x16_BUFFER(0,(u8*)"Testing..."); //��ʾ�ַ���

	if(HAL_I2C_IsDeviceReady(&hi2c1,0x78,5,10)!=HAL_OK)
		return;
	//============================================================
	//Step2��TIM4ͨ�ö�ʱ����ʼ��
	/*##-1- Start the TIM Base generation in interrupt mode ####################*/
	//��ͨ��ʱ����ʼ����TIM4��50Hz��
  HAL_TIM_Base_Start_IT(&htim4);
	//============================================================
	//Step3��ABZ��������ʼ��
	HAL_TIM_Encoder_Start(&htim2, TIM_CHANNEL_ALL);
	//============================================================
	//Step4��TIM3_Channel1��2��3ͨ����UVW������������ʼ��
	//			 TIM3_Channel4�������������Ƚϣ���Ϊ��ʱ��
	bldcMotor.enableRun(true);
	bldcMotor.setClockWise(true); 
	
	HAL_TIMEx_HallSensor_Start(&htim3);
	__HAL_TIM_ENABLE_IT(&htim3,TIM_IT_TRIGGER|TIM_IT_CC4);	
	
	//BLDC��������
	bldcMotor.updateHallValue();
	bldcMotor.updatePWMD(10);
	bldcMotor.setSpeed();//����һ�Σ��������
}


///////////////////////////////////////////////////
//�û�ѭ������
void user_loop()
{
		TaskProcess();
}


///////////////////////////////////////////////////
//�δ�ʱ����
void user_systick_fun()
{
		uint8_t i;
		
    for (i=0; i<TASK_MAX; i++)   // �������ʱ�䴦��        
    {
			if ( TaskComps[i].Status)   //��������TASK_ON       
			{
					TaskComps[i].Timer--;     // ��ȥһ������    
					if (TaskComps[i].Timer <= 0)  // ��ʱ��ʱ�䵽
					{
							 TaskComps[i].Timer = TaskComps[i].ItvTime;   // �ָ���ʱ��ֵ��������һ�� 
							 TaskComps[i].Run = 1;    // �����������
					}
			}
		}
}

/////////////////////////////////////////////////////
//TIM3�������������ĺ�����
void user_TIM3_HALL_fun()
{
		bldcMotor.updateHallValue();//���»�����������ֵ
		bldcMotor.setSpeed();	//���ݻ�����������ֵ�������������࣬��ͨ������PWMռ�ձ�������
}


