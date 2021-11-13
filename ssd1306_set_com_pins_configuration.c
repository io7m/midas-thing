#ifndef SSD1306_SET_COM_PINS_CONFIGURATION_C
#define SSD1306_SET_COM_PINS_CONFIGURATION_C

#include "i2c.h"
#include "ssd1306.h"

uint8_t ssd1306_set_com_pins_configuration(struct ssd1306_t *const sd,
                                           uint8_t configuration) {
  if (!ssd1306_send_command(sd, SSD1306_SET_COM_PINS_CONFIGURATION)) {
    return 0;
  }
  if (!ssd1306_send_command(sd, configuration)) {
    return 0;
  }
  return 1;
}

#endif // SSD1306_SET_COM_PINS_CONFIGURATION_C
