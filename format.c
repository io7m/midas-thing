#ifndef FORMAT_C
#define FORMAT_C

#include "format.h"
#include <avr/pgmspace.h>

static const char HEX[] PROGMEM = "0123456789abcdef";

uint8_t formatU8B(char *str, uint8_t x) {
  uint8_t quotient = x;
  uint8_t length = 1;

  /*
   * Determine the number of digits.
   */

  while (quotient > 1) {
    ++length;
    quotient /= 2;
  }

  /*
   * Render digits.
   */

  uint8_t index = length - 1;
  for (;;) {
    const char ch = '0' + (x % 2);
    str[index] = ch;
    x /= 2;

    if (index == 0) {
      break;
    }
    --index;
  }

  return length;
}

uint8_t formatU8X(char *str, uint8_t x) {
  uint8_t quotient = x;
  uint8_t length = 1;

  /*
   * Determine the number of digits.
   */

  while (quotient > 15) {
    ++length;
    quotient /= 16;
  }

  /*
   * Render digits.
   */

  uint8_t index = length - 1;
  for (;;) {
    const char ch = pgm_read_byte(HEX + (x & 15));
    str[index] = ch;
    x /= 16;

    if (index == 0) {
      break;
    }
    --index;
  }

  return length;
}

uint8_t formatU16D(char *str, uint16_t x) {
  uint16_t quotient = x;
  uint8_t length = 1;

  /*
   * Determine the number of digits.
   */

  while (quotient > 9) {
    ++length;
    quotient /= 10;
  }

  /*
   * Render digits.
   */

  uint8_t index = length - 1;
  for (;;) {
    const char ch = '0' + (x % 10);
    str[index] = ch;
    x /= 10;

    if (index == 0) {
      break;
    }
    --index;
  }

  return length;
}

uint8_t formatU16X(char *str, uint16_t x) {
  uint16_t quotient = x;
  uint8_t length = 1;

  /*
   * Determine the number of digits.
   */

  while (quotient > 15) {
    ++length;
    quotient /= 16;
  }

  /*
   * Render digits.
   */

  uint8_t index = length - 1;
  for (;;) {
    const char ch = pgm_read_byte(HEX + (x & 15));
    str[index] = ch;
    x /= 16;

    if (index == 0) {
      break;
    }
    --index;
  }

  return length;
}

uint8_t formatU32X(char *str, uint32_t x) {
  uint32_t quotient = x;
  uint8_t length = 1;

  /*
   * Determine the number of digits.
   */

  while (quotient > 15) {
    ++length;
    quotient /= 16;
  }

  /*
   * Render digits.
   */

  uint8_t index = length - 1;
  for (;;) {
    const char ch = pgm_read_byte(HEX + (x & 15));
    str[index] = ch;
    x /= 16;

    if (index == 0) {
      break;
    }
    --index;
  }

  return length;
}

uint8_t formatU32D(char *str, uint32_t x) {
  uint32_t quotient = x;
  uint8_t length = 1;

  /*
   * Determine the number of digits.
   */

  while (quotient > 9) {
    ++length;
    quotient /= 10;
  }

  /*
   * Render digits.
   */

  uint8_t index = length - 1;
  for (;;) {
    const char ch = '0' + (x % 10);
    str[index] = ch;
    x /= 10;

    if (index == 0) {
      break;
    }
    --index;
  }

  return length;
}

#endif // FORMAT_C
