#ifndef UART_H
#define UART_H

void uart_init();
int uart_putchar(char);
int uart_getchar();

void uart_puts(const char *text);
void uart_puts_P(const char *text);

#endif // UART_H
