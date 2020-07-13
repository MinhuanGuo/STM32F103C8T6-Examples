#include "master_Control.h"

void Task_LED0(void)
{
	HAL_GPIO_TogglePin(LED0_GPIO_Port,LED0_Pin);
}


void Task_UART2(void)
{
	static char hello[] = "Hello, World!\r\n";
	static char res[10];
	static float ticTime;
	
	sprintf(res,"%4.2f: ",ticTime);
	ticTime+=0.1f;

	//´®¿Ú2·¢ËÍ×Ö·û´®
	HAL_UART_Transmit(&huart2,(uint8_t *)res,std::strlen(res),10);
	HAL_UART_Transmit(&huart2,(uint8_t *)hello,std::strlen(hello),10);	
}










