#ifndef PROGRAM_STATS_C
#define PROGRAM_STATS_C

#include "program_stats.h"
#include "format.h"
#include "program.h"
#include "rom.h"
#include "sizes.h"

#include <stdint.h>

static char program_stats_format[FORMAT_U16_SIZE_BASE10];

static void program_stats_init(struct program_context_t *context) {
  struct ssd1306_t *const display = context->display;

  ssd1306_set_invert_off(display);
}

static program_sleep_t program_stats_run(struct program_context_t *context) {
  struct framebuffer_t *const framebuffer = context->framebuffer;

  framebuffer_init(framebuffer);

  framebuffer_render_text_P(framebuffer, PSTR("TEXT "), 8, 8);
  framebuffer_render_text_P(framebuffer, PSTR("DATA "), 8, 16);
  framebuffer_render_text_P(framebuffer, PSTR("STACK"), 8, 24);
  framebuffer_render_text_P(framebuffer, PSTR("VERS "), 8, 32);

  program_stats_format[formatU16D(program_stats_format, size_text())] = 0;
  framebuffer_render_text(framebuffer, program_stats_format, 64, 8);

  const uint16_t bss = size_bss();
  const uint16_t data = size_data();
  program_stats_format[formatU16D(program_stats_format, bss + data)] = 0;
  framebuffer_render_text(framebuffer, program_stats_format, 64, 16);

  program_stats_format[formatU16D(program_stats_format, size_stack())] = 0;
  framebuffer_render_text(framebuffer, program_stats_format, 64, 24);

  framebuffer_render_text_P(framebuffer, rom_version(), 64, 32);
  return PROGRAM_SLEEP;
}

static PGM_P program_stats_name(void) { return PSTR("stats"); }

const struct program_t program_stats = {
    .name = &program_stats_name,
    .init = &program_stats_init,
    .run = &program_stats_run,
};

#endif // PROGRAM_STATS_C
