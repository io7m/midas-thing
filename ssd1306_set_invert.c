#ifndef SSD1306_SET_INVERT_C
#define SSD1306_SET_INVERT_C

#include "i2c.h"
#include "ssd1306.h"

uint8_t ssd1306_set_invert_on(struct ssd1306_t *const sd) {
  return ssd1306_send_command(sd, SSD1306_SET_DISPLAY_INVERT);
}

uint8_t ssd1306_set_invert_off(struct ssd1306_t *const sd) {
  return ssd1306_send_command(sd, SSD1306_SET_DISPLAY_NORMAL);
}

#endif // SSD1306_SET_INVERT_C
