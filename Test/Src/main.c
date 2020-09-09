/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
/*  ARM exam 평가
  Created : 2020-06-25
  Author : 백규현
*/
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "adc.h"
#include "dma.h"
#include "i2c.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "lcd.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */
#define SHT2x_ADDR              (0x40 << 1)
#define SHT2x_HOLD_MASTER_T     0xE3
#define SHT2x_HOLD_MASTER_RH    0xE5
#define SHT2x_NOHOLD_MASTER_T   0xF3
#define SHT2x_NOHOLD_MASTER_RH  0xF5
#define SHT2x_WRITE_USER_REG    0xE6
#define SHT2x_READ_USER_REG     0xE7
#define SHT2x_SOFT_RESET        0xFE
#define STR_MAX                 16
/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
volatile bool enable = false;
uint32_t melodies[] = {523, 587, 659, 698, 783, 880, 987, 1046};
uint8_t rxData;
uint8_t menu[] = "++++ Menu ++++\r\n"\
                 "L : LED\r\n"\
                 "C : CDS (DMA)\r\n"\
                 "0 ~ 7 : PIANO\r\n"\
                 "T : Temp Humidity\r\n"\
                 "Push Button : Stop\r\n";
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */
void Init();
void PrintTempHumi();
void PrintTemp();
void PrintHumi();
void PrintCds();
void PlayPiano();
void LedRun();
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */
  
  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_ADC1_Init();
  MX_I2C1_Init();
  MX_TIM2_Init();
  MX_USART1_UART_Init();
  MX_TIM5_Init();
  /* USER CODE BEGIN 2 */
  lcdInit();
  Init();
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    HAL_UART_Receive(&huart1, &rxData, sizeof(rxData), 10);
    if(rxData == 'L' || rxData == 'l')
    {
      LedRun();
    }
    else if(rxData == 'c' || rxData == 'C')
    {
      PrintCds();
    }
    else if('0' <= rxData && rxData <= '7')
    {
      PlayPiano();
    }
    else if(rxData == 'T' || rxData == 't')
    {
      PrintTempHumi();
    }
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage 
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 168;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
void Init()
{
  enable = false;
  rxData = '\0';
  HAL_UART_Transmit_DMA(&huart1, menu, sizeof(menu));
  TIM2->CCR1 = 0;
  TIM5->CCR4 = 0;
}

void PrintTempHumi()
{
  enable = true;
  
  while(enable == true)
  {
    PrintTemp();
    PrintHumi();
  }
  
  lcdClear();
}

void PrintTemp()
{ 
  char lcdStr[STR_MAX];
  uint8_t i2cData[2];
  uint16_t convData;
  uint8_t i2cMode;
  float temp;
  
  i2cMode = SHT2x_NOHOLD_MASTER_T;
  HAL_I2C_Master_Transmit(&hi2c1, SHT2x_ADDR, &i2cMode, 1, HAL_TIMEOUT);
  HAL_Delay(100);
  HAL_I2C_Master_Receive(&hi2c1, SHT2x_ADDR, i2cData, 2, HAL_TIMEOUT);
  
  convData = i2cData[0] << 8 | i2cData[1];
  temp = -46.85 + 172.72 * (convData / 65536.0);
  
  lcdGotoXY(0, 0);
  sprintf(lcdStr, "TEMP : %4.1f\'C", temp);
  lcdPrint(lcdStr);
}

void PrintHumi()
{
  char lcdStr[STR_MAX];
  uint8_t i2cData[2];
  uint16_t convData;
  uint8_t i2cMode;
  float humi;
  
  i2cMode = SHT2x_NOHOLD_MASTER_RH;
  HAL_I2C_Master_Transmit(&hi2c1, SHT2x_ADDR, &i2cMode, 1, HAL_TIMEOUT);
  HAL_Delay(100);
  HAL_I2C_Master_Receive(&hi2c1, SHT2x_ADDR, i2cData, 2, HAL_TIMEOUT);
  
  convData = i2cData[0] << 8 | i2cData[1];
  humi = -6 + 125 * (convData / 65536.0);
  
  lcdGotoXY(0, 1);
  sprintf(lcdStr, "HUMI : %4.1f%%", humi);
  lcdPrint(lcdStr);
  
}

void PrintCds()
{
  uint16_t cdsValue;
  char lcdStr[STR_MAX];
  
  enable = true;
  HAL_ADC_Start_DMA(&hadc1, (uint32_t*)&cdsValue, 1);
  while(enable == true)
  {
    lcdGotoXY(0, 0);
    sprintf(lcdStr, "CDS : %4d", cdsValue);
    lcdPrint(lcdStr);
    HAL_Delay(100);
  }
  lcdClear();
  HAL_ADC_Stop_DMA(&hadc1);
}

void PlayPiano()
{
  uint32_t freq, duty;
  uint8_t oldData = '\0';
  enable = true;
  HAL_TIM_PWM_Start(&htim5, TIM_CHANNEL_4);
  while(enable == true)
  {
    HAL_UART_Receive(&huart1, &rxData, sizeof(rxData), 10);
    if(oldData == rxData)
    {
      continue;
    }
    
    oldData = rxData;
    
    if('0' <= rxData && rxData <= '7')
    {
      TIM5->EGR &= ~(0x01);
      
      freq = 84000000 / melodies[rxData - '0'] - 1;
      duty = freq / 2;
      
      TIM5->ARR = freq;
      TIM5->CCR4 = duty;
      
      TIM5->EGR |= (0x01);
    }
    else
    {
      TIM5->CCR4 = 0;
    }
  }
  TIM5->CCR4 = 0;
  HAL_TIM_PWM_Stop(&htim5, TIM_CHANNEL_4);
}

void LedRun()
{ 
  uint8_t bright = 0;
  uint8_t turn = 0;
  
  enable = true;
  HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1);
  while(enable == true)
  {
    if(turn == 0)
    {
      bright++;
      if(bright > 100 - 1)
      {
        turn = 1;
      }
    }
    else
    {
       bright--;
       if(bright <= 0)
       {
         turn = 0;
       }
    }
    
    TIM2->CCR1 = bright;
    HAL_Delay(100);
  }
  TIM2->CCR1 = 0;
  HAL_TIM_PWM_Stop(&htim2, TIM_CHANNEL_1);
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
  if(GPIO_Pin == SW_INT_Pin)
  {
    Init();
  }
}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */

  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{ 
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
