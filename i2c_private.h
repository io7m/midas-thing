#ifndef I2C_PRIVATE_H
#define I2C_PRIVATE_H

#include <util/twi.h>

#define I2C_INTERRUPT ((1 << TWINT))
#define I2C_START ((1 << TWSTA))
#define I2C_STOP ((1 << TWSTO))
#define I2C_ENABLE ((1 << TWEN))
#define I2C_STATUS_PRESCALER1 ((1 << TWPS1))
#define I2C_STATUS_PRESCALER0 ((1 << TWPS0))

#endif // I2C_PRIVATE_H
