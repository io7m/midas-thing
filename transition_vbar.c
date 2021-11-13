#ifndef TRANSITION_VBAR_C
#define TRANSITION_VBAR_C

#include "transitions.h"

void transition_vbars(struct ssd1306_t *const display,
                      struct framebuffer_t *const framebuffer) {

  const uint8_t y0 = 0;
  const uint8_t y1 = FRAMEBUFFER_HEIGHT - 1;

  for (uint8_t t = 0; t < 8; ++t) {
    for (uint8_t x = 0; x < FRAMEBUFFER_WIDTH / 8; ++x) {
      framebuffer_render_vline(framebuffer, (x * 8) + t, y0, y1, 1);
    }
    framebuffer_send(display, framebuffer);
  }

  for (uint8_t t = 0; t < 8; ++t) {
    for (uint8_t x = 0; x < FRAMEBUFFER_WIDTH / 8; ++x) {
      framebuffer_render_vline(framebuffer, (x * 8) + t, y0, y1, 0);
    }
    framebuffer_send(display, framebuffer);
  }
}

#endif // TRANSITION_VBAR_C
