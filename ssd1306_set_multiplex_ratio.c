#ifndef SSD1306_SET_MULTIPLEX_RATIO_C
#define SSD1306_SET_MULTIPLEX_RATIO_C

#include "i2c.h"
#include "ssd1306.h"

uint8_t ssd1306_set_multiplex_ratio(struct ssd1306_t *const sd, uint8_t ratio) {
  if (!ssd1306_send_command(sd, SSD1306_SET_MULTIPLEX_RATIO)) {
    return 0;
  }
  if (!ssd1306_send_command(sd, ratio)) {
    return 0;
  }
  return 1;
}

#endif // SSD1306_SET_MULTIPLEX_RATIO_C
