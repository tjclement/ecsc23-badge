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
#define TP14_Pin GPIO_PIN_4
#define TP14_GPIO_Port GPIOA
#define TP15_Pin GPIO_PIN_5
#define TP15_GPIO_Port GPIOA
#define TP16_Pin GPIO_PIN_6
#define TP16_GPIO_Port GPIOA
#define TP17_Pin GPIO_PIN_7
#define TP17_GPIO_Port GPIOA
#define SW3_Pin GPIO_PIN_0
#define SW3_GPIO_Port GPIOB
#define SW4_Pin GPIO_PIN_1
#define SW4_GPIO_Port GPIOB
#define SW5_Pin GPIO_PIN_2
#define SW5_GPIO_Port GPIOB
#define CONN_Pin GPIO_PIN_10
#define CONN_GPIO_Port GPIOB
#define CONNB11_Pin GPIO_PIN_11
#define CONNB11_GPIO_Port GPIOB
#define CONNB12_Pin GPIO_PIN_12
#define CONNB12_GPIO_Port GPIOB
#define CONNB13_Pin GPIO_PIN_13
#define CONNB13_GPIO_Port GPIOB
#define CONNB14_Pin GPIO_PIN_14
#define CONNB14_GPIO_Port GPIOB
#define CONNB15_Pin GPIO_PIN_15
#define CONNB15_GPIO_Port GPIOB
#define EEPROM1_WC_Pin GPIO_PIN_8
#define EEPROM1_WC_GPIO_Port GPIOA
#define EEPROM2_WC_CHECK_Pin GPIO_PIN_11
#define EEPROM2_WC_CHECK_GPIO_Port GPIOA
#define EEPROM2_WC_Pin GPIO_PIN_12
#define EEPROM2_WC_GPIO_Port GPIOA
#define EEPROM1_WC_CHECK_Pin GPIO_PIN_15
#define EEPROM1_WC_CHECK_GPIO_Port GPIOA
#define SW6_Pin GPIO_PIN_3
#define SW6_GPIO_Port GPIOB
#define TP9_Pin GPIO_PIN_4
#define TP9_GPIO_Port GPIOB
#define TP10_Pin GPIO_PIN_5
#define TP10_GPIO_Port GPIOB
#define TP11_Pin GPIO_PIN_8
#define TP11_GPIO_Port GPIOB
#define TP12_Pin GPIO_PIN_9
#define TP12_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
