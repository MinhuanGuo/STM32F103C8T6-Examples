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
		void Init(void);//初始化
		void DISPLAY_ON (void);//OLED屏开显示
		void DISPLAY_OFF (void);//OLED屏关显示
		void DISPLAY_LIT (u8 x);//OLED屏亮度设置（0~255）
		void DISPLAY_CLEAR(void);//清屏操作
		void DISPLAY_8x16(u8 x,u8 y,u16 w);//显示8x16的单个字符 
		void DISPLAY_8x16_BUFFER(u8 row,u8 *str);//显示8x16的字符串

		void DISPLAY_16x16(u8 x,u8 y,u16 w); //汉字显示
		void DISPLAY_PIC1(void);//图片显示
		
	
};

}






#endif
