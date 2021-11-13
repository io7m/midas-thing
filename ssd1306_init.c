#ifndef SSD1306_INIT_C
#define SSD1306_INIT_C

#include "i2c.h"
#include "ssd1306.h"

void ssd1306_init(struct ssd1306_t *const sd, uint8_t address) {
  sd->address = address;
  i2c_init(&sd->i2c);
}

#endif // SSD1306_INIT_C
