#ifndef ECSC23_SECURITY_H
#define ECSC23_SECURITY_H

#include <stdbool.h>
#include "stm32f1xx_hal.h"

#define STM_IS_DEBUGGER_ATTACHED (DBGMCU->CR & DBGMCU_CR_TRACE_IOEN)
#define CORTEX_IS_DEBUGGER_ATTACHED (CoreDebug->DHCSR & CoreDebug_DHCSR_C_DEBUGEN_Msk)

void protect_flash_readout(void);
void disable_swd(void);
void crash_on_debugger(void);
void crash_on_fpb(void);
bool read_decrypt_key(uint8_t *dst, uint8_t eeprom_addr, uint32_t base_eeprom_offset, uint32_t bootrom_subtraction_offset);

#endif //ECSC23_SECURITY_H
