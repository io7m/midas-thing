#ifndef I2C_WRITE_C
#define I2C_WRITE_C

#include "i2c.h"
#include "i2c_private.h"

#include <stdint.h>
#include <util/twi.h>

#ifdef I2C_DEBUG
#include "format.h"
#include "uart.h"
static void i2c_write_dump(uint8_t data) {
  char buffer[8] = {0};
  buffer[formatU8X(buffer, data)] = 0;
  uart_puts("0x");
  uart_puts(buffer);
  uart_putchar(' ');
}
#else
#define i2c_write_dump(d)
#endif

uint8_t i2c_write(struct i2c_t *const i, uint8_t data) {
  i2c_write_dump(data);

  TWDR = data;
  TWCR = (I2C_INTERRUPT | I2C_ENABLE);

  for (;;) {
    if ((TWCR & I2C_INTERRUPT)) {
      break;
    }
  }

  i->status = TWSR & 0b11111000;
  if (i->status == 0) {
    i2c_reset(i);
    return 0;
  }

  if (i->status != TW_MT_DATA_ACK) {
    return 0;
  }

  return 1;
}

#endif // I2C_WRITE_C
