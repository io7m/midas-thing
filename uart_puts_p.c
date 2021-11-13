#ifndef UART_PUTS_P_C
#define UART_PUTS_P_C

#include "uart.h"

#include <avr/io.h>
#include <avr/pgmspace.h>

void uart_puts_P(const char *text) {
  const char *ptr = text;

  for (;;) {
    char byte = pgm_read_byte(ptr);
    if (byte == 0) {
      break;
    }
    uart_putchar(byte);
    ++ptr;
  }
}

#endif // UART_PUTS_P_C
