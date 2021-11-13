#ifndef I2C_STOP_C
#define I2C_STOP_C

#include "i2c.h"
#include "i2c_private.h"

#include <util/twi.h>

void i2c_stop(struct i2c_t *const i) {
  TWCR = (I2C_INTERRUPT | I2C_STOP | I2C_ENABLE);
  i->status = 0;
}

#endif // I2C_STOP_C
