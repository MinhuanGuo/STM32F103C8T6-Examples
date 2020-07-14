#include "TSK_STM_core.h" 

/**************************************************************************************
* FunctionName   : TaskProcess()
* Description    : 任务处理
* EntryParameter : None
* ReturnValue    : None
**************************************************************************************/
void TaskProcess(void)
{
    uint8_t i;
    for (i=0; i<TASK_MAX; i++)           // 逐个任务时间处理
    {
        if (TaskComps[i].Run)           // 程序运行
        {
						 TaskComps[i].TaskHook();       // 运行任务
             TaskComps[i].Run = 0;          // 标志清0
        }
    }
}


/**************************************************************************************
* FunctionName   : taskStart
* Description    : 使能任务
* EntryParameter : None
* ReturnValue    : None
**************************************************************************************/
void taskStart(TASK_COMPONENTS *newTASK,uint8_t que)
{
	 newTASK[que].Status=	TASK_ON;
}
/**************************************************************************************
* FunctionName   : taskOff
* Description    : 失能任务
* EntryParameter : None
* ReturnValue    : None
**************************************************************************************/
void taskEnd(TASK_COMPONENTS *newTASK,uint8_t que)
{
	 newTASK[que].Status=	TASK_OFF;
}


