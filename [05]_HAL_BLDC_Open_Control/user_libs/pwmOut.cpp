#include "pwmOut.h"

void setPWM(TIM_HandleTypeDef timer, uint32_t channel, uint16_t period,uint16_t pulse)
{
	 HAL_TIM_PWM_Stop(&timer, channel); // stop generation of pwm
	 TIM_OC_InitTypeDef sConfigOC;
	 timer.Init.Period = period; // set the period duration
	 HAL_TIM_PWM_Init(&timer); // reinititialise with new period value
	 sConfigOC.OCMode = TIM_OCMODE_PWM1;
	 sConfigOC.Pulse = pulse; // set the pulse duration
	 
	 sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
	 sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;

	 HAL_TIM_PWM_ConfigChannel(&timer, &sConfigOC, channel);
	 HAL_TIM_PWM_Start(&timer, channel); // start pwm generation	
}


void setUVW_PWM(uint16_t period,uint16_t pulseU,uint16_t pulseV,uint16_t pulseW)
{
	 //TIM_HandleTypeDef timer = htim1;//TIM1
	 //uint32_t channel = TIM_CHANNEL_3;//Channel_3 and Channel_3N
	
	 HAL_TIM_PWM_Stop(&htim1, TIM_CHANNEL_ALL); // stop generation of pwm
	 htim1.Init.Period = period;
	 HAL_TIM_PWM_Init(&htim1);	
	
	 TIM_OC_InitTypeDef sConfigOC;
	 sConfigOC.OCMode = TIM_OCMODE_PWM1;
	 //timer.Init.Period = period; // set the period duration
	 
	 //HAL_TIM_PWM_Init(&timer); // reinititialise with new period value
	 

		
   
	 //sConfigOC.OCNPolarity = TIM_OCPOLARITY_HIGH;
	//Channel 1:
	 sConfigOC.Pulse = pulseU; // set the pulse duration 
	 sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
	 sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
	
	 HAL_TIM_PWM_ConfigChannel(&htim1, &sConfigOC, TIM_CHANNEL_1);
	 //Channel 2:
	 sConfigOC.Pulse = pulseV; // set the pulse duration 
	 sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
	 sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
	
	 HAL_TIM_PWM_ConfigChannel(&htim1, &sConfigOC, TIM_CHANNEL_2);	 
	 //Channel 3:
	 sConfigOC.Pulse = pulseW; // set the pulse duration 
	 sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
	 sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
	
	 HAL_TIM_PWM_ConfigChannel(&htim1, &sConfigOC, TIM_CHANNEL_3);	 
	 
	 /////////////////////////////////////////////////////////
	 //Start all channels:
	 HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1); // start pwm generation
	 HAL_TIMEx_PWMN_Start(&htim1, TIM_CHANNEL_1);
	 HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_2); // start pwm generation
	 HAL_TIMEx_PWMN_Start(&htim1, TIM_CHANNEL_2);
	 HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_3); // start pwm generation
	 HAL_TIMEx_PWMN_Start(&htim1, TIM_CHANNEL_3);	
	
}
/*********************************************/
/*********************************************/
//B+ C-
void setBLDC_Phase1(uint16_t pulseU, uint16_t pulseV, uint16_t pulseW)
{
		//A
		HAL_TIM_PWM_Stop(&htim1, TIM_CHANNEL_1);
		HAL_TIMEx_PWMN_Stop(&htim1, TIM_CHANNEL_1);	
	
		//B+
		sPWMConfig2.OCMode = TIM_OCMODE_PWM1;
		sPWMConfig2.Pulse      = pulseV;
		
		HAL_TIM_PWM_ConfigChannel(&htim1, &sPWMConfig2, TIM_CHANNEL_2); 
		HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_2);	
		HAL_TIMEx_PWMN_Start(&htim1, TIM_CHANNEL_2);	

		//C-
		sPWMConfig3.OCMode = TIM_OCMODE_PWM1;
		sPWMConfig3.Pulse      = pulseW;
		
		HAL_TIM_PWM_ConfigChannel(&htim1, &sPWMConfig3, TIM_CHANNEL_3); 
		HAL_TIMEx_PWMN_Start(&htim1, TIM_CHANNEL_3);		
}

//B+ A-
void setBLDC_Phase5(uint16_t pulseU,uint16_t pulseV,uint16_t pulseW)
{
		//C
		HAL_TIM_PWM_Stop(&htim1, TIM_CHANNEL_3);
		HAL_TIMEx_PWMN_Stop(&htim1, TIM_CHANNEL_3);	
	
		//B+
		sPWMConfig2.OCMode = TIM_OCMODE_PWM1;
		sPWMConfig2.Pulse      = pulseV;
		
		HAL_TIM_PWM_ConfigChannel(&htim1, &sPWMConfig2, TIM_CHANNEL_2); 
		HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_2);	
		HAL_TIMEx_PWMN_Start(&htim1, TIM_CHANNEL_2);

		//A-
		sPWMConfig1.OCMode = TIM_OCMODE_PWM1;
		sPWMConfig1.Pulse      = pulseU;
		
		HAL_TIM_PWM_ConfigChannel(&htim1, &sPWMConfig1, TIM_CHANNEL_1);
		HAL_TIM_PWM_Stop(&htim1, TIM_CHANNEL_1);
		HAL_TIMEx_PWMN_Start(&htim1, TIM_CHANNEL_1);		
}
//C+ A-
void setBLDC_Phase4(uint16_t pulseU,uint16_t pulseV,uint16_t pulseW)
{
		//B
		HAL_TIM_PWM_Stop(&htim1, TIM_CHANNEL_2);
		HAL_TIMEx_PWMN_Stop(&htim1, TIM_CHANNEL_2);	
	
		//C+
		sPWMConfig3.OCMode = TIM_OCMODE_PWM1;
		sPWMConfig3.Pulse      = pulseW;
		
		HAL_TIM_PWM_ConfigChannel(&htim1, &sPWMConfig3, TIM_CHANNEL_3); 
		HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_3);	
		HAL_TIMEx_PWMN_Start(&htim1, TIM_CHANNEL_3);

		//A-
		sPWMConfig1.OCMode = TIM_OCMODE_PWM1;
		sPWMConfig1.Pulse      = pulseU;
		
		HAL_TIM_PWM_ConfigChannel(&htim1, &sPWMConfig1, TIM_CHANNEL_1);
		HAL_TIM_PWM_Stop(&htim1, TIM_CHANNEL_1);	
		HAL_TIMEx_PWMN_Start(&htim1, TIM_CHANNEL_1);

}
//C+ B-
void setBLDC_Phase6(uint16_t pulseU,uint16_t pulseV,uint16_t pulseW)
{
		//A
		HAL_TIM_PWM_Stop(&htim1, TIM_CHANNEL_1);
		HAL_TIMEx_PWMN_Stop(&htim1, TIM_CHANNEL_1);	
	
		//C+
		sPWMConfig3.OCMode = TIM_OCMODE_PWM1;
		sPWMConfig3.Pulse      = pulseW;
		
		HAL_TIM_PWM_ConfigChannel(&htim1, &sPWMConfig3, TIM_CHANNEL_3); 
		HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_3);	
		HAL_TIMEx_PWMN_Start(&htim1, TIM_CHANNEL_3);

		//B-
		sPWMConfig2.OCMode = TIM_OCMODE_PWM1;
		sPWMConfig2.Pulse      = pulseV;
		
		HAL_TIM_PWM_ConfigChannel(&htim1, &sPWMConfig2, TIM_CHANNEL_2);
		HAL_TIM_PWM_Stop(&htim1, TIM_CHANNEL_2);
		HAL_TIMEx_PWMN_Start(&htim1, TIM_CHANNEL_2);			
}
//A+ B-
void setBLDC_Phase2(uint16_t pulseU,uint16_t pulseV,uint16_t pulseW)
{
		//C
		HAL_TIM_PWM_Stop(&htim1, TIM_CHANNEL_3);
		HAL_TIMEx_PWMN_Stop(&htim1, TIM_CHANNEL_3);	
	
		//A+
		sPWMConfig1.OCMode = TIM_OCMODE_PWM1;
		sPWMConfig1.Pulse      = pulseU;
		
		HAL_TIM_PWM_ConfigChannel(&htim1, &sPWMConfig1, TIM_CHANNEL_1); 
		HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);	
		HAL_TIMEx_PWMN_Start(&htim1, TIM_CHANNEL_1);	

		//B-
		sPWMConfig2.OCMode = TIM_OCMODE_PWM1;
		sPWMConfig2.Pulse      = pulseV;
		
		HAL_TIM_PWM_ConfigChannel(&htim1, &sPWMConfig2, TIM_CHANNEL_2);
		HAL_TIM_PWM_Stop(&htim1, TIM_CHANNEL_2);
		HAL_TIMEx_PWMN_Start(&htim1, TIM_CHANNEL_2);			
}
//A+ C-
void setBLDC_Phase3(uint16_t pulseU,uint16_t pulseV,uint16_t pulseW)
{
		//B
		HAL_TIM_PWM_Stop(&htim1, TIM_CHANNEL_2);
		HAL_TIMEx_PWMN_Stop(&htim1, TIM_CHANNEL_2);	
	
		//A+
		sPWMConfig1.OCMode = TIM_OCMODE_PWM1;
		sPWMConfig1.Pulse      = pulseU;
		
		HAL_TIM_PWM_ConfigChannel(&htim1, &sPWMConfig1, TIM_CHANNEL_1); 
		HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);	
		HAL_TIMEx_PWMN_Start(&htim1, TIM_CHANNEL_1);	

		//C-
		sPWMConfig3.OCMode = TIM_OCMODE_PWM1;
		sPWMConfig3.Pulse      = pulseW;
		
		HAL_TIM_PWM_ConfigChannel(&htim1, &sPWMConfig3, TIM_CHANNEL_3); 
		HAL_TIM_PWM_Stop(&htim1, TIM_CHANNEL_3);
		HAL_TIMEx_PWMN_Start(&htim1, TIM_CHANNEL_3);		
}

void stopBLDC(void)
{
		HAL_TIM_PWM_Stop(&htim1, TIM_CHANNEL_1);
		HAL_TIMEx_PWMN_Stop(&htim1, TIM_CHANNEL_1);	
		HAL_TIM_PWM_Stop(&htim1, TIM_CHANNEL_2);
		HAL_TIMEx_PWMN_Stop(&htim1, TIM_CHANNEL_2);	
		HAL_TIM_PWM_Stop(&htim1, TIM_CHANNEL_3);
		HAL_TIMEx_PWMN_Stop(&htim1, TIM_CHANNEL_3);		
}

