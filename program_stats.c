#ifndef PROGRAM_STATS_C
#define PROGRAM_STATS_C

#include "program_stats.h"
#include "format.h"
#include "program.h"
#include "rom.h"

#include <stdint.h>

static void program_stats_init(struct ssd1306_t *const display,
                               struct framebuffer_t *const framebuffer) {}

extern const void *_etext;
extern const void *__bss_end;
extern const void *__bss_start;
extern const void *__data_end;
extern const void *__data_start;

static uint32_t program_stats_get_text_size(void) { return (uint16_t)&_etext; }

static uint32_t program_stats_get_data_size(void) {
  const uint16_t bss_end = (uint16_t)&__bss_end;
  const uint16_t bss_start = (uint16_t)&__bss_start;
  const uint16_t bss_size = bss_end - bss_start;
  const uint16_t data_end = (uint16_t)&__data_end;
  const uint16_t data_start = (uint16_t)&__data_start;
  const uint16_t data_size = data_end - data_start;
  return bss_size + data_size;
}

static void program_stats_run(struct ssd1306_t *const display,
                              struct framebuffer_t *const framebuffer) {
  framebuffer_init(framebuffer);

  framebuffer_render_text_P(framebuffer, PSTR("TEXT "), 8, 8);
  framebuffer_render_text_P(framebuffer, PSTR("DATA "), 8, 16);
  framebuffer_render_text_P(framebuffer, PSTR("VERS "), 8, 24);

  char buffer[FORMAT_U32_SIZE_BASE2];
  buffer[formatU32D(buffer, program_stats_get_text_size())] = 0;
  framebuffer_render_text(framebuffer, buffer, 56, 8);
  buffer[formatU32D(buffer, program_stats_get_data_size())] = 0;
  framebuffer_render_text(framebuffer, buffer, 56, 16);
  framebuffer_render_text_P(framebuffer, rom_version, 56, 24);

  framebuffer_send(display, framebuffer);
}

const struct program_t program_stats = {
    .init = &program_stats_init,
    .run = &program_stats_run,
};

#endif // PROGRAM_STATS_C
