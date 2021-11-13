#ifndef FORMAT_H
#define FORMAT_H

#include <stdint.h>

#define FORMAT_U8_SIZE_BASE2 (8 + 1)
#define FORMAT_U8_SIZE_BASE8 (7 + 1)
#define FORMAT_U8_SIZE_BASE10 (3 + 1)
#define FORMAT_U8_SIZE_BASE16 (2 + 1)

uint8_t formatU8D(char *str, uint8_t x);
uint8_t formatU8X(char *str, uint8_t x);
uint8_t formatU8O(char *str, uint8_t x);
uint8_t formatU8B(char *str, uint8_t x);

#endif // FORMAT_H
