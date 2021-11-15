#ifndef SIZES_H
#define SIZES_H

#include <stdint.h>

uint16_t size_bss(void);
uint16_t size_data(void);
uint16_t size_text(void);
uint16_t size_stack(void);

#endif // SIZES_H
