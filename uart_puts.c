#ifndef UART_PUTS_C
#define UART_PUTS_C

#include "uart.h"

#include <avr/io.h>

void uart_puts(const char *text) {
  const char *ptr = text;

  for (;;) {
    if (*ptr == 0) {
      break;
    }
    uart_putchar(*ptr);
    ++ptr;
  }
}

#endif // UART_PUTS_C
