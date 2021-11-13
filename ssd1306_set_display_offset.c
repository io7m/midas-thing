#ifndef SSD1306_SET_DISPLAY_OFFSET_C
#define SSD1306_SET_DISPLAY_OFFSET_C

#include "i2c.h"
#include "ssd1306.h"

uint8_t ssd1306_set_display_offset(struct ssd1306_t *const sd, uint8_t offset) {
  if (!ssd1306_send_command(sd, SSD1306_SET_DISPLAY_OFFSET)) {
    return 0;
  }
  if (!ssd1306_send_command(sd, offset)) {
    return 0;
  }
  return 1;
}

#endif // SSD1306_SET_DISPLAY_OFFSET_C
