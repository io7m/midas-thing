#ifndef FRAMEBUFFER_SEND_C
#define FRAMEBUFFER_SEND_C

#include "framebuffer.h"

uint8_t framebuffer_send(struct ssd1306_t *const sd,
                         struct framebuffer_t *const f) {

  if (!ssd1306_set_memory_addressing_mode(
          sd, SSD1306_MEMORY_ADDRESSING_MODE_PAGE)) {
    return 0;
  }
  if (!ssd1306_set_page_column_address(sd, 0x0)) {
    return 0;
  }

  const uint8_t *const data = f->data;
  uint16_t byte_index = 0;

  for (uint8_t page_row = 0; page_row < FRAMEBUFFER_PAGE_ROWS; ++page_row) {
    if (!ssd1306_set_page_start_address(sd, page_row)) {
      return 0;
    }
    if (!ssd1306_data_start(sd)) {
      return 0;
    }
    for (uint8_t j = 0; j < FRAMEBUFFER_WIDTH; ++j) {
      if (!ssd1306_data_write(sd, data[byte_index])) {
        return 0;
      }
      ++byte_index;
    }
    ssd1306_data_finish(sd);
  }
  return 0;
}

#endif // FRAMEBUFFER_SEND_C
