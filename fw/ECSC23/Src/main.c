/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "i2c.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "security.h"
#include "print.h"
#include "chall1.h"
#include "chall2.h"
#include "chall3.h"
#include "chall4.h"
#include "eeprom.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
volatile int chosen_chall = -1;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */
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
  disable_swd();
  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */
  disable_swd();
  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_I2C1_Init();
  MX_USART1_UART_Init();
  /* USER CODE BEGIN 2 */

#ifdef DEBUG
  uart_printf("DEBUG - Build timestamp - %s@%s\r\n", __DATE__, __TIME__);

  uint32_t uid0 = HAL_GetUIDw0();
  uint32_t uid1 = HAL_GetUIDw1();
  uint32_t uid2 = HAL_GetUIDw2();

  uart_printf("DEBUG - HW UID: 0x%08X 0x%08X 0x%08X\r\n", uid0, uid1, uid2);
  uart_printf("DEBUG - FPB regs: 0x%08X 0x%08X 0x%08X 0x%08X\r\n", *(uint32_t*)0xe0002000, *(uint32_t*)0xe0002004, *(uint32_t*)0xe0002008, *(uint32_t*)0xe000200c);
#endif

  check:
  if (HAL_GPIO_ReadPin(SW_CHALL1_GPIO_Port, SW_CHALL1_Pin) && chosen_chall == -1) {
    HAL_GPIO_WritePin(GPIOA, LED_RUNNING_Pin, GPIO_PIN_SET);
    if (chosen_chall != -1) { goto check; }
    uart_printf("Starting challenge 1\r\n");
    if (chosen_chall != -1) { goto check; }
    chosen_chall = 1;
    chall1();
  } else if (HAL_GPIO_ReadPin(SW_CHALL2_GPIO_Port, SW_CHALL2_Pin) && chosen_chall == -1) {
    HAL_GPIO_WritePin(GPIOA, LED_RUNNING_Pin, GPIO_PIN_SET);
    if (chosen_chall != -1) { goto check; }
    uart_printf("Starting challenge 2\r\n");
    if (chosen_chall != -1) { goto check; }
    chosen_chall = 2;
    chall2();
  } else if (HAL_GPIO_ReadPin(SW_CHALL3_GPIO_Port, SW_CHALL3_Pin) && chosen_chall == -1) {
    HAL_GPIO_WritePin(GPIOA, LED_RUNNING_Pin, GPIO_PIN_SET);
    if (chosen_chall != -1) { goto check; }
    uart_printf("Starting challenge 3\r\n");
    if (chosen_chall != -1) { goto check; }
    chosen_chall = 3;
    chall3();
  } else if (HAL_GPIO_ReadPin(SW_CHALL4_GPIO_Port, SW_CHALL4_Pin) && chosen_chall == -1) {
    HAL_GPIO_WritePin(GPIOA, LED_RUNNING_Pin, GPIO_PIN_SET);
    if (chosen_chall != -1) { goto check; }
    uart_printf("Starting challenge 4\r\n");
    if (chosen_chall != -1) { goto check; }
    chosen_chall = 4;
    chall4();
  } else {
    uart_printf("Hold one of the 4 challenge buttons to start them\r\n");

    uint8_t first_byte;
    if (eeprom_read(&first_byte, EEPROM2_ADDR, EEPROM_LEN-1, 1) == HAL_OK && first_byte == 0xFF) {
      uart_printf("EEPROM contents are corrupted. Restoring.\r\n");
      eeprom_restore();
    }

    HAL_GPIO_WritePin(GPIOA, LED_RUNNING_Pin, GPIO_PIN_SET);
    HAL_Delay(500);
    HAL_GPIO_WritePin(GPIOA, LED_RUNNING_Pin, GPIO_PIN_RESET);
    HAL_Delay(500);
    goto check;
  }
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
    HAL_GPIO_WritePin(GPIOA, LED_RUNNING_Pin, GPIO_PIN_RESET);
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

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add their own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
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
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
