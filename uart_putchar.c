#ifndef UART_PUTCHAR_C
#define UART_PUTCHAR_C

#include "uart.h"

#include <avr/io.h>
#include <util/setbaud.h>

int uart_putchar(char c) {
  if (c == '\n') {
    uart_putchar('\r');
  }
  loop_until_bit_is_set(UCSR0A, UDRE0);
  UDR0 = c;
  return c;
}

#endif // UART_PUTCHAR_C
