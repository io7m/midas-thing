#ifndef PROGRAM_H
#define PROGRAM_H

#include "buttons.h"
#include "framebuffer.h"
#include "ssd1306.h"

#include <avr/pgmspace.h>

struct program_context_t {
  struct ssd1306_t *const display;
  struct framebuffer_t *const framebuffer;
  const struct buttons_t *const buttons;
};

struct program_t {
  PGM_P (*name)(void);
  void (*init)(struct program_context_t *context);
  void (*run)(struct program_context_t *context);
};

#endif
