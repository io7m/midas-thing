#ifndef ADC_H
#define ADC_H

#include <stdint.h>

typedef enum {
  ADC_0 = 0b000,
  ADC_1 = 0b001,
  ADC_2 = 0b010,
  ADC_3 = 0b011
} adc_t;

void adc_init(void);
uint16_t adc_read(adc_t adc);

#endif // ADC_H
