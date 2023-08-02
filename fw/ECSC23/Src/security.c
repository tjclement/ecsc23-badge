#include "stm32f1xx_hal.h"
#include "stm32f1xx_hal_flash_ex.h"
#include "security.h"
#include "print.h"
#include "gpio.h"

void protect_flash_readout(void) {
#ifndef DEBUG
  FLASH_OBProgramInitTypeDef opts;
  HAL_FLASHEx_OBGetConfig(&opts);

  if (opts.RDPLevel != OB_RDP_LEVEL_1) {
    uart_printf("Enabling flash readout protection\r\n");
    HAL_Delay(5000);
    if (HAL_FLASH_OB_Unlock() != HAL_OK) { uart_printf("Failed to unlock flash\r\n"); }
    opts.RDPLevel = OB_RDP_LEVEL_1;
    if (HAL_FLASHEx_OBProgram(&opts) != HAL_OK) { uart_printf("Failed to write flash options\r\n"); }
    HAL_FLASH_OB_Lock();
    HAL_FLASH_OB_Launch();
  }
#endif
}

void disable_swd(void) {
#ifndef DEBUG
  __HAL_AFIO_REMAP_SWJ_DISABLE();
#endif
}

void crash_on_debugger(void) {
#ifndef DEBUG
  if (STM_IS_DEBUGGER_ATTACHED) {
    HAL_GPIO_WritePin(GPIOA, LED_TAMPER_Pin, GPIO_PIN_SET);
    uart_printf("Busted: STM debugger detected!\r\n");
    HAL_Delay(500);
    NVIC_SystemReset();
  }
  if (CORTEX_IS_DEBUGGER_ATTACHED) {
    HAL_GPIO_WritePin(GPIOA, LED_TAMPER_Pin, GPIO_PIN_SET);
    uart_printf("Busted: Cortex debugger detected!\r\n");
    HAL_Delay(500);
    NVIC_SystemReset();
  }
#endif
}