/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
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
#define LED_POWER_Pin GPIO_PIN_0
#define LED_POWER_GPIO_Port GPIOA
#define LED_RUNNING_Pin GPIO_PIN_1
#define LED_RUNNING_GPIO_Port GPIOA
#define LED_SUCCESS_Pin GPIO_PIN_2
#define LED_SUCCESS_GPIO_Port GPIOA
#define LED_TAMPER_Pin GPIO_PIN_3
#define LED_TAMPER_GPIO_Port GPIOA
#define EEPROM2_WC_CHECK_Pin GPIO_PIN_4
#define EEPROM2_WC_CHECK_GPIO_Port GPIOA
#define EEPROM2_WC_Pin GPIO_PIN_5
#define EEPROM2_WC_GPIO_Port GPIOA
#define EEPROM1_WC_CHECK_Pin GPIO_PIN_6
#define EEPROM1_WC_CHECK_GPIO_Port GPIOA
#define EEPROM1_WC_Pin GPIO_PIN_7
#define EEPROM1_WC_GPIO_Port GPIOA
#define SW_CHALL1_Pin GPIO_PIN_2
#define SW_CHALL1_GPIO_Port GPIOB
#define SW_CHALL2_Pin GPIO_PIN_5
#define SW_CHALL2_GPIO_Port GPIOB
#define SW_CHALL3_Pin GPIO_PIN_8
#define SW_CHALL3_GPIO_Port GPIOB
#define SW_CHALL4_Pin GPIO_PIN_9
#define SW_CHALL4_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */
extern volatile int chosen_chall;
void SystemClock_Config(void);
/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
