#include "stm32f1xx_hal.h"
#include "eeprom.h"
#include "print.h"
#include "i2c.h"

#define I2C_TIMEOUT (9000) // in ms

void i2c_scan(void) {
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
}

void eeprom_dump(uint8_t i2c_addr) {
  uart_printf("\r\n0x%02X contents:\r\n     00   01   02   03   04   05   06   07   08   09   0A   0B   0C   0D   0E   0F", i2c_addr);
  for(int i=0; i<8; i++)
  {
    uart_printf("\r\n %d0  ", i);
    for(int j = 0; j < 16; j++) {
      int addr = (i * 16) + j;
      uint8_t buf;
      HAL_StatusTypeDef ret = HAL_I2C_Mem_Read(&hi2c1, (uint16_t) (i2c_addr << 1), addr, I2C_MEMADD_SIZE_8BIT, &buf, 1, I2C_TIMEOUT);
      if (ret == HAL_OK) {
        uart_printf("0x%02X ", buf);
      } else {
        uart_printf("ERR  ");
      }
    }
  }
}

HAL_StatusTypeDef eeprom_read(uint8_t *dest, uint8_t i2c_addr, uint16_t reg_addr, uint16_t nbytes) {
  return HAL_I2C_Mem_Read(&hi2c1, (uint16_t) (i2c_addr << 1), reg_addr, I2C_MEMADD_SIZE_8BIT, dest, nbytes, I2C_TIMEOUT);
}

HAL_StatusTypeDef eeprom_write(uint8_t *src, uint8_t i2c_addr, uint16_t reg_addr, uint16_t nbytes) {
  return HAL_I2C_Mem_Write(&hi2c1, (uint16_t) (i2c_addr << 1), reg_addr, I2C_MEMADD_SIZE_8BIT, src, nbytes, I2C_TIMEOUT);
}