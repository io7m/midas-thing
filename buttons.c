#ifndef BUTTONS_C
#define BUTTONS_C

#include "buttons.h"

uint8_t button_0_set(const struct buttons_t *const b) {
  return (b->buttons & BUTTON_0) == BUTTON_0;
}

uint8_t button_1_set(const struct buttons_t *const b) {
  return (b->buttons & BUTTON_1) == BUTTON_1;
}

uint8_t button_2_set(const struct buttons_t *const b) {
  return (b->buttons & BUTTON_2) == BUTTON_2;
}

uint8_t button_3_set(const struct buttons_t *const b) {
  return (b->buttons & BUTTON_3) == BUTTON_3;
}

void button_set_changed(struct buttons_t *const b, uint8_t c) {
  if (c) {
    b->buttons |= BUTTONS_CHANGED;
  } else {
    b->buttons &= ~BUTTONS_CHANGED;
  }
}

uint8_t buttons_changed(const struct buttons_t *const b) {
  return (b->buttons & BUTTONS_CHANGED) == BUTTONS_CHANGED;
}

#endif // BUTTONS_C
