#include "GPIOKey.h"


namespace MH_Hardware{
	_gpio_key::_gpio_key(unsigned long KeyFlag)
	{
		_KeyFlag = KeyFlag;
		_KeyFlagLongPressed = KeyFlag;
	}
	
	unsigned char _gpio_key::GetKeyValue()
	{
			unsigned char KeyValue = 0;
			//KEY1:
			if(KEY1_PRESSED)
				KeyValue = 1;
			//KEY2:
			if(KEY2_PRESSED)
				KeyValue = 2;
			
			return KeyValue;
	}
	
	void  _gpio_key::scan(void)
	{
			
			unsigned char ret;
			unsigned char i;
			// Step1：读取所有按键值，
			// ret=0：表示没有按键按下，
			// ret=1、2、3等，表示对应序号的按键被按下
			ret = GetKeyValue();		
			// Step2: 根据读到的按键值，进行处理
			for(i=0; i<KEYNUMBER; i++)//依次处理不同的按键
			{
				//是否识别到按键
				if(i+1==ret)
				{
					_KeyCount[i]++;//识别到按键之后，对应的计数器++
				}
				else
				{
					_KeyCount[i] = 0;//没有识别到按键，对应的计数器清零
					_KeyFlag &= ~(1<<i);//同时，对应的Flag位也清零
				}
				//识别到按键后，计数器是否到达响应时间
				if( _KeyCount[i]==LIMITCOUNT_VALUE)//
				{
					_KeyFlag |= (1<<i);//对应的Flag位置1								
				}
				//识别到按键后，计数器超过设定阈值
				if(_KeyCount[i] > MAXCOUNT_VALUE)
				{
					_KeyCount[i] = 0;
					_KeyFlag &= ~(1<<i);
				}
			}
	}

	
	unsigned char _gpio_key::GetKeyStatus(unsigned char KeyNumber)
	{
		unsigned long Status;
		
		// Get Status of KeyNumber
		Status = _KeyFlag&(1<<KeyNumber);
				
		// Clear Key Flag
		_KeyFlag &= ~(1<<KeyNumber);//该状态仅一次有效
		
		return (Status ? KEYDOWN:KEYUP);//若真，返回前者
	}	
	

		
}


