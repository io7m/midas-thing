#ifndef SSD1306_SET_MEMORY_ADDRESSING_MODE_C
#define SSD1306_SET_MEMORY_ADDRESSING_MODE_C

#include "i2c.h"
#include "ssd1306.h"

uint8_t
ssd1306_set_memory_addressing_mode(struct ssd1306_t *const sd,
                                   ssd1306_memory_addressing_mode_t mode) {
  if (!ssd1306_send_command(sd, SSD1306_SET_MEMORY_ADDRESSING_MODE)) {
    return 0;
  }
  if (!ssd1306_send_command(sd, mode)) {
    return 0;
  }
  return 1;
}

#endif // SSD1306_SET_MEMORY_ADDRESSING_MODE_C
