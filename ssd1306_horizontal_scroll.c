#ifndef SSD1306_SET_HORIZONTAL_SCROLL_C
#define SSD1306_SET_HORIZONTAL_SCROLL_C

#include "i2c.h"
#include "ssd1306.h"

uint8_t ssd1306_horizontal_scroll(struct ssd1306_t *const sd,
                                  ssd1306_horizontal_scroll_t direction,
                                  uint8_t page_start,
                                  ssd1306_scroll_rate_t scroll_rate,
                                  uint8_t page_end) {
  if (!ssd1306_send_command(sd, SD1306_DEACTIVATE_SCROLL)) {
    return 0;
  }
  return 0;
}

#endif // SSD1306_SET_HORIZONTAL_SCROLL_C
