#include <stdbool.h>
#include "chall2.h"
#include "print.h"

// JTAG disable attack
void chall2() {
  volatile bool check = false;
  uint8_t flag_encrypted[FLAG_BYTESIZE] = {
    0x60, 0x2C, 0x2B, 0x3D, 0x2E, 0x28, 0xC2, 0x0B, 0xB9, 0xEB, 0xA2, 0xF1, 0xAA, 0xFD, 0xFA, 0xC4
  };

  // TODO: replace with SRAM dump chall

  if (check) {
    uart_printf("Gotcha\r\n");
  } else {
    uart_printf("Bummer\r\n");
  }
}
