#ifndef SSD1306_SET_DISPLAY_START_LINE_C
#define SSD1306_SET_DISPLAY_START_LINE_C

#include "i2c.h"
#include "ssd1306.h"

uint8_t ssd1306_set_display_start_line(struct ssd1306_t *const sd,
                                       uint8_t line) {
  const uint8_t line_clamp = line & 0b111111;
  return ssd1306_send_command(sd, SSD1306_SET_START_LINE_0 | line_clamp);
}

#endif // SSD1306_SET_DISPLAY_START_LINE_C
