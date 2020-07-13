#ifndef __Time_STM_core_H
#define __Time_STM_core_H

#include "stm32f1xx_hal.h"

#define TASK_MAX   2    //任务数量
#define TASK_ON    1		//任务开启标志
#define TASK_OFF   0		//任务关闭标志

typedef struct _TASK_COMPONENTS
{
		uint8_t Status;   // 程序运行标记：0-不运行，1运行									     
    uint8_t Run;    // 程序运行标记：0-不运行，1运行             
    uint16_t Timer; // 计时器            
    uint16_t ItvTime;   // 任务运行间隔时间        
    void (*TaskHook)(void);   // 要运行的任务函数  
} TASK_COMPONENTS;   // 任务定义

extern void TaskProcess(void);

extern void taskStart(TASK_COMPONENTS *newTASK,uint8_t que);
extern void taskEnd(TASK_COMPONENTS *newTASK,uint8_t que);


extern TASK_COMPONENTS TaskComps[];
#endif

