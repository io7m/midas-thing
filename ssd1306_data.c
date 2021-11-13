#ifndef SSD1306_DATA_C
#define SSD1306_DATA_C

#include "i2c.h"
#include "ssd1306.h"

uint8_t ssd1306_data_start(struct ssd1306_t *const sd) {
  struct i2c_t *const i2c = &sd->i2c;

  if (!i2c_start(i2c, sd->address)) {
    return 0;
  }
  if (!i2c_write(i2c, 0x40)) {
    return 0;
  }
  return 1;
}

uint8_t ssd1306_data_write(struct ssd1306_t *const sd, uint8_t data) {
  struct i2c_t *const i2c = &sd->i2c;

  if (!i2c_write(i2c, data)) {
    return 0;
  }
  return 1;
}

uint8_t ssd1306_data_finish(struct ssd1306_t *const sd) {
  struct i2c_t *const i2c = &sd->i2c;

  i2c_stop(i2c);
  return 1;
}

#endif // SSD1306_DATA_C
