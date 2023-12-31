#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include "chall2.h"
#include "print.h"
#include "security.h"
#include "eeprom.h"
#include "aes.h"
#include "crc32.h"
#include "main.h"



#define KEY1_OFFSET (12 * 16)

char flag_contents[64];

// JTAG disable attack
void chall1() {
  uint8_t flag_encrypted[FLAG_BYTESIZE] = {
    0x60, 0x2C, 0x2B, 0x3D, 0x2E, 0x28, 0xC2, 0x0B, 0xB9, 0xEB, 0xA2, 0xF1, 0xAA, 0xFD, 0xFA, 0xC4
  };

  if(chosen_chall != 1) { return; }

  char hex[3] = {0};
  uint8_t key[FLAG_BYTESIZE];
  crash_on_debugger();
  crash_on_fpb();
  // Bootrom ("System Memory" in reference manual) contains 0x1020024A LE at offset 0x239
  if (!read_decrypt_key(key, EEPROM1_ADDR, KEY1_OFFSET + 0x1020024A, 0x239)) {
    HAL_GPIO_WritePin(GPIOA, LED_TAMPER_Pin, GPIO_PIN_SET);
    uart_printf("Failed to read data from EEPROM, stopping challenge..\r\n");
    return;
  }
  crash_on_debugger();
  crash_on_fpb();
  noob_decrypt(flag_encrypted, key);

  if(chosen_chall != 1) { return; }

  crash_on_debugger();
  crash_on_fpb();
  memset(flag_contents, 0x00, 64);
  strcat(flag_contents, "ctf{");
  for (int i = 0; i < FLAG_BYTESIZE; i++) {
    snprintf(hex, 3, "%02X", flag_encrypted[i]);
    strcat(flag_contents, hex);
  }

  if(chosen_chall != 1) { return; }

  crash_on_debugger();
  crash_on_fpb();
  uint32_t uid0 = HAL_GetUIDw0();
  uint32_t uid1 = HAL_GetUIDw1();
  uint32_t uid2 = HAL_GetUIDw2();
  uint32_t crc = crc32buf((char*)flag_encrypted, FLAG_BYTESIZE);
  crc = updateCRC32(((uint8_t*)&uid0)[0], crc);
  crc = updateCRC32(((uint8_t*)&uid0)[1], crc);
  crc = updateCRC32(((uint8_t*)&uid0)[2], crc);
  crc = updateCRC32(((uint8_t*)&uid0)[3], crc);
  crc = updateCRC32(((uint8_t*)&uid1)[0], crc);
  crc = updateCRC32(((uint8_t*)&uid1)[1], crc);
  crc = updateCRC32(((uint8_t*)&uid1)[2], crc);
  crc = updateCRC32(((uint8_t*)&uid1)[3], crc);
  crc = updateCRC32(((uint8_t*)&uid2)[0], crc);
  crc = updateCRC32(((uint8_t*)&uid2)[1], crc);
  crc = updateCRC32(((uint8_t*)&uid2)[2], crc);
  crc = updateCRC32(((uint8_t*)&uid2)[3], crc);
  snprintf(hex, 3, "%02X", ((uint8_t*)&crc)[3]);
  strcat(flag_contents, hex);
  strcat(flag_contents, "}");

  if(chosen_chall != 1) { return; }

  uart_printf("Flag loaded to memory in plaintext. It will not be printed. SWD and JTAG are disabled, so the flag is unreachable.\r\n");
}
