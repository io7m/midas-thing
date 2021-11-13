#ifndef I2C_START_C
#define I2C_START_C

#include "i2c.h"
#include "i2c_private.h"

#include <avr/io.h>
#include <stdint.h>
#include <util/twi.h>

uint8_t i2c_start(struct i2c_t *const i, uint8_t address) {
  TWDR = 0;
  TWCR = (I2C_INTERRUPT | I2C_START | I2C_ENABLE);

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

  if (i->status != TW_START && i->status != TW_REP_START) {
    return 0;
  }

  TWDR = address << 1;
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

  if (i->status != TW_MT_SLA_ACK) {
    return 0;
  }

  return 1;
}

#endif // I2C_START_C
