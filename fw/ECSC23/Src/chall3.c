#include "chall3.h"
#include "i2c.h"
#include "print.h"
#include "eeprom.h"
#include "crc32.h"
#include "aes.h"
#include "security.h"

#define KEY3_OFFSET (4 * 16)
#define DATA_OFFSET (137)
#define DATA_LEN (4)
#define CRC_STATIC (0xD1DFD7EA)

uint8_t restore_data[DATA_LEN+4] = {
  0xD0, 0x0D, 0x2B, 0xAD, // data
  0xAA, 0xAA, 0xAA, 0xAA, // CRC32
};

// i2c eeprom MITM attack
void chall3(void) {
  uint8_t buf[DATA_LEN+4];
  uint8_t flag_encrypted[FLAG_BYTESIZE] = {
    0x4B, 0xD4, 0x77, 0xC6, 0x3C, 0x41, 0x61, 0xA4, 0xE3, 0x96, 0xDB, 0x1D, 0x08, 0x34, 0x99, 0xD7
  };
  uart_printf("Checking EEPROM integrity\r\n");

  if (eeprom_read(buf, EEPROM1_ADDR, DATA_OFFSET, DATA_LEN+4) != HAL_OK) {
    HAL_GPIO_WritePin(GPIOA, LED_TAMPER_Pin, GPIO_PIN_SET);
    uart_printf("Failed to read EEPROM, stopping challenge..\r\n");
    return;
  }

  uint32_t crc = crc32buf((char*)buf, DATA_LEN);
  uint32_t* crc_saved = (uint32_t*) &buf[DATA_LEN];

  if (crc != *crc_saved || crc != CRC_STATIC) {
    HAL_GPIO_WritePin(GPIOA, LED_TAMPER_Pin, GPIO_PIN_SET);
    uart_printf("EEPROM has been tampered with, restoring contents..\r\n");
    if (eeprom_restore() == HAL_OK) {
      uart_printf("Contents restored, stopping challenge.\r\n");
    } else {
      uart_printf("Error restoring contents, stopping challeng.\r\n");
    }
    return;
  }

  uart_printf("Checking access protection\r\n");

  if (eeprom_read(buf, EEPROM1_ADDR, DATA_OFFSET, DATA_LEN) != HAL_OK) {
    HAL_GPIO_WritePin(GPIOA, LED_TAMPER_Pin, GPIO_PIN_SET);
    uart_printf("Failed to read EEPROM, stopping challenge..\r\n");
    return;
  }

  if (buf[1] != 0x00) {
    HAL_GPIO_WritePin(GPIOA, LED_TAMPER_Pin, GPIO_PIN_SET);
    uart_printf("Protection bits set (0x%02X), refusing to continue. Stopping challenge..\r\n", buf[1]);
    return;
  }

  uart_printf("Protection bits are clear, proceeding to print flag:\r\n");

  uint8_t key[FLAG_BYTESIZE];
  // Bootrom ("System Memory" in reference manual) contains 0x4149F760 LE at offset 0x5B
  if (!read_decrypt_key(key, EEPROM2_ADDR, KEY3_OFFSET + 0x4149F760, 0x5B)) {
    HAL_GPIO_WritePin(GPIOA, LED_TAMPER_Pin, GPIO_PIN_SET);
    uart_printf("Failed to read data from EEPROM, stopping challenge..\r\n");
    return;
  }
  HAL_GPIO_WritePin(GPIOA, LED_SUCCESS_Pin, GPIO_PIN_SET);
  noob_decrypt(flag_encrypted, key);
  print_flag(flag_encrypted);
}
