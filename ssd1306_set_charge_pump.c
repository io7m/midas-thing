#ifndef SSD1306_SET_CHARGE_PUMP_C
#define SSD1306_SET_CHARGE_PUMP_C

#include "i2c.h"
#include "ssd1306.h"

uint8_t ssd1306_set_charge_pump(struct ssd1306_t *const sd,
                                ssd1306_charge_pump_t charge_pump) {
  if (!ssd1306_send_command(sd, SSD1306_SET_CHARGE_PUMP)) {
    return 0;
  }
  if (!ssd1306_send_command(sd, charge_pump)) {
    return 0;
  }
  return 1;
}

#endif // SSD1306_SET_CHARGE_PUMP_C
