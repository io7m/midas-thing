#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

#include "ssd1306.h"
#include <stdint.h>

#define FRAMEBUFFER_WIDTH 128
#define FRAMEBUFFER_HEIGHT 64
#define FRAMEBUFFER_SIZE ((FRAMEBUFFER_WIDTH * FRAMEBUFFER_HEIGHT) / 8)
#define FRAMEBUFFER_PAGE_ROWS (FRAMEBUFFER_HEIGHT / 8)
#define FRAMEBUFFER_ROW_PACKETS (FRAMEBUFFER_WIDTH / 16)

struct framebuffer_t {
  uint8_t data[FRAMEBUFFER_SIZE];
};

_Static_assert(sizeof(struct framebuffer_t) == FRAMEBUFFER_SIZE,
               "framebuffer_t size correct");

void framebuffer_init(struct framebuffer_t *const f);

void framebuffer_set(struct framebuffer_t *const f, uint8_t x, uint8_t y,
                     uint8_t b);

uint8_t framebuffer_send(struct ssd1306_t *const sd,
                         struct framebuffer_t *const f);

struct framebuffer_blit_t {
  const uint8_t *source;
  uint8_t source_flash;
  uint8_t source_image_width;
  uint8_t source_image_height;
  uint8_t source_x;
  uint8_t source_y;
  uint8_t target_x;
  uint8_t target_y;
  uint8_t blit_width;
  uint8_t blit_height;
};

_Static_assert(sizeof(struct framebuffer_blit_t) == 11,
               "framebuffer_blit_t size correct");

void framebuffer_blit(struct framebuffer_t *const f,
                      const struct framebuffer_blit_t *const blit);

extern struct framebuffer_blit_t framebuffer_rom_blit_data;

void framebuffer_render_text_P(struct framebuffer_t *const f, const char *text,
                               uint8_t x, uint8_t y);
void framebuffer_render_text(struct framebuffer_t *const f, const char *text,
                             uint8_t x, uint8_t y);

void framebuffer_render_vline(struct framebuffer_t *const f, uint8_t x,
                              uint8_t y0, uint8_t y1, uint8_t v);

#endif // FRAMEBUFFER_H
