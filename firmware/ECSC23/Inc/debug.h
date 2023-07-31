#ifndef ECSC23_DEBUG_H
#define ECSC23_DEBUG_H

#include "stm32f103x6.h"

#define STM_IS_DEBUGGER_ATTACHED (DBGMCU->CR & DBGMCU_CR_TRACE_IOEN)
#define CORTEX_IS_DEBUGGER_ATTACHED (CoreDebug->DHCSR & CoreDebug_DHCSR_C_DEBUGEN_Msk)

#endif //ECSC23_DEBUG_H
