#include "chall3.h"
#include "i2c.h"
#include "print.h"

// i2c eeprom MITM attack
void chall3() {
  /*-[ I2C Bus Scanning ]-*/
  uart_printf("I2C scan:\r\n     00   01   02   03   04   05   06   07   08   09   0A   0B   0C   0D   0E   0F");
  for(int i=0; i<8; i++)
  {
    uart_printf("\r\n %d0  ", i);
    for(int j = 0; j < 16; j++) {
      int addr = (i * 16) + j;
      HAL_StatusTypeDef ret = HAL_I2C_IsDeviceReady(&hi2c1, (uint16_t) (addr << 1), 3, 5);
      if (ret != HAL_OK) /* No ACK Received At That Address */
      {
        uart_printf(".... ");
      } else {
        uart_printf("0x%02X ", addr);
      }
    }
  }
  /*--[ Scanning Done ]--*/

  uart_printf("\r\n0x50 contents:\r\n     00   01   02   03   04   05   06   07   08   09   0A   0B   0C   0D   0E   0F");
  for(int i=0; i<8; i++)
  {
    uart_printf("\r\n %d0  ", i);
    for(int j = 0; j < 16; j++) {
      int addr = (i * 16) + j;
      uint8_t buf;
      HAL_StatusTypeDef ret = HAL_I2C_Mem_Read(&hi2c1, (uint16_t) (0x50 << 1), addr, I2C_MEMADD_SIZE_8BIT, &buf, 1, 9000);
      if (ret == HAL_OK) {
        uart_printf("0x%02X ", buf);
      } else {
        uart_printf("ER ");
      }
    }
  }

  uart_printf("\r\n0x51 contents:\r\n     00   01   02   03   04   05   06   07   08   09   0A   0B   0C   0D   0E   0F");
  for(int i=0; i<8; i++)
  {
    uart_printf("\r\n %d0  ", i);
    for(int j = 0; j < 16; j++) {
      int addr = (i * 16) + j;
      uint8_t buf;
      HAL_StatusTypeDef ret = HAL_I2C_Mem_Read(&hi2c1, (uint16_t) (0x51 << 1), addr, I2C_MEMADD_SIZE_8BIT, &buf, 1, 9000);
      if (ret == HAL_OK) {
        uart_printf("0x%02X ", buf);
      } else {
        uart_printf("ER ");
      }
    }
  }
}
