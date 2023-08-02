#include <stdbool.h>
#include "chall1.h"
#include "print.h"
#include "security.h"
#include "gpio.h"

// For loop glitch
void chall1() {
  crash_on_debugger();

  volatile bool check = true;
  for (volatile int i = 0; i < 1000000000; i++) {
    if (!check) {
      uart_printf("Gotcha\r\n");
      HAL_GPIO_WritePin(GPIOA, LED_SUCCESS_Pin, GPIO_PIN_SET);
      return;
    }
  }

  uart_printf("Bummer\r\n");
}
