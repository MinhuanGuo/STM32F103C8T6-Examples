#ifndef __Time_STM_core_H
#define __Time_STM_core_H

#include "stm32f1xx_hal.h"

#define TASK_MAX   2    //��������
#define TASK_ON    1		//��������־
#define TASK_OFF   0		//����رձ�־

typedef struct _TASK_COMPONENTS
{
		uint8_t Status;   // �������б�ǣ�0-�����У�1����									     
    uint8_t Run;    // �������б�ǣ�0-�����У�1����             
    uint16_t Timer; // ��ʱ��            
    uint16_t ItvTime;   // �������м��ʱ��        
    void (*TaskHook)(void);   // Ҫ���е�������  
} TASK_COMPONENTS;   // ������

extern void TaskProcess(void);

extern void taskStart(TASK_COMPONENTS *newTASK,uint8_t que);
extern void taskEnd(TASK_COMPONENTS *newTASK,uint8_t que);


extern TASK_COMPONENTS TaskComps[];
#endif

