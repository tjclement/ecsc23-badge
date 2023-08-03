#include <stdbool.h>
#include "chall1.h"
#include "print.h"
#include "security.h"
#include "gpio.h"

// For loop glitch
void chall1() {
  crash_on_debugger();

  volatile bool check = true;
  volatile uint32_t cnt = 0;
  int i = 0;
  int j;

  while (true) {
    cnt = 0;
    for (i = 0; i < 1000; i++) {
      for (j = 0; j < 1000; j++) {
        cnt++;
        if (!check) {
          uart_printf("U R winrar!\r\n");
          HAL_GPIO_WritePin(GPIOA, LED_SUCCESS_Pin, GPIO_PIN_SET);
          return;
        }
      }
    }
    uart_printf("%u %u %u\r\n", i, j, cnt);
  }
}
