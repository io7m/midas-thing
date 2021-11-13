#ifndef SSD1306_DISPLAY_OFF_C
#define SSD1306_DISPLAY_OFF_C

#include "i2c.h"
#include "ssd1306.h"

uint8_t ssd1306_display_off(struct ssd1306_t *const sd) {
  return ssd1306_send_command(sd, SSD1306_DISPLAY_OFF);
}

#endif // SSD1306_DISPLAY_OFF_C
