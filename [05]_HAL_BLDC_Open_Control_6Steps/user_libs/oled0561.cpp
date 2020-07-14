#include "oled0561.h"
#include "ASCII_8x16.h" //�������� ASCII

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
	DISPLAY_OFF(); //OLED����ʾ
	DISPLAY_CLEAR(); //�����Ļ����
	DISPLAY_ON(); //OLED����ʼֵ���ò�����ʾ	
}
////////////////////////////////
void _oled0561::DISPLAY_ON ()
{
	u8 buf[28]={
	0xae,//0xae:����ʾ��0xaf:����ʾ
  0x00,0x10,//��ʼ��ַ��˫�ֽڣ�       
	0xd5,0x80,//��ʾʱ��Ƶ�ʣ�
	0xa8,0x3f,//�����ʣ�
	0xd3,0x00,//��ʾƫ�ƣ�
	0XB0,//д��ҳλ�ã�0xB0~7��
	0x40,//��ʾ��ʼ��
	0x8d,0x14,//VCC��Դ
	0xa1,//���ö�����ӳ�䣿
	0xc8,//COM�����ʽ��
	0xda,0x12,//COM�����ʽ��
	0x81,0xff,//�Աȶȣ�ָ�0x81�����ݣ�0~255��255��ߣ�
	0xd9,0xf1,//������ڣ�
	0xdb,0x30,//VCC��ѹ���
	0x20,0x00,//ˮƽѰַ����
	0xa4,//0xa4:������ʾ��0xa5:�������
	0xa6,//0xa6:������ʾ��0xa7:��ɫ��ʾ
	0xaf//0xae:����ʾ��0xaf:����ʾ
	}; //
	HAL_I2C_Mem_Write(_hi2c,_address,_COM,1,buf,28,10);
	
	
	////////////////
	u8 _buffer[2] = {3,4};
	
	HAL_I2C_Mem_Read(_hi2c,_address,_COM,1,_buffer,1,100);//��ȡ�Ĵ�����У��
	HAL_I2C_Mem_Read(_hi2c,_address,_COM,1,&_buffer[1],1,100);
	_buffer[1]=_buffer[1]+0;
	_buffer[1]=_buffer[1]+0;
		
}
void _oled0561::DISPLAY_OFF ()
{
	u8 buf[3]={
		0xae,//0xae:����ʾ��0xaf:����ʾ
		0x8d,0x10,//VCC��Դ
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
	for(t=0xB0;t<0xB8;t++){	//������ʼҳ��ַΪ0xB0
		HAL_I2C_Mem_Write(_hi2c,_address,_COM,1,&t,1,10);//ҳ��ַ����0xB0��0xB7��
		HAL_I2C_Mem_Write(_hi2c,_address,_COM,1,&buf[1],1,10);//��ʼ�е�ַ�ĸ�4λ
		HAL_I2C_Mem_Write(_hi2c,_address,_COM,1,buf,1,10);//��ʼ�е�ַ�ĵ�4λ

		for(j=0;j<132;j++){	//��ҳ�������
 			HAL_I2C_Mem_Write(_hi2c,_address,_DAT,1,buf,1,10);
 		}
	}	
}



void _oled0561::DISPLAY_8x16(u8 x,u8 y,u16 w)//��ʾ8x16�ĵ����ַ�
{
	u8 tmp;
	u8 j,t,c=0;
	y=y+2; //��OLED������������оƬ�Ǵ�0x02����Ϊ��������һ�У�����Ҫ����ƫ����
	for(t=0;t<2;t++){
		tmp = 0xb0+x;
		HAL_I2C_Mem_Write(_hi2c,_address,_COM,1,&tmp,1,10); //ҳ��ַ����0xB0��0xB7��
		tmp = y/16+0x10;
		HAL_I2C_Mem_Write(_hi2c,_address,_COM,1,&tmp,1,10);//��ʼ�е�ַ�ĸ�4λ
		tmp = y%16;
		HAL_I2C_Mem_Write(_hi2c,_address,_COM,1,&tmp,1,10);//��ʼ�е�ַ�ĵ�4λ
		
		for(j=0;j<8;j++){ //��ҳ�������
			tmp = ASCII_8x16[(w*16)+c-512];//Ϊ�˺�ASII���ӦҪ��512
			HAL_I2C_Mem_Write(_hi2c,_address,_DAT,1,&tmp,1,10);
			c++;}x++; //ҳ��ַ��1
	}	
}	
void _oled0561::DISPLAY_8x16_BUFFER(u8 row,u8 *str)//��ʾ8x16���ַ���
{
	u8 r=0;
	while(*str != '\0'){
		DISPLAY_8x16(row,r*8,*str++);
		r++;
    }		
}


}



















