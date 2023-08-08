#ifndef ECSC23_PRINT_H
#define ECSC23_PRINT_H

#include <stdint.h>

#define FLAG_BYTESIZE (16)

int uart_printf(const char *format, ...);
void print_flag(uint8_t *contents);

#endif //ECSC23_PRINT_H
