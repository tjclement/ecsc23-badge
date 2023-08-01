#include <stdbool.h>
#include "chall1.h"
#include "print.h"
#include "debug.h"

// For loop glitch
void chall1() {
  if (STM_IS_DEBUGGER_ATTACHED) {
    uart_printf("Busted: STM\r\n");
    NVIC_SystemReset();
  }
  if (CORTEX_IS_DEBUGGER_ATTACHED) {
    uart_printf("Busted: Cortex\r\n");
    NVIC_SystemReset();
  }

  volatile bool check = false;
  for (volatile int i = 0; i < 100000; i++) {
    if (check) {
      uart_printf("Gotcha\r\n");
      return;
    }
  }

  uart_printf("Bummer\r\n");
}
