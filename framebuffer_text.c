#ifndef FRAMEBUFFER_TEXT_C
#define FRAMEBUFFER_TEXT_C

#include "framebuffer.h"
#include "rom.h"
#include <avr/pgmspace.h>

struct framebuffer_blit_t framebuffer_rom_blit_text = {
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

void framebuffer_render_text_P(struct framebuffer_t *const f, const char *text,
                               uint8_t x, uint8_t y) {
  struct rom_character_t rom_char;

  framebuffer_rom_blit_text.source_image_width = ROM_WIDTH;
  framebuffer_rom_blit_text.source_image_height = ROM_HEIGHT;
  framebuffer_rom_blit_text.blit_width = 8;
  framebuffer_rom_blit_text.blit_height = 8;
  framebuffer_rom_blit_text.source_x = 0;
  framebuffer_rom_blit_text.source_y = 0;
  framebuffer_rom_blit_text.target_x = x;
  framebuffer_rom_blit_text.target_y = y;

  const char *ptr = text;
  uint8_t x_now = x;

  for (;;) {
    const char ch = pgm_read_byte(ptr);
    if (ch == 0) {
      break;
    }

    rom_character_for(&rom_char, ch);
    framebuffer_rom_blit_text.source_x = rom_char.source_x;
    framebuffer_rom_blit_text.source_y = rom_char.source_y;
    framebuffer_rom_blit_text.target_x = x_now;
    framebuffer_blit(f, &framebuffer_rom_blit_text);
    x_now += 8;
    ++ptr;
  }
}

void framebuffer_render_text(struct framebuffer_t *const f, const char *text,
                             uint8_t x, uint8_t y) {
  struct rom_character_t rom_char;
  framebuffer_rom_blit_text.source_image_width = ROM_WIDTH;
  framebuffer_rom_blit_text.source_image_height = ROM_HEIGHT;
  framebuffer_rom_blit_text.blit_width = 8;
  framebuffer_rom_blit_text.blit_height = 8;
  framebuffer_rom_blit_text.source_x = 0;
  framebuffer_rom_blit_text.source_y = 0;
  framebuffer_rom_blit_text.target_x = x;
  framebuffer_rom_blit_text.target_y = y;

  const char *ptr = text;
  uint8_t x_now = x;

  for (;;) {
    const char ch = *ptr;
    if (ch == 0) {
      break;
    }

    rom_character_for(&rom_char, ch);
    framebuffer_rom_blit_text.source_x = rom_char.source_x;
    framebuffer_rom_blit_text.source_y = rom_char.source_y;
    framebuffer_rom_blit_text.target_x = x_now;
    framebuffer_blit(f, &framebuffer_rom_blit_text);
    x_now += 8;
    ++ptr;
  }
}

#endif // FRAMEBUFFER_TEXT_C
