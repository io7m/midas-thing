#ifndef FRAMEBUFFER_TEXT_C
#define FRAMEBUFFER_TEXT_C

#include "framebuffer.h"
#include "rom.h"
#include <avr/pgmspace.h>

void framebuffer_render_text_P(struct framebuffer_t *const f, const char *text,
                               uint8_t x, uint8_t y) {
  struct rom_character_t rom_char;
  struct framebuffer_blit_t blit;

  blit.source = rom;
  blit.source_flash = 1;
  blit.source_image_width = ROM_WIDTH;
  blit.source_image_height = ROM_HEIGHT;
  blit.blit_width = 8;
  blit.blit_height = 8;
  blit.source_x = 0;
  blit.source_y = 0;
  blit.target_x = x;
  blit.target_y = y;

  const char *ptr = text;
  uint8_t x_now = x;

  for (;;) {
    const char ch = pgm_read_byte(ptr);
    if (ch == 0) {
      break;
    }

    rom_character_for(&rom_char, ch);
    blit.source_x = rom_char.source_x;
    blit.source_y = rom_char.source_y;
    blit.target_x = x_now;

    framebuffer_blit(f, &blit);
    x_now += 8;
    ++ptr;
  }
}

void framebuffer_render_text(struct framebuffer_t *const f, const char *text,
                             uint8_t x, uint8_t y) {
  struct rom_character_t rom_char;
  struct framebuffer_blit_t blit;

  blit.source = rom;
  blit.source_flash = 1;
  blit.source_image_width = ROM_WIDTH;
  blit.source_image_height = ROM_HEIGHT;
  blit.blit_width = 8;
  blit.blit_height = 8;
  blit.source_x = 0;
  blit.source_y = 0;
  blit.target_x = x;
  blit.target_y = y;

  const char *ptr = text;
  uint8_t x_now = x;

  for (;;) {
    const char ch = *ptr;
    if (ch == 0) {
      break;
    }

    rom_character_for(&rom_char, ch);
    blit.source_x = rom_char.source_x;
    blit.source_y = rom_char.source_y;
    blit.target_x = x_now;

    framebuffer_blit(f, &blit);
    x_now += 8;
    ++ptr;
  }
}

#endif // FRAMEBUFFER_TEXT_C
