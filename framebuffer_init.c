#ifndef FRAMEBUFFER_INIT_C
#define FRAMEBUFFER_INIT_C

#include "framebuffer.h"
#include <string.h>

void framebuffer_init(struct framebuffer_t *const f) {
  uint8_t *const data = f->data;
  memset(data, 0, FRAMEBUFFER_SIZE);
}

#endif // FRAMEBUFFER_INIT_C
