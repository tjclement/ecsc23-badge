#ifndef ECSC23_SECURITY_H
#define ECSC23_SECURITY_H

#include "stm32f1xx_hal.h"

#define STM_IS_DEBUGGER_ATTACHED (DBGMCU->CR & DBGMCU_CR_TRACE_IOEN)
#define CORTEX_IS_DEBUGGER_ATTACHED (CoreDebug->DHCSR & CoreDebug_DHCSR_C_DEBUGEN_Msk)

inline void protect_flash_readout(void);
inline void disable_swd(void);
inline void crash_on_debugger(void);

#endif //ECSC23_SECURITY_H
