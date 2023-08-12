#ifndef ECSC23_EEPROM_H
#define ECSC23_EEPROM_H

#include "stm32f1xx_hal.h"

#define EEPROM1_ADDR (0x51)
#define EEPROM2_ADDR (0x50)
#define EEPROM_LEN (256)

void i2c_scan(void);
void eeprom_dump(uint8_t i2c_addr);
HAL_StatusTypeDef eeprom_read(uint8_t *dest, uint8_t i2c_addr, uint16_t reg_addr, uint16_t nbytes);
HAL_StatusTypeDef eeprom_write(uint8_t *src, uint8_t i2c_addr, uint16_t reg_addr, uint16_t nbytes);
HAL_StatusTypeDef eeprom_restore(void);
void eeprom_test_write(uint8_t i2c_addr);

#endif //ECSC23_EEPROM_H
