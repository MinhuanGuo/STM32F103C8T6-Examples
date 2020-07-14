#include "oled0561.h"
#include "ASCII_8x16.h" //引入字体 ASCII

namespace MH_Hardware{

_oled0561::_oled0561(u8 addr)
{
	_address = addr;
	_hi2c = &hi2c1;
	_COM = 0x00;
	_DAT = 0x40;
}


void _oled0561::Init()
{
	DISPLAY_OFF(); //OLED关显示
	DISPLAY_CLEAR(); //清空屏幕内容
	DISPLAY_ON(); //OLED屏初始值设置并开显示	
}
////////////////////////////////
void _oled0561::DISPLAY_ON ()
{
	u8 buf[28]={
	0xae,//0xae:关显示，0xaf:开显示
  0x00,0x10,//开始地址（双字节）       
	0xd5,0x80,//显示时钟频率？
	0xa8,0x3f,//复用率？
	0xd3,0x00,//显示偏移？
	0XB0,//写入页位置（0xB0~7）
	0x40,//显示开始线
	0x8d,0x14,//VCC电源
	0xa1,//设置段重新映射？
	0xc8,//COM输出方式？
	0xda,0x12,//COM输出方式？
	0x81,0xff,//对比度，指令：0x81，数据：0~255（255最高）
	0xd9,0xf1,//充电周期？
	0xdb,0x30,//VCC电压输出
	0x20,0x00,//水平寻址设置
	0xa4,//0xa4:正常显示，0xa5:整体点亮
	0xa6,//0xa6:正常显示，0xa7:反色显示
	0xaf//0xae:关显示，0xaf:开显示
	}; //
	HAL_I2C_Mem_Write(_hi2c,_address,_COM,1,buf,28,10);
	
	
	////////////////
	u8 _buffer[2] = {3,4};
	
	HAL_I2C_Mem_Read(_hi2c,_address,_COM,1,_buffer,1,100);//读取寄存器，校验
	HAL_I2C_Mem_Read(_hi2c,_address,_COM,1,&_buffer[1],1,100);
	_buffer[1]=_buffer[1]+0;
	_buffer[1]=_buffer[1]+0;
		
}
void _oled0561::DISPLAY_OFF ()
{
	u8 buf[3]={
		0xae,//0xae:关显示，0xaf:开显示
		0x8d,0x10,//VCC电源
	}; //
	HAL_I2C_Mem_Write(_hi2c,_address,_COM,1,buf,3,10);
}
void _oled0561::DISPLAY_LIT (u8 x)
{
	u8 buf[2]={0x81};
	buf[1] = x;
	HAL_I2C_Mem_Write(_hi2c,_address,_COM,1,buf,1,10);
	HAL_I2C_Mem_Write(_hi2c,_address,_COM,1,&buf[1],1,10);
	
}

void _oled0561::DISPLAY_CLEAR ()
{
	u8 j,t;
	u8 buf[2] = {0x00,0x10};
	for(t=0xB0;t<0xB8;t++){	//设置起始页地址为0xB0
		HAL_I2C_Mem_Write(_hi2c,_address,_COM,1,&t,1,10);//页地址（从0xB0到0xB7）
		HAL_I2C_Mem_Write(_hi2c,_address,_COM,1,&buf[1],1,10);//起始列地址的高4位
		HAL_I2C_Mem_Write(_hi2c,_address,_COM,1,buf,1,10);//起始列地址的低4位

		for(j=0;j<132;j++){	//整页内容填充
 			HAL_I2C_Mem_Write(_hi2c,_address,_DAT,1,buf,1,10);
 		}
	}	
}



void _oled0561::DISPLAY_8x16(u8 x,u8 y,u16 w)//显示8x16的单个字符
{
	u8 tmp;
	u8 j,t,c=0;
	y=y+2; //因OLED屏的内置驱动芯片是从0x02列作为屏上最左一列，所以要加上偏移量
	for(t=0;t<2;t++){
		tmp = 0xb0+x;
		HAL_I2C_Mem_Write(_hi2c,_address,_COM,1,&tmp,1,10); //页地址（从0xB0到0xB7）
		tmp = y/16+0x10;
		HAL_I2C_Mem_Write(_hi2c,_address,_COM,1,&tmp,1,10);//起始列地址的高4位
		tmp = y%16;
		HAL_I2C_Mem_Write(_hi2c,_address,_COM,1,&tmp,1,10);//起始列地址的低4位
		
		for(j=0;j<8;j++){ //整页内容填充
			tmp = ASCII_8x16[(w*16)+c-512];//为了和ASII表对应要减512
			HAL_I2C_Mem_Write(_hi2c,_address,_DAT,1,&tmp,1,10);
			c++;}x++; //页地址加1
	}	
}	
void _oled0561::DISPLAY_8x16_BUFFER(u8 row,u8 *str)//显示8x16的字符串
{
	u8 r=0;
	while(*str != '\0'){
		DISPLAY_8x16(row,r*8,*str++);
		r++;
    }		
}


}



















