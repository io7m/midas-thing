#ifndef ROM_H
#define ROM_H

#include <avr/pgmspace.h>

#define ROM_WIDTH 128
#define ROM_HEIGHT 128
#define ROM_SIZE ((ROM_WIDTH * ROM_HEIGHT) / 8)

struct rom_character_t {
  uint8_t source_x;
  uint8_t source_y;
};

void rom_character_for(struct rom_character_t *const rom, char ch);

uint8_t rom_random_8();

extern const uint8_t rom[ROM_SIZE] PROGMEM;

PGM_P rom_version(void);

#endif // ROM_H
