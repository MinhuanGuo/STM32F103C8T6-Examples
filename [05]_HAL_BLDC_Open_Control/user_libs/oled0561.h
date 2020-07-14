#ifndef __oled0561_H
#define __oled0561_H

#include "stm32f1xx_hal.h"
#include "time.h"
#include "string.h"
#include "i2c.h"


typedef uint8_t u8;
typedef uint16_t u16;


	
namespace MH_Hardware{

class _oled0561{
	private:
		u8 _address;
		I2C_HandleTypeDef *_hi2c;
		u8 _COM;
		u8 _DAT;
		
	public:
		_oled0561(u8 addr);
		void Init(void);//��ʼ��
		void DISPLAY_ON (void);//OLED������ʾ
		void DISPLAY_OFF (void);//OLED������ʾ
		void DISPLAY_LIT (u8 x);//OLED���������ã�0~255��
		void DISPLAY_CLEAR(void);//��������
		void DISPLAY_8x16(u8 x,u8 y,u16 w);//��ʾ8x16�ĵ����ַ� 
		void DISPLAY_8x16_BUFFER(u8 row,u8 *str);//��ʾ8x16���ַ���

		void DISPLAY_16x16(u8 x,u8 y,u16 w); //������ʾ
		void DISPLAY_PIC1(void);//ͼƬ��ʾ
		
	
};

}






#endif
