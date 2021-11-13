#ifndef SSD1306_SET_CLOCK_DIVIDER_C
#define SSD1306_SET_CLOCK_DIVIDER_C

#include "i2c.h"
#include "ssd1306.h"

uint8_t ssd1306_set_clock_divider(struct ssd1306_t *const sd, uint8_t divider) {
  if (!ssd1306_send_command(sd, SSD1306_SET_DISPLAY_CLOCK_DIVIDER)) {
    return 0;
  }
  if (!ssd1306_send_command(sd, divider)) {
    return 0;
  }
  return 1;
}

#endif // SSD1306_SET_CLOCK_DIVIDER_C
