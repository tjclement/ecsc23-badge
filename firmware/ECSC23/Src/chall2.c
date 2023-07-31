#include <stdbool.h>
#include "chall2.h"
#include "print.h"

// JTAG disable attack
void chall2() {
  volatile bool check = false;
  if (check) {
    uart_printf("Gotcha\r\n");
  } else {
    uart_printf("Bummer\r\n");
  }
}
