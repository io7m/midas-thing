#ifndef UART_GETCHAR_C
#define UART_GETCHAR_C

#include "uart.h"

#include <avr/io.h>

int uart_getchar() {
  loop_until_bit_is_set(UCSR0A, RXC0);
  return UDR0;
}

#endif // UART_GETCHAR_C
