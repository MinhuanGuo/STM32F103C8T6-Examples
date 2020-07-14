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
			// Step1����ȡ���а���ֵ��
			// ret=0����ʾû�а������£�
			// ret=1��2��3�ȣ���ʾ��Ӧ��ŵİ���������
			ret = GetKeyValue();		
			// Step2: ���ݶ����İ���ֵ�����д���
			for(i=0; i<KEYNUMBER; i++)//���δ���ͬ�İ���
			{
				//�Ƿ�ʶ�𵽰���
				if(i+1==ret)
				{
					_KeyCount[i]++;//ʶ�𵽰���֮�󣬶�Ӧ�ļ�����++
				}
				else
				{
					_KeyCount[i] = 0;//û��ʶ�𵽰�������Ӧ�ļ���������
					_KeyFlag &= ~(1<<i);//ͬʱ����Ӧ��FlagλҲ����
				}
				//ʶ�𵽰����󣬼������Ƿ񵽴���Ӧʱ��
				if( _KeyCount[i]==LIMITCOUNT_VALUE)//
				{
					_KeyFlag |= (1<<i);//��Ӧ��Flagλ��1								
				}
				//ʶ�𵽰����󣬼����������趨��ֵ
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
		_KeyFlag &= ~(1<<KeyNumber);//��״̬��һ����Ч
		
		return (Status ? KEYDOWN:KEYUP);//���棬����ǰ��
	}	
	

		
}


