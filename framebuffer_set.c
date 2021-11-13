#ifndef FRAMEBUFFER_SET_C
#define FRAMEBUFFER_SET_C

#include "framebuffer.h"

void framebuffer_set(struct framebuffer_t *const f, uint8_t x, uint8_t y,
                     uint8_t b) {
  uint8_t *const data = f->data;

  /*
   * Clamp x to [0 .. FRAMEBUFFER_WIDTH).
   * Clamp y to [0 .. FRAMEBUFFER_HEIGHT).
   */

  const uint8_t xsafe = x & (FRAMEBUFFER_WIDTH - 1);
  const uint8_t ysafe = y & (FRAMEBUFFER_HEIGHT - 1);

  /*
   * The framebuffer is divided up into (FRAMEBUFFER_HEIGHT / 8) rows.
   * A row consists of FRAMEBUFFER_WIDTH vertical strips of 8 pixels.
   * The datasheet refers to these vertical strips of pixels as "pages".
   *
   * Effectively, each byte in the framebuffer stores 8 pixels. In
   * order to set a single pixel, we need to work out what page byte
   * to modify, and then which bit within that byte to set.
   */

  const uint8_t ypages = ysafe / 8;
  const uint16_t index_row_start = ypages * FRAMEBUFFER_WIDTH;
  const uint16_t index_byte = index_row_start + xsafe;
  const uint8_t ybit = y & 7;
  const uint8_t current = data[index_byte];

  if (b) {
    data[index_byte] = current | (1 << ybit);
  } else {
    data[index_byte] = current & ~(1 << ybit);
  }
}

#endif // FRAMEBUFFER_SET_C
