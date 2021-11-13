#ifndef SSD1306_SET_PAGE_ADDRESS_C
#define SSD1306_SET_PAGE_ADDRESS_C

#include "i2c.h"
#include "ssd1306.h"

uint8_t ssd1306_set_page_address(struct ssd1306_t *const sd, uint8_t start,
                                 uint8_t end) {
  if (!ssd1306_send_command(sd, SSD1306_SET_PAGE_ADDRESS)) {
    return 0;
  }
  if (!ssd1306_send_command(sd, start)) {
    return 0;
  }
  if (!ssd1306_send_command(sd, end)) {
    return 0;
  }
  return 1;
}

#endif // SSD1306_SET_PAGE_ADDRESS_C
