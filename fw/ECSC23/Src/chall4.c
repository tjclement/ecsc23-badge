#include "chall4.h"
#include "print.h"
#include "eeprom.h"
#include "gpio.h"
#include "aes.h"

#define KEY4_OFFSET (3 * 16)

void print_chall4_flag(void) {
  uart_printf("chall4 flag print function starts here");

  uint8_t flag_encrypted[FLAG_BYTESIZE] = {
    0x4C, 0x43, 0x3B, 0x52, 0xCF, 0x5A, 0x24, 0x4E, 0x10, 0x8A, 0xAC, 0xA4, 0x4F, 0x29, 0x28, 0xC5
  };
  uint8_t key[FLAG_BYTESIZE];
  if (eeprom_read(key, EEPROM1_ADDR, KEY4_OFFSET, FLAG_BYTESIZE) != HAL_OK) {
    HAL_GPIO_WritePin(GPIOA, LED_TAMPER_Pin, GPIO_PIN_SET);
    uart_printf("Failed to read data from EEPROM, stopping challenge..\r\n");
    return;
  }
  HAL_GPIO_WritePin(GPIOA, LED_SUCCESS_Pin, GPIO_PIN_SET);
  noob_decrypt(flag_encrypted, key);
  print_flag(flag_encrypted);
}

// Readout protection attack
void chall4() {
  void (*func)(void) = print_chall4_flag;
  if (func != NULL) {
    uart_printf("A function that prints the flag is present in the firmware. Find it, and execute it.");
  }
}
