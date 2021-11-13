#ifndef SSD1306_CLEAR_C
#define SSD1306_CLEAR_C

#include "i2c.h"
#include "ssd1306.h"

uint8_t ssd1306_clear(struct ssd1306_t *const sd, uint8_t value) {
  struct i2c_t *const i2c = &sd->i2c;
  const uint8_t address = sd->address;

  for (uint8_t z = 0; z < 8; ++z) {
    for (uint8_t y = 0; y < 8; ++y) {
      if (!i2c_start(i2c, address)) {
        return 0;
      }
      if (!i2c_write(i2c, 0x40)) {
        return 0;
      }
      for (uint8_t x = 0; x < 16; ++x) {
        if (!i2c_write(i2c, value)) {
          return 0;
        }
      }
      i2c_stop(i2c);
    }
  }
  return 1;
}

#endif // SSD1306_CLEAR_C
