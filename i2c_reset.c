#ifndef I2C_RESET_C
#define I2C_RESET_C

#include "i2c.h"
#include "i2c_private.h"

#include <util/twi.h>

void i2c_reset(struct i2c_t *const i) {
  TWCR = (I2C_INTERRUPT | I2C_STOP);
  i->status = 0;
}

#endif // I2C_RESET_C
