#ifndef SSD1306_SET_PAGE_COLUMN_ADDRESS_C
#define SSD1306_SET_PAGE_COLUMN_ADDRESS_C

#include "i2c.h"
#include "ssd1306.h"

uint8_t ssd1306_set_page_start_address(struct ssd1306_t *const sd,
                                       uint8_t address) {
  const uint8_t addr3 = address & 0b111;

  if (!ssd1306_send_command(sd, SSD1306_SET_PAGE_START_ADDRESS_0 | addr3)) {
    return 0;
  }
  return 1;
}

#endif // SSD1306_SET_PAGE_COLUMN_ADDRESS_C
