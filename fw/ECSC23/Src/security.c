#include <stdbool.h>
#include "stm32f1xx_hal.h"
#include "stm32f1xx_hal_flash_ex.h"
#include "security.h"
#include "print.h"
#include "gpio.h"
#include "eeprom.h"

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

bool read_decrypt_key(uint8_t *dst, uint8_t eeprom_addr, uint32_t base_eeprom_offset, uint32_t bootrom_subtraction_offset) {
  uint8_t *bootrom = (uint8_t*)0x1FFFF000;
  uint32_t subtraction = *((uint32_t*)&bootrom[bootrom_subtraction_offset]);
  base_eeprom_offset -= subtraction;
  if (eeprom_read(dst, eeprom_addr, base_eeprom_offset, FLAG_BYTESIZE) != HAL_OK) {
    return false;
  }

  return true;
}