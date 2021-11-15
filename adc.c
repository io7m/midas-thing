#ifndef ADC_C
#define ADC_C

#include <avr/io.h>

#include "adc.h"

void adc_init(void) { ADCSRA |= 1 << ADEN; }

uint16_t adc_read(adc_t adc) {
  ADMUX = 0b01000000;
  ADMUX |= adc;
  ADCSRA |= (1 << ADSC);

  for (;;) {
    if ((ADCSRA & ADSC) == 0) {
      break;
    }
  }

  return ADC;
}

#endif // ADC_C
