#ifndef I2C_INIT_C
#define I2C_INIT_C

#include "i2c.h"
#include "i2c_private.h"

#include <util/twi.h>

void i2c_init(struct i2c_t *const i) {
  i->status = 0;

  /*
   * See page 242 of the ATMega2560 datasheet. The SCL frequency is
   * given by:
   *
   * SCL = F_CPU / (16 + (2 * TWBR * 4^TWPS))
   *
   * The TWPS (prescaler) value can be simplified to 1 (the default):
   *
   * SCL = F_CPU / (16 + (2 * TWBR * 1))
   *     = F_CPU / (16 + (2 * TWBR))
   *
   * If we want a standard 100khz SCL clock on a 16mhz CPU, we get:
   *
   * 100000 = 16000000 / (16 + (2 * TWBR))
   *
   * Solving for TWBR yields TWBR = 72.
   */

  TWSR &= ~I2C_STATUS_PRESCALER0;
  TWSR &= ~I2C_STATUS_PRESCALER1;
  TWBR = 72;
}

#endif // I2C_INIT_C
