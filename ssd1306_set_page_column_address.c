#ifndef SSD1306_SET_PAGE_COLUMN_ADDRESS_C
#define SSD1306_SET_PAGE_COLUMN_ADDRESS_C

#include "i2c.h"
#include "ssd1306.h"

uint8_t ssd1306_set_page_column_address(struct ssd1306_t *const sd,
                                        uint8_t address) {
  const uint8_t low = address & 0b00001111;
  const uint8_t high = (address & 0b11110000) >> 4;

  if (!ssd1306_send_command(sd, SSD1306_SET_COLUMN_ADDRESS_LOW_4B_0 | low)) {
    return 0;
  }
  if (!ssd1306_send_command(sd, SSD1306_SET_COLUMN_ADDRESS_HIGH_4B_0 | high)) {
    return 0;
  }
  return 1;
}

#endif // SSD1306_SET_PAGE_COLUMN_ADDRESS_C
