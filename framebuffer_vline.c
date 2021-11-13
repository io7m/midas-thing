#ifndef FRAMEBUFFER_SEND_C
#define FRAMEBUFFER_SEND_C

#include "framebuffer.h"

void framebuffer_render_vline(struct framebuffer_t *const f, uint8_t x,
                              uint8_t y0, uint8_t y1, uint8_t v) {
  uint8_t *const data = f->data;

  const uint8_t x_safe = x & (FRAMEBUFFER_WIDTH - 1);
  const uint8_t y0_safe = y0 & (FRAMEBUFFER_HEIGHT - 1);
  const uint8_t y1_safe = y1 & (FRAMEBUFFER_HEIGHT - 1);

  for (uint8_t y = y0_safe; y < y1_safe; ++y) {
    const uint8_t y_pages = y / 8;
    const uint16_t index_row_start = y_pages * FRAMEBUFFER_WIDTH;
    const uint16_t index_byte = index_row_start + x_safe;
    const uint8_t ybit = y & 7;
    const uint8_t current = data[index_byte];

    if (v) {
      data[index_byte] = current | (1 << ybit);
    } else {
      data[index_byte] = current & ~(1 << ybit);
    }
  }
}

#endif // FRAMEBUFFER_SEND_C
