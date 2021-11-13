#ifndef SSD1306_SET_PRECHARGE_PERIOD_C
#define SSD1306_SET_PRECHARGE_PERIOD_C

#include "i2c.h"
#include "ssd1306.h"

uint8_t ssd1306_set_precharge_period(struct ssd1306_t *const sd,
                                     uint8_t period) {
  if (!ssd1306_send_command(sd, SSD1306_SET_PRECHARGE_PERIOD)) {
    return 0;
  }
  if (!ssd1306_send_command(sd, period)) {
    return 0;
  }
  return 1;
}

#endif // SSD1306_SET_PRECHARGE_PERIOD_C
