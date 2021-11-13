#ifndef SSD1306_SET_COM_OUTPUT_SCAN_C
#define SSD1306_SET_COM_OUTPUT_SCAN_C

#include "i2c.h"
#include "ssd1306.h"

uint8_t
ssd1306_set_com_output_scan(struct ssd1306_t *const sd,
                            ssd1306_com_output_scan_direction_t direction) {
  return ssd1306_send_command(sd, direction);
}

#endif // SSD1306_SET_COM_OUTPUT_SCAN_C
