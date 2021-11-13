#ifndef SSD1306_SET_VCOM_DESELECT_C
#define SSD1306_SET_VCOM_DESELECT_C

#include "i2c.h"
#include "ssd1306.h"

uint8_t ssd1306_set_vcom_deselect(struct ssd1306_t *const sd,
                                  uint8_t deselect) {
  if (!ssd1306_send_command(sd, SSD1306_SET_VCOM_DESELECT)) {
    return 0;
  }
  if (!ssd1306_send_command(sd, deselect)) {
    return 0;
  }
  return 1;
}

#endif // SSD1306_SET_VCOM_DESELECT_C
