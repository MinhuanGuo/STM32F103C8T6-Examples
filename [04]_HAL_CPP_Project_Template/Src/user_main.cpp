#include "main.h"
#include "usart.h"
#include "gpio.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "TSK_STM_core.h"  
#include "master_Control.h"

extern void Task_LED0(void);//任务1：翻转LED0
extern void Task_UART2(void);//任务2：串口2发送数据

//定义若干个任务：Status，Run，Timer，ItvTime，(*TaskHook)；
TASK_COMPONENTS TaskComps[TASK_MAX] = 
{
		//{Status, Run, Timer, ItvTime, *TaskHook}
		{TASK_ON, 0, 100, 500, Task_LED0}, //
		{TASK_ON, 0, 1, 1000, Task_UART2}, //
}; 
///////////////////////////////////////////////
void user_setup()
{
	//等待一会儿
	HAL_Delay(1000);	
}

///////////////////////////////////////////////
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


