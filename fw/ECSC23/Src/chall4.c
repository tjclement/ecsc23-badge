#include "chall4.h"
#include "print.h"
#include "eeprom.h"
#include "gpio.h"
#include "aes.h"
#include "security.h"
#include "usart.h"
#include "i2c.h"

#define KEY4_OFFSET (3 * 16)

_Noreturn __attribute__ ((used))
void print_chall4_flag(void) {
  uart_printf("chall4 flag print function starts here");

  // Re-init system because we're likely booted through SRAM
  HAL_Init();
  SystemClock_Config();
  MX_GPIO_Init();
  MX_I2C1_Init();
  MX_USART1_UART_Init();

  uint8_t flag_encrypted[FLAG_BYTESIZE] = {
    0x4C, 0x43, 0x3B, 0x52, 0xCF, 0x5A, 0x24, 0x4E, 0x10, 0x8A, 0xAC, 0xA4, 0x4F, 0x29, 0x28, 0xC5
  };
  uint8_t key[FLAG_BYTESIZE];
  crash_on_debugger();
  // Bootrom ("System Memory" in reference manual) contains 0xE0E0064D LE at offset 0x76F
  if (!read_decrypt_key(key, EEPROM1_ADDR, KEY4_OFFSET + 0xE0E0064D, 0x76F)) {
    HAL_GPIO_WritePin(GPIOA, LED_TAMPER_Pin, GPIO_PIN_SET);
    uart_printf("Failed to read data from EEPROM, stopping challenge..\r\n");
    return;
  }
  crash_on_debugger();
  HAL_GPIO_WritePin(GPIOA, LED_SUCCESS_Pin, GPIO_PIN_SET);
  crash_on_debugger();
  noob_decrypt(flag_encrypted, key);
  while (true) {
    crash_on_debugger();
    print_flag(flag_encrypted);
  }
}

// Readout protection attack
__attribute__ ((optimize("-O0")))
void chall4() {
  void (*func)(void) = print_chall4_flag;
  if (func != NULL) {
    uart_printf("A function that prints the flag is present in the firmware. Find it, and execute it.");
  }
}
