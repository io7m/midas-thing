#ifndef PROGRAM_NOISE_C
#define PROGRAM_NOISE_C

#include "program_noise.h"
#include "adc.h"
#include "program.h"
#include <stdint.h>

static void program_noise_init(struct program_context_t *context) {
  struct ssd1306_t *const display = context->display;
  struct framebuffer_t *const framebuffer = context->framebuffer;

  ssd1306_set_invert_off(display);
  framebuffer_init(framebuffer);
}

static program_sleep_t program_noise_run(struct program_context_t *context) {
  struct framebuffer_t *const framebuffer = context->framebuffer;

  framebuffer_init(framebuffer);
  framebuffer_render_text_P(framebuffer, PSTR("ADC0"), 0, 0);

  for (uint8_t x = 0; x < FRAMEBUFFER_WIDTH; ++x) {
    framebuffer_set(framebuffer, x, (FRAMEBUFFER_HEIGHT >> 1), 1);
  }

  for (uint8_t x = 0; x < FRAMEBUFFER_WIDTH; ++x) {
    const int8_t sample0 = adc_read(ADC_0);
    const int8_t sample1 = adc_read(ADC_0);
    const int8_t yupper = sample0 + (FRAMEBUFFER_HEIGHT >> 1);
    const int8_t ylower = -sample1 + (FRAMEBUFFER_HEIGHT >> 1);
    framebuffer_render_vline(framebuffer, x, ylower, yupper, 1);
  }

  for (uint8_t x = 0; x < FRAMEBUFFER_WIDTH; ++x) {
    const int8_t sample0 = adc_read(ADC_0);
    const int8_t sample1 = adc_read(ADC_0);
    const int8_t yupper = sample0 + (FRAMEBUFFER_HEIGHT >> 1);
    const int8_t ylower = -sample1 + (FRAMEBUFFER_HEIGHT >> 1);
    framebuffer_set(framebuffer, x, ylower, 1);
    framebuffer_set(framebuffer, x, yupper, 1);
  }

  return PROGRAM_NO_SLEEP;
}

static PGM_P program_noise_name(void) { return PSTR("noise"); }

const struct program_t program_noise = {
    .name = &program_noise_name,
    .init = &program_noise_init,
    .run = &program_noise_run,
};

#endif // PROGRAM_NOISE_C
