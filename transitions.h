#ifndef TRANSITIONS_H
#define TRANSITIONS_H

#include "framebuffer.h"
#include "ssd1306.h"

void transition_vbars(struct ssd1306_t *const display,
                      struct framebuffer_t *const framebuffer);

#endif
