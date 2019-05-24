#ifndef __SPI_H
#define	__SPI_H

#include "stm32f10x.h"
#include "sys.h"
 /*******
 *�������±���
 KEY_ON 0
 KEY_OFF 1
 ********/
 
void SPI2_Init(void);			 //��ʼ��SPI��
void SPI2_SetSpeed(u8 SpeedSet); //����SPI�ٶ�   
u8 SPI2_ReadWriteByte(u8 TxData);//SPI���߶�дһ���ֽ�

#endif /* __SPI_H */

