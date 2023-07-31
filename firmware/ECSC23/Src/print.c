#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include "usart.h"

#define MAX_PRINT_CHARS (1024)

char printbuf[MAX_PRINT_CHARS];

int uart_printf(const char *format, ...)
{
    va_list args;
    va_start(args, format);
    int ret = vsnprintf(printbuf, MAX_PRINT_CHARS, format, args);
    va_end(args);

    HAL_UART_Transmit(&huart1, (uint8_t *)printbuf, strnlen(printbuf, MAX_PRINT_CHARS), 0xFFFF);
    return ret;
}