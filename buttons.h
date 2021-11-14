#ifndef BUTTONS_H
#define BUTTONS_H

#include <stdint.h>

typedef enum {
  BUTTON_0 = 0b0001,
  BUTTON_1 = 0b0010,
  BUTTON_2 = 0b0100,
  BUTTON_3 = 0b1000
} button_t;

#define BUTTONS_CHANGED 0b1000000

struct buttons_t {
  uint8_t buttons;
};

uint8_t button_0_set(const struct buttons_t *const b);
uint8_t button_1_set(const struct buttons_t *const b);
uint8_t button_2_set(const struct buttons_t *const b);
uint8_t button_3_set(const struct buttons_t *const b);
void button_set_changed(struct buttons_t *const b, uint8_t c);
uint8_t buttons_changed(const struct buttons_t *const b);

#endif // BUTTONS_H
