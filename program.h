#ifndef PROGRAM_H
#define PROGRAM_H

#include "buttons.h"
#include "framebuffer.h"
#include "ssd1306.h"

#include <avr/pgmspace.h>

typedef enum { PROGRAM_NO_SLEEP = 0, PROGRAM_SLEEP = 1 } program_sleep_t;

struct program_context_t {
  struct ssd1306_t *const display;
  struct framebuffer_t *const framebuffer;
  const struct buttons_t *const buttons;
};

struct program_t {
  PGM_P (*name)(void);
  void (*init)(struct program_context_t *context);
  program_sleep_t (*run)(struct program_context_t *context);
};

#endif
