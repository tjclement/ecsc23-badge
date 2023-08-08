#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include "usart.h"
#include "crc32.h"
#include "print.h"

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

void print_flag(uint8_t *contents) {

  /* Plaintext flag contents:
   * chall1 - b'oH\xc0UgNu\x1bJDJ3(\xc0\x0c\x93'
   * chall2 - b'\x119\xbeJ\x97\xd2\x17.n9\xb7\x1e\xfa\xd4\xb3\x06'
   * chall3 - b'X\x05\x90\x1e]\xa7lhe\x88E\x9cG\x9d\xac\x99'
   * chall4 - b'\xd0\xbc\xce\x94\xc7\x14x\xad\xefyD\x8fF\x0f\x1f\xf6'
   *
   * Encrypted flag contents:
   * chall1 - b']\x13\xdc\x07\xc7U\xc2o\xc1}\xbc\x9e\x1e\xdd\x851'
   * chall2 - b'`,+=.(\xc2\x0b\xb9\xeb\xa2\xf1\xaa\xfd\xfa\xc4'
   * chall3 - b'K\xd4w\xc6<Aa\xa4\xe3\x96\xdb\x1d\x084\x99\xd7'
   * chall4 - b'LC;R\xcfZ$N\x10\x8a\xac\xa4O)(\xc5'
   * */

  uint32_t uid = HAL_GetUIDw2();
  uint32_t crc = crc32buf((char*)contents, FLAG_BYTESIZE);
  crc = updateCRC32(((uint8_t*)&uid)[0], crc);
  crc = updateCRC32(((uint8_t*)&uid)[1], crc);
  crc = updateCRC32(((uint8_t*)&uid)[2], crc);
  crc = updateCRC32(((uint8_t*)&uid)[3], crc);

  uart_printf("ctf{") ;
  for (int i = 0; i < FLAG_BYTESIZE; i++) {
    uart_printf("%02X", contents[i]);
  }
  uart_printf("%02X}", ((uint8_t*)&crc)[3]);
}