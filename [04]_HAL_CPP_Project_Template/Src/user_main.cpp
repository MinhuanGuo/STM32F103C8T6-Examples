#include "main.h"
#include "usart.h"
#include "gpio.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "TSK_STM_core.h"  
#include "master_Control.h"

extern void Task_LED0(void);//����1����תLED0
extern void Task_UART2(void);//����2������2��������

//�������ɸ�����Status��Run��Timer��ItvTime��(*TaskHook)��
TASK_COMPONENTS TaskComps[TASK_MAX] = 
{
		//{Status, Run, Timer, ItvTime, *TaskHook}
		{TASK_ON, 0, 100, 500, Task_LED0}, //
		{TASK_ON, 0, 1, 1000, Task_UART2}, //
}; 
///////////////////////////////////////////////
void user_setup()
{
	//�ȴ�һ���
	HAL_Delay(1000);	
}

///////////////////////////////////////////////
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


