#include "TSK_STM_core.h" 

/**************************************************************************************
* FunctionName   : TaskProcess()
* Description    : ������
* EntryParameter : None
* ReturnValue    : None
**************************************************************************************/
void TaskProcess(void)
{
    uint8_t i;
    for (i=0; i<TASK_MAX; i++)           // �������ʱ�䴦��
    {
        if (TaskComps[i].Run)           // ��������
        {
						 TaskComps[i].TaskHook();       // ��������
             TaskComps[i].Run = 0;          // ��־��0
        }
    }
}


/**************************************************************************************
* FunctionName   : taskStart
* Description    : ʹ������
* EntryParameter : None
* ReturnValue    : None
**************************************************************************************/
void taskStart(TASK_COMPONENTS *newTASK,uint8_t que)
{
	 newTASK[que].Status=	TASK_ON;
}
/**************************************************************************************
* FunctionName   : taskOff
* Description    : ʧ������
* EntryParameter : None
* ReturnValue    : None
**************************************************************************************/
void taskEnd(TASK_COMPONENTS *newTASK,uint8_t que)
{
	 newTASK[que].Status=	TASK_OFF;
}


