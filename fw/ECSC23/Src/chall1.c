#include <stdbool.h>
#include "chall1.h"
#include "print.h"
#include "security.h"
#include "gpio.h"
#include "eeprom.h"
#include "aes.h"

#define KEY1_OFFSET (13 * 16)

// For loop glitch
void chall1() {
  crash_on_debugger();

  uint8_t flag_encrypted[FLAG_BYTESIZE] = {
    0x5D, 0x13, 0xDC, 0x07, 0xC7, 0x55, 0xC2, 0x6F, 0xC1, 0x7D, 0xBC, 0x9E, 0x1E, 0xDD, 0x85, 0x31
  };

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
          crash_on_debugger();
          crash_on_fpb();
          HAL_GPIO_WritePin(GPIOA, LED_SUCCESS_Pin, GPIO_PIN_SET);
          crash_on_debugger();
          crash_on_fpb();
          uart_printf("Unreachable point reached, proceeding to print flag:\r\n");
          crash_on_debugger();
          crash_on_fpb();

          uint8_t key[FLAG_BYTESIZE];
          // Bootrom ("System Memory" in reference manual) contains 0x2079D15A LE at offset 0x47E
          if (!read_decrypt_key(key, EEPROM2_ADDR, KEY1_OFFSET + 0x2079D15A, 0x47E)) {
            HAL_GPIO_WritePin(GPIOA, LED_TAMPER_Pin, GPIO_PIN_SET);
            uart_printf("Failed to read data from EEPROM, stopping challenge..\r\n");
            return;
          }
          crash_on_debugger();
          crash_on_fpb();
          HAL_GPIO_WritePin(GPIOA, LED_SUCCESS_Pin, GPIO_PIN_SET);
          crash_on_debugger();
          crash_on_fpb();
          noob_decrypt(flag_encrypted, key);
          crash_on_debugger();
          crash_on_fpb();
          print_flag(flag_encrypted);
          return;
        }
      }
    }
    uart_printf("%u %u %u\r\n", i, j, cnt);
  }
}
