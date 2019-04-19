#ifndef __SPI_H
#define	__SPI_H

#include "stm32f10x.h"
#include "sys.h"
 /*******
 *按键按下标置
 KEY_ON 0
 KEY_OFF 1
 ********/
 
void SPI2_Init(void);			 //初始化SPI口
void SPI2_SetSpeed(u8 SpeedSet); //设置SPI速度   
u8 SPI2_ReadWriteByte(u8 TxData);//SPI总线读写一个字节

#endif /* __SPI_H */

