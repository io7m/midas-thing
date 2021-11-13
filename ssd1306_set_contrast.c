#ifndef SSD1306_SET_CONTRAST_C
#define SSD1306_SET_CONTRAST_C

#include "i2c.h"
#include "ssd1306.h"

uint8_t ssd1306_set_contrast(struct ssd1306_t *const sd, uint8_t contrast) {
  if (!ssd1306_send_command(sd, SSD1306_SET_CONTRAST)) {
    return 0;
  }
  if (!ssd1306_send_command(sd, contrast)) {
    return 0;
  }
  return 1;
}

#endif // SSD1306_SET_CONTRAST_C
