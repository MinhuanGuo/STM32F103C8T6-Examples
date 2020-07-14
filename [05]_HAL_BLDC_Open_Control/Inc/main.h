/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define encoder_A_Pin GPIO_PIN_0
#define encoder_A_GPIO_Port GPIOA
#define encoder_B_Pin GPIO_PIN_1
#define encoder_B_GPIO_Port GPIOA
#define HALL_U_Pin GPIO_PIN_6
#define HALL_U_GPIO_Port GPIOA
#define HALL_V_Pin GPIO_PIN_7
#define HALL_V_GPIO_Port GPIOA
#define HALL_W_Pin GPIO_PIN_0
#define HALL_W_GPIO_Port GPIOB
#define LED0_Pin GPIO_PIN_12
#define LED0_GPIO_Port GPIOB
#define PU_L_Pin GPIO_PIN_13
#define PU_L_GPIO_Port GPIOB
#define PV_L_Pin GPIO_PIN_14
#define PV_L_GPIO_Port GPIOB
#define PW_L_Pin GPIO_PIN_15
#define PW_L_GPIO_Port GPIOB
#define PU_H_Pin GPIO_PIN_8
#define PU_H_GPIO_Port GPIOA
#define PV_H_Pin GPIO_PIN_9
#define PV_H_GPIO_Port GPIOA
#define PW_H_Pin GPIO_PIN_10
#define PW_H_GPIO_Port GPIOA
#define Encoder_Key_Pin GPIO_PIN_15
#define Encoder_Key_GPIO_Port GPIOA
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
