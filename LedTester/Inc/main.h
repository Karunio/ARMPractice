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
#include "stm32f4xx_hal.h"

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
#define FND_5_Pin GPIO_PIN_13
#define FND_5_GPIO_Port GPIOC
#define FND_6_Pin GPIO_PIN_14
#define FND_6_GPIO_Port GPIOC
#define FND_7_Pin GPIO_PIN_15
#define FND_7_GPIO_Port GPIOC
#define LED_0_Pin GPIO_PIN_0
#define LED_0_GPIO_Port GPIOC
#define LED_1_Pin GPIO_PIN_1
#define LED_1_GPIO_Port GPIOC
#define LED_2_Pin GPIO_PIN_2
#define LED_2_GPIO_Port GPIOC
#define LED_3_Pin GPIO_PIN_3
#define LED_3_GPIO_Port GPIOC
#define SW_0_Pin GPIO_PIN_12
#define SW_0_GPIO_Port GPIOB
#define SW_1_Pin GPIO_PIN_13
#define SW_1_GPIO_Port GPIOB
#define SW_2_Pin GPIO_PIN_14
#define SW_2_GPIO_Port GPIOB
#define SW_3_Pin GPIO_PIN_15
#define SW_3_GPIO_Port GPIOB
#define FND_0_Pin GPIO_PIN_8
#define FND_0_GPIO_Port GPIOC
#define FND_1_Pin GPIO_PIN_9
#define FND_1_GPIO_Port GPIOC
#define FND_2_Pin GPIO_PIN_10
#define FND_2_GPIO_Port GPIOC
#define FND_3_Pin GPIO_PIN_11
#define FND_3_GPIO_Port GPIOC
#define FND_4_Pin GPIO_PIN_12
#define FND_4_GPIO_Port GPIOC
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
