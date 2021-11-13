#ifndef I2C_H
#define I2C_H

#include <stdint.h>

struct i2c_t {
  uint8_t status;
};

void i2c_init(struct i2c_t *const);
void i2c_reset(struct i2c_t *const);
uint8_t i2c_start(struct i2c_t *const, uint8_t address);
uint8_t i2c_write(struct i2c_t *const, uint8_t data);
void i2c_stop(struct i2c_t *const);

#endif // I2C_H
