#include "bldc_motor.h"

namespace MH_Hardware{
	
	_bldc_motor::_bldc_motor(uint8_t hall)
	{
		_tim1_handle = &htim1;
		_isEnable = false;//默认停机
		_isClockWise = true;//默认顺时针
		_hallStep = hall;//Hall传感器的值，默认用0x00初始化
		_hallStepCount = 0;//Hall传感器计数值，用来计算速度
		_pwmPercent = 30;//默认占空比30%
		
	}
	
	//B+，C-
	void _bldc_motor::setBLDC_Phase1(uint8_t _pwmPercent)
	{
		uint16_t pulsePWM = _pwmPercent * TIM1_PERIOD_DEFAULT/100;
		uint16_t pulseON = TIM1_PERIOD_DEFAULT;
		
		//A
		HAL_TIM_PWM_Stop(_tim1_handle, TIM_CHANNEL_1);
		HAL_TIMEx_PWMN_Stop(_tim1_handle, TIM_CHANNEL_1);		

		//B+
		sPWMConfig2.OCMode = TIM_OCMODE_PWM1;
		sPWMConfig2.Pulse      = pulsePWM;
		
		HAL_TIM_PWM_ConfigChannel(_tim1_handle, &sPWMConfig2, TIM_CHANNEL_2); 
		HAL_TIM_PWM_Start(_tim1_handle, TIM_CHANNEL_2);	
		HAL_TIMEx_PWMN_Start(_tim1_handle, TIM_CHANNEL_2);
		
		//C-
		sPWMConfig3.OCMode = TIM_OCMODE_PWM1;
		sPWMConfig3.Pulse      = pulseON;
		
		HAL_TIM_PWM_ConfigChannel(_tim1_handle, &sPWMConfig3, TIM_CHANNEL_3); 
		HAL_TIMEx_PWMN_Start(_tim1_handle, TIM_CHANNEL_3);			
	}
	
	//A+ B-
	void _bldc_motor::setBLDC_Phase2(uint8_t _pwmPercent)
	{
			uint16_t pulsePWM = _pwmPercent * TIM1_PERIOD_DEFAULT/100;
			uint16_t pulseON = TIM1_PERIOD_DEFAULT;
		
			//C
			HAL_TIM_PWM_Stop(_tim1_handle, TIM_CHANNEL_3);
			HAL_TIMEx_PWMN_Stop(_tim1_handle, TIM_CHANNEL_3);	
		
			//A+
			sPWMConfig1.OCMode = TIM_OCMODE_PWM1;
			sPWMConfig1.Pulse      = pulsePWM;
			
			HAL_TIM_PWM_ConfigChannel(_tim1_handle, &sPWMConfig1, TIM_CHANNEL_1); 
			HAL_TIM_PWM_Start(_tim1_handle, TIM_CHANNEL_1);	
			HAL_TIMEx_PWMN_Start(_tim1_handle, TIM_CHANNEL_1);	

			//B-
			sPWMConfig2.OCMode = TIM_OCMODE_PWM1;
			sPWMConfig2.Pulse      = pulseON;
			
			HAL_TIM_PWM_ConfigChannel(_tim1_handle, &sPWMConfig2, TIM_CHANNEL_2);
			HAL_TIM_PWM_Stop(_tim1_handle, TIM_CHANNEL_2);
			HAL_TIMEx_PWMN_Start(_tim1_handle, TIM_CHANNEL_2);			
	}	
	
	//A+ C-
	void _bldc_motor::setBLDC_Phase3(uint8_t _pwmPercent)
	{
			uint16_t pulsePWM = _pwmPercent * TIM1_PERIOD_DEFAULT/100;
			uint16_t pulseON = TIM1_PERIOD_DEFAULT;
		
			//B
			HAL_TIM_PWM_Stop(_tim1_handle, TIM_CHANNEL_2);
			HAL_TIMEx_PWMN_Stop(_tim1_handle, TIM_CHANNEL_2);	
		
			//A+
			sPWMConfig1.OCMode = TIM_OCMODE_PWM1;
			sPWMConfig1.Pulse      = pulsePWM;
			
			HAL_TIM_PWM_ConfigChannel(_tim1_handle, &sPWMConfig1, TIM_CHANNEL_1); 
			HAL_TIM_PWM_Start(_tim1_handle, TIM_CHANNEL_1);	
			HAL_TIMEx_PWMN_Start(_tim1_handle, TIM_CHANNEL_1);	

			//C-
			sPWMConfig3.OCMode = TIM_OCMODE_PWM1;
			sPWMConfig3.Pulse      = pulseON;
			
			HAL_TIM_PWM_ConfigChannel(_tim1_handle, &sPWMConfig3, TIM_CHANNEL_3); 
			HAL_TIM_PWM_Stop(_tim1_handle, TIM_CHANNEL_3);
			HAL_TIMEx_PWMN_Start(_tim1_handle, TIM_CHANNEL_3);		
	}	
	
	//C+ A-
	void _bldc_motor::setBLDC_Phase4(uint8_t _pwmPercent)
	{
			uint16_t pulsePWM = _pwmPercent * TIM1_PERIOD_DEFAULT/100;
			uint16_t pulseON = TIM1_PERIOD_DEFAULT;
		
			//B
			HAL_TIM_PWM_Stop(_tim1_handle, TIM_CHANNEL_2);
			HAL_TIMEx_PWMN_Stop(_tim1_handle, TIM_CHANNEL_2);	
		
			//C+
			sPWMConfig3.OCMode = TIM_OCMODE_PWM1;
			sPWMConfig3.Pulse      = pulsePWM;
			
			HAL_TIM_PWM_ConfigChannel(_tim1_handle, &sPWMConfig3, TIM_CHANNEL_3); 
			HAL_TIM_PWM_Start(_tim1_handle, TIM_CHANNEL_3);	
			HAL_TIMEx_PWMN_Start(_tim1_handle, TIM_CHANNEL_3);

			//A-
			sPWMConfig1.OCMode = TIM_OCMODE_PWM1;
			sPWMConfig1.Pulse      = pulseON;
			
			HAL_TIM_PWM_ConfigChannel(_tim1_handle, &sPWMConfig1, TIM_CHANNEL_1);
			HAL_TIM_PWM_Stop(_tim1_handle, TIM_CHANNEL_1);	
			HAL_TIMEx_PWMN_Start(_tim1_handle, TIM_CHANNEL_1);

	}	
	
	//B+ A-
	void _bldc_motor::setBLDC_Phase5(uint8_t _pwmPercent)
	{
			uint16_t pulsePWM = _pwmPercent * TIM1_PERIOD_DEFAULT/100;
			uint16_t pulseON = TIM1_PERIOD_DEFAULT;
			//C
			HAL_TIM_PWM_Stop(_tim1_handle, TIM_CHANNEL_3);
			HAL_TIMEx_PWMN_Stop(_tim1_handle, TIM_CHANNEL_3);	
		
			//B+
			sPWMConfig2.OCMode = TIM_OCMODE_PWM1;
			sPWMConfig2.Pulse      = pulsePWM;
			
			HAL_TIM_PWM_ConfigChannel(_tim1_handle, &sPWMConfig2, TIM_CHANNEL_2); 
			HAL_TIM_PWM_Start(_tim1_handle, TIM_CHANNEL_2);	
			HAL_TIMEx_PWMN_Start(_tim1_handle, TIM_CHANNEL_2);

			//A-
			sPWMConfig1.OCMode = TIM_OCMODE_PWM1;
			sPWMConfig1.Pulse      = pulseON;
			
			HAL_TIM_PWM_ConfigChannel(_tim1_handle, &sPWMConfig1, TIM_CHANNEL_1);
			HAL_TIM_PWM_Stop(_tim1_handle, TIM_CHANNEL_1);
			HAL_TIMEx_PWMN_Start(_tim1_handle, TIM_CHANNEL_1);		
	}	
	
	//C+ B-
	void _bldc_motor::setBLDC_Phase6(uint8_t _pwmPercent)
	{
			uint16_t pulsePWM = _pwmPercent * TIM1_PERIOD_DEFAULT/100;
			uint16_t pulseON = TIM1_PERIOD_DEFAULT;
		
			//A
			HAL_TIM_PWM_Stop(_tim1_handle, TIM_CHANNEL_1);
			HAL_TIMEx_PWMN_Stop(_tim1_handle, TIM_CHANNEL_1);	
		
			//C+
			sPWMConfig3.OCMode = TIM_OCMODE_PWM1;
			sPWMConfig3.Pulse      = pulsePWM;
			
			HAL_TIM_PWM_ConfigChannel(_tim1_handle, &sPWMConfig3, TIM_CHANNEL_3); 
			HAL_TIM_PWM_Start(_tim1_handle, TIM_CHANNEL_3);	
			HAL_TIMEx_PWMN_Start(_tim1_handle, TIM_CHANNEL_3);

			//B-
			sPWMConfig2.OCMode = TIM_OCMODE_PWM1;
			sPWMConfig2.Pulse      = pulseON;
			
			HAL_TIM_PWM_ConfigChannel(_tim1_handle, &sPWMConfig2, TIM_CHANNEL_2);
			HAL_TIM_PWM_Stop(_tim1_handle, TIM_CHANNEL_2);
			HAL_TIMEx_PWMN_Start(_tim1_handle, TIM_CHANNEL_2);			
	}	
	
	void _bldc_motor::BLDC_PHASE_CHANGE(uint8_t _hallStep, uint8_t _pwmPercent)
	{
		switch(_hallStep)
		{
			//+:PWM导通， 上下管采用互补PWM，D = pulse/period，pulse可以由转速计算得到
			//-:ON全导通，上管关闭，下管导通，D = 100%
			case 4: //A- C+
				setBLDC_Phase4(_pwmPercent);			
				break;
			case 5: //A- B+
				setBLDC_Phase5(_pwmPercent);			
				break;
			case 1: //B+ C-
				setBLDC_Phase1(_pwmPercent);				
				break;
			case 3: //A+ C-
				setBLDC_Phase3(_pwmPercent);
				break;
			case 2: //A+ B-
				setBLDC_Phase2(_pwmPercent);
				break;
			case 6: //B- C+
				setBLDC_Phase6(_pwmPercent);
				break;
			default:
				HAL_TIM_PWM_Stop(_tim1_handle, TIM_CHANNEL_1);
				HAL_TIMEx_PWMN_Stop(_tim1_handle, TIM_CHANNEL_1);	
				HAL_TIM_PWM_Stop(_tim1_handle, TIM_CHANNEL_2);
				HAL_TIMEx_PWMN_Stop(_tim1_handle, TIM_CHANNEL_2);	
				HAL_TIM_PWM_Stop(_tim1_handle, TIM_CHANNEL_3);
				HAL_TIMEx_PWMN_Stop(_tim1_handle, TIM_CHANNEL_3);		
				break;
		}		
	}



		void _bldc_motor::enableRun(bool isRUN)
		{
			_isEnable = isRUN;
		}
		
		void _bldc_motor::setClockWise(bool isCW)
		{
			_isClockWise = isCW;
		}
	
	void _bldc_motor::updateHallValue(void)
	{
		uint8_t pinState = 0x00;
		static __IO int8_t pinState0 = 0;
		
		if( (HALL_U_GPIO_Port->IDR & HALL_U_Pin) != GPIO_PIN_RESET )
		{
			pinState |= 0x04;
		}
		if( (HALL_V_GPIO_Port->IDR & HALL_V_Pin) != GPIO_PIN_RESET )
		{
			pinState |= 0x02;
		}
		if( (HALL_W_GPIO_Port->IDR & HALL_W_Pin) != GPIO_PIN_RESET )
		{
			pinState |= 0x01;
		}
		
		if(pinState0 != pinState)
		{
			_hallStepCount++;//更新hall传感器状态变化的累计值
			pinState0 = pinState;
		}	
		_hallStep = pinState;//更新hall传感器状态
	}
	
	uint8_t _bldc_motor::getHallValue(void)
	{
		return _hallStep;
	}
	
	void _bldc_motor::updatePWMD(uint8_t userPWMPercent)
	{
		_pwmPercent = userPWMPercent;
	}
	
	uint16_t _bldc_motor::getPWMD()
	{
		return _pwmPercent;
	}
	
	
	void _bldc_motor::setSpeed()
	{
		if(_isEnable)//RUN
		{			
				if(_isClockWise)
				{
					BLDC_PHASE_CHANGE(_hallStep,_pwmPercent);
				}
				else
				{
					BLDC_PHASE_CHANGE((7-_hallStep),_pwmPercent);
				}
		}
		else//STOP
		{
				HAL_TIM_PWM_Stop(_tim1_handle, TIM_CHANNEL_1);
				HAL_TIMEx_PWMN_Stop(_tim1_handle, TIM_CHANNEL_1);	

				HAL_TIM_PWM_Stop(_tim1_handle, TIM_CHANNEL_2);
				HAL_TIMEx_PWMN_Stop(_tim1_handle, TIM_CHANNEL_2);	

				HAL_TIM_PWM_Stop(_tim1_handle, TIM_CHANNEL_3);
				HAL_TIMEx_PWMN_Stop(_tim1_handle, TIM_CHANNEL_3);				
		}

	}
	
	uint16_t _bldc_motor::getHallCount(void)
	{
		return _hallStepCount;
	}
	
	void _bldc_motor::clearHallCount(void)
	{
		_hallStepCount = 0;
	}
	
	bool _bldc_motor::getDir(void)
	{
		return _isClockWise;
	}
	
	void _bldc_motor::calculateRPM(uint16_t delayMS)
	{
		//转子共有8个磁极，即4对极，
		//360°E = 90°M
		//六分之一个电周期，对应机械角度15°
		//   1°/s = 1/6 RPM
			float degPsec;
			degPsec = (float)(15.0f * _hallStepCount )/((float)delayMS/1000.0f);
			_rpm	= degPsec/6.0f;
	}
	
	float _bldc_motor::getRPM(void)
	{
		return _rpm;
	}
}

