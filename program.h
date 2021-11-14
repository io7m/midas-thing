#ifndef PROGRAM_H
#define PROGRAM_H

#include "framebuffer.h"
#include "ssd1306.h"

#include <avr/pgmspace.h>

struct program_t {
  PGM_P (*name)(void);

  void (*init)(struct ssd1306_t *const display,
               struct framebuffer_t *const framebuffer);

  void (*run)(struct ssd1306_t *const display,
              struct framebuffer_t *const framebuffer);
};

#endif
