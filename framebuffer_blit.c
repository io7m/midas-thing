#ifndef FRAMEBUFFER_BLIT_C
#define FRAMEBUFFER_BLIT_C

#include <avr/pgmspace.h>

#include "framebuffer.h"
#include "rom.h"

struct framebuffer_blit_t framebuffer_rom_blit_data = {
    .blit_height = 0,
    .blit_width = 0,
    .source = rom,
    .source_flash = 1,
    .source_image_width = ROM_WIDTH,
    .source_image_height = ROM_HEIGHT,
    .source_x = 0,
    .source_y = 0,
    .target_x = 0,
    .target_y = 0};

static void framebuffer_blit_sram(struct framebuffer_t *const f,
                                  const struct framebuffer_blit_t *const blit) {

  const uint8_t blit_width = blit->blit_width;
  const uint8_t blit_height = blit->blit_height;
  const uint8_t source_min_x = blit->source_x;
  const uint8_t source_min_y = blit->source_y;
  const uint8_t target_min_x = blit->target_x;
  const uint8_t target_min_y = blit->target_y;
  const uint8_t source_image_width = blit->source_image_width;
  const uint8_t *const source_data = blit->source;

  for (uint8_t y_off = 0; y_off < blit_height; ++y_off) {
    const uint8_t target_y = target_min_y + y_off;
    const uint8_t source_y = source_min_y + y_off;
    const uint8_t source_y_pages = source_y / 8;
    const uint16_t source_row_start_index =
        (uint16_t)source_y_pages * (uint16_t)source_image_width;
    const uint8_t source_y_bit = source_y & 7;

    for (uint8_t x_off = 0; x_off < blit_width; ++x_off) {
      const uint8_t target_x = target_min_x + x_off;
      const uint8_t source_x = source_min_x + x_off;
      const uint16_t source_byte_index =
          (uint16_t)source_row_start_index + (uint16_t)source_x;
      const uint8_t current_byte = source_data[source_byte_index];
      const uint8_t current_bit = (current_byte >> source_y_bit) & 1;

      framebuffer_set(f, target_x, target_y, current_bit);
    }
  }
}

static void
framebuffer_blit_flash(struct framebuffer_t *const f,
                       const struct framebuffer_blit_t *const blit) {

  const uint8_t blit_width = blit->blit_width;
  const uint8_t blit_height = blit->blit_height;
  const uint8_t source_min_x = blit->source_x;
  const uint8_t source_min_y = blit->source_y;
  const uint8_t target_min_x = blit->target_x;
  const uint8_t target_min_y = blit->target_y;
  const uint8_t source_image_width = blit->source_image_width;
  const uint8_t *const source_data = blit->source;

  for (uint8_t y_off = 0; y_off < blit_height; ++y_off) {
    const uint8_t target_y = target_min_y + y_off;
    const uint8_t source_y = source_min_y + y_off;
    const uint8_t source_y_pages = source_y / 8;
    const uint16_t source_row_start_index =
        (uint16_t)source_y_pages * (uint16_t)source_image_width;
    const uint8_t source_y_bit = source_y & 7;

    for (uint8_t x_off = 0; x_off < blit_width; ++x_off) {
      const uint8_t target_x = target_min_x + x_off;
      const uint8_t source_x = source_min_x + x_off;
      const uint16_t source_byte_index =
          (uint16_t)source_row_start_index + (uint16_t)source_x;
      const uint8_t current_byte =
          pgm_read_byte(source_data + source_byte_index);
      const uint8_t current_bit = (current_byte >> source_y_bit) & 1;

      framebuffer_set(f, target_x, target_y, current_bit);
    }
  }
}

void framebuffer_blit(struct framebuffer_t *const f,
                      const struct framebuffer_blit_t *const blit) {
  if (blit->source_flash) {
    framebuffer_blit_flash(f, blit);
  } else {
    framebuffer_blit_sram(f, blit);
  }
}

#endif // FRAMEBUFFER_BLIT_C
