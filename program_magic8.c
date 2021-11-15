#ifndef PROGRAM_MAGIC8_C
#define PROGRAM_MAGIC8_C

#include "program_magic8.h"
#include "program.h"

#include <stdint.h>
#include <stdlib.h>

typedef enum { MAGIC8_ASK, MAGIC8_ROLLING, MAGIC8_ANSWERED } magic8_state_t;

static magic8_state_t program_magic8_state = MAGIC8_ASK;
static uint8_t program_magic8_timer;
static uint8_t program_answer_length;
static const char *program_answer;

static const char program_magic8_r0[] PROGMEM = "UNLIKELY";
static const char program_magic8_r1[] PROGMEM = "CERTAINLY";
static const char program_magic8_r2[] PROGMEM = "I DON'T CARE";
static const char program_magic8_r3[] PROGMEM = "DOUBTFUL";
static const char program_magic8_r4[] PROGMEM = "YES";
static const char program_magic8_r5[] PROGMEM = "UNCLEAR";
static const char program_magic8_r6[] PROGMEM = "NEVER";
static const char program_magic8_r7[] PROGMEM = "ABSOLUTELY";
static const char program_magic8_r8[] PROGMEM = "WHO KNOWS?";

static const char *const program_magic8_responses[] PROGMEM = {
    program_magic8_r0, program_magic8_r1, program_magic8_r2,
    program_magic8_r3, program_magic8_r4, program_magic8_r5,
    program_magic8_r6, program_magic8_r7, program_magic8_r8};

static const uint8_t program_magic8_responses_count =
    sizeof(program_magic8_responses) / sizeof(const char *);

static void program_magic8_init(struct program_context_t *context) {
  struct ssd1306_t *const display = context->display;
  ssd1306_set_invert_off(display);

  program_magic8_state = MAGIC8_ASK;
}

static program_sleep_t program_magic8_run(struct program_context_t *context) {
  struct framebuffer_t *const framebuffer = context->framebuffer;

  framebuffer_init(framebuffer);

  switch (program_magic8_state) {
  case MAGIC8_ASK: {
    if (buttons_changed(context->buttons) && button_1_set(context->buttons)) {
      program_magic8_state = MAGIC8_ROLLING;
      program_magic8_timer = 30;
      return PROGRAM_NO_SLEEP;
    }

    framebuffer_render_text_P(framebuffer, PSTR("ASK"), 48, 16);
    framebuffer_render_text_P(framebuffer, PSTR("..."), 48, 24);
    framebuffer_render_text_P(framebuffer, PSTR("THEN PRESS B"), 16, 48);
    return PROGRAM_SLEEP;
  }

  case MAGIC8_ROLLING: {
    --program_magic8_timer;

    framebuffer_rom_blit_data.blit_width = 32;
    framebuffer_rom_blit_data.blit_height = 32;
    framebuffer_rom_blit_data.source_x = 48;
    framebuffer_rom_blit_data.source_y = 96;
    framebuffer_rom_blit_data.target_x = 64 - (32 >> 1);
    framebuffer_rom_blit_data.target_y = 16 + (program_magic8_timer & 1);
    framebuffer_blit(context->framebuffer, &framebuffer_rom_blit_data);

    if (program_magic8_timer == 0) {
      const uint8_t index = random() % program_magic8_responses_count;
      program_answer = pgm_read_ptr(program_magic8_responses + index);
      program_answer_length = strlen_P(program_answer) * 8;
      program_magic8_state = MAGIC8_ANSWERED;
    }
    return PROGRAM_NO_SLEEP;
  }
  case MAGIC8_ANSWERED: {
    if (buttons_changed(context->buttons) && button_1_set(context->buttons)) {
      program_magic8_state = MAGIC8_ASK;
      return PROGRAM_NO_SLEEP;
    }

    const uint8_t x = 64 - (program_answer_length >> 1);
    framebuffer_render_text_P(framebuffer, program_answer, x, 32);
    return PROGRAM_SLEEP;
  }
  }

  return PROGRAM_SLEEP;
}

static PGM_P program_magic8_name(void) { return PSTR("magic8"); }

const struct program_t program_magic8 = {
    .name = &program_magic8_name,
    .init = &program_magic8_init,
    .run = &program_magic8_run,
};

#endif // PROGRAM_MAGIC8_C
