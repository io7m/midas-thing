#ifndef PROGRAM_STATS_C
#define PROGRAM_STATS_C

#include "program_stats.h"
#include "format.h"
#include "program.h"
#include "rom.h"

#include <stdint.h>

static void program_stats_init(struct program_context_t *context) {
  struct ssd1306_t *const display = context->display;

  ssd1306_set_invert_off(display);
}

static program_sleep_t program_stats_run(struct program_context_t *context) {
  struct framebuffer_t *const framebuffer = context->framebuffer;

  framebuffer_init(framebuffer);

  framebuffer_render_text_P(framebuffer, PSTR("TEXT "), 8, 8);
  framebuffer_render_text_P(framebuffer, PSTR("DATA "), 8, 16);
  framebuffer_render_text_P(framebuffer, PSTR("VERS "), 8, 24);

  framebuffer_render_text_P(framebuffer, rom_version(), 56, 24);
  return PROGRAM_SLEEP;
}

static PGM_P program_stats_name(void) { return PSTR("stats"); }

const struct program_t program_stats = {
    .name = &program_stats_name,
    .init = &program_stats_init,
    .run = &program_stats_run,
};

#endif // PROGRAM_STATS_C
