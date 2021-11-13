#ifndef ROM_H
#define ROM_H

#include <avr/pgmspace.h>

#define ROM_WIDTH 128
#define ROM_HEIGHT 128
#define ROM_SIZE ((ROM_WIDTH * ROM_HEIGHT) / 8)

extern const uint8_t rom[ROM_SIZE] PROGMEM;

#endif // ROM_H
