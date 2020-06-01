#include "main.h"
#include "usart.h"
#include "gpio.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

////////////////
void user_setup()
{
	
}

////////////////
void user_loop()
{
	static char hello[] = "Hello, World!\r\n";
	static char sendString[10];
	static float ticTime;
	
	sprintf(sendString,"%4.2f: ",ticTime);
	ticTime+=0.1f;
	
	//´®¿Ú2·¢ËÍ×Ö·û´®
	HAL_UART_Transmit(&huart2,(uint8_t *)sendString,std::strlen(sendString),10);
	HAL_UART_Transmit(&huart2,(uint8_t *)hello,std::strlen(hello),10);
	
	//¿ØÖÆLED0(PB12)µÆÁÁ¡¢Ãð
	HAL_GPIO_TogglePin(LED0_GPIO_Port,LED0_Pin);
	HAL_Delay(1000);
}



