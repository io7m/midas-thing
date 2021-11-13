#ifndef SSD1306_SEND_COMMAND_C
#define SSD1306_SEND_COMMAND_C

#include "i2c.h"
#include "ssd1306.h"

uint8_t ssd1306_send_command(struct ssd1306_t *const sd, uint8_t command) {
  struct i2c_t *const i2c = &sd->i2c;

  if (!i2c_start(i2c, sd->address)) {
    return 0;
  }
  if (!i2c_write(i2c, 0x0)) {
    return 0;
  }
  if (!i2c_write(i2c, command)) {
    return 0;
  }

  i2c_stop(i2c);
  return 1;
}

#endif // SSD1306_SEND_COMMAND_C
