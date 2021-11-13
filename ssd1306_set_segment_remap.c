#ifndef SSD1306_SET_SEGMENT_REMAP_C
#define SSD1306_SET_SEGMENT_REMAP_C

#include "i2c.h"
#include "ssd1306.h"

uint8_t ssd1306_set_segment_remap(struct ssd1306_t *const sd,
                                  ssd1306_segment_remap_t segment) {
  return ssd1306_send_command(sd, segment);
}

#endif // SSD1306_SET_SEGMENT_REMAP_C
