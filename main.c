#ifndef MAIN_C
#define MAIN_C

#include <avr/io.h>
#include <avr/pgmspace.h>
#include <util/delay.h>
#include <util/twi.h>

#include <stdint.h>

#include "format.h"
#include "i2c.h"
#include "uart.h"

void i2c_error(PGM_P name, uint8_t command, uint8_t status) {
  char buffer[8] = {0};

  uart_puts_P(PSTR("i2c_error: "));
  uart_puts_P(name);
  uart_puts_P(PSTR(" command 0x"));

  buffer[formatU8X(buffer, command)] = 0;
  uart_puts(buffer);

  uart_puts_P(PSTR(" status 0x"));

  buffer[formatU8X(buffer, status)] = 0;
  uart_puts(buffer);

  uart_puts_P(PSTR("\n"));
}

void i2c_crash(PGM_P name, uint8_t command, uint8_t status) {
  i2c_error(name, command, status);

  DDRB = 0b11111111;
  for (;;) {
    PORTB = 0b00000000;
    _delay_ms(100);
    PORTB = 0b11111111;
    _delay_ms(100);
  }
}

#define MIDAS_ADDRESS 0x3C

#define SSD1306_SET_CONTRAST 0x81
#define SSD1306_DISPLAYALLON_RESUME 0xA4
#define SSD1306_DISPLAYALLON 0xA5
#define SSD1306_SET_DISPLAY_NORMAL 0xA6
#define SSD1306_SET_DISPLAY_INVERT 0xA7
#define SSD1306_DISPLAY_OFF 0xAE
#define SSD1306_DISPLAY_ON 0xAF
#define SSD1306_SET_DISPLAY_OFFSET 0xD3
#define SSD1306_SET_COM_PINS_CONFIGURATION 0xDA
#define SSD1306_SET_VCOM_DESELECT 0xDB
#define SSD1306_SET_DISPLAY_CLOCK_DIVIDER 0xD5
#define SSD1306_SET_PRECHARGE_PERIOD 0xD9
#define SSD1306_SET_MULTIPLEX_RATIO 0xA8
#define SSD1306_SET_HIGH_COLUMN 0x10
#define SSD1306_SET_START_LINE_0 0x40
#define SSD1306_SET_COLUMN_ADDRESS 0x21
#define SSD1306_SET_PAGE_ADDRESS 0x22
#define SSD1306_SET_COM_OUTPUT_SCAN_INCREMENT 0xC0
#define SSD1306_SET_COM_OUTPUT_SCAN_DECREMENT 0xC8
#define SSD1306_SET_SEGMENT_REMAP_0 0xA0
#define SSD1306_SET_SEGMENT_REMAP_1 0xA1

#define SSD1306_SET_COLUMN_ADDRESS_LOW_4B_0 0x00
#define SSD1306_SET_COLUMN_ADDRESS_HIGH_4B_0 0x10

typedef enum {
  SSD1306_SET_PAGE_START_ADDRESS_0 = 0xB0,
  SSD1306_SET_PAGE_START_ADDRESS_1 = 0xB1,
  SSD1306_SET_PAGE_START_ADDRESS_2 = 0xB2,
  SSD1306_SET_PAGE_START_ADDRESS_3 = 0xB3,
  SSD1306_SET_PAGE_START_ADDRESS_4 = 0xB4,
  SSD1306_SET_PAGE_START_ADDRESS_5 = 0xB5,
  SSD1306_SET_PAGE_START_ADDRESS_6 = 0xB6,
  SSD1306_SET_PAGE_START_ADDRESS_7 = 0xB7
} ssd1306_set_page_start_address_t;

#define SSD1306_SET_MEMORY_ADDRESSING_MODE 0x20

typedef enum {
  SSD1306_MEMORY_ADDRESSING_MODE_PAGE = 0b00000010,
  SSD1306_MEMORY_ADDRESSING_MODE_HORIZONTAL = 0b00000000,
  SSD1306_MEMORY_ADDRESSING_MODE_VERTICAL = 0b00000001
} ssd1306_memory_addressing_mode_t;

#define SSD1306_SET_CHARGE_PUMP 0x8D
#define SSD1306_SET_CHARGE_PUMP_ENABLE 0x14
#define SSD1306_SET_CHARGE_PUMP_DISABLE 0x10

#define SSD1306_EXTERNALVCC 0x1
#define SSD1306_SWITCHCAPVCC 0x2

static struct i2c_t i2c;

void ssd1306_command(uint8_t data) {
  if (!i2c_start(&i2c, MIDAS_ADDRESS)) {
    i2c_crash(PSTR("i2c_start"), data, i2c.status);
  }
  if (!i2c_write(&i2c, 0x0)) {
    i2c_crash(PSTR("i2c_write_0"), data, i2c.status);
  }
  if (!i2c_write(&i2c, data)) {
    i2c_crash(PSTR("i2c_write_command"), data, i2c.status);
  }

  i2c_stop(&i2c);
}

void ssd1306_clear(uint8_t value) {
  for (uint8_t z = 0; z < 8; ++z) {
    for (uint8_t y = 0; y < 8; ++y) {
      if (!i2c_start(&i2c, MIDAS_ADDRESS)) {
        i2c_crash(PSTR("i2c_start"), MIDAS_ADDRESS, i2c.status);
      }
      if (!i2c_write(&i2c, 0x40)) {
        i2c_crash(PSTR("i2c_write_0"), 0x40, i2c.status);
      }
      for (uint8_t x = 0; x < 16; ++x) {
        if (!i2c_write(&i2c, value)) {
          i2c_crash(PSTR("i2c_write_0"), value, i2c.status);
        }
      }
      i2c_stop(&i2c);
    }
  }
}

int main(void) {
  uart_init();
  // uart_puts_P(PSTR("i: init\n"));

  /*
   * Enable pull-up resistors on port D (the pins attached to the i2c bus).
   */

  DDRD = 0b00000000;
  PORTD = 0b11111111;

  i2c_init(&i2c);

  ssd1306_command(SSD1306_DISPLAY_OFF);

  ssd1306_command(SSD1306_SET_DISPLAY_CLOCK_DIVIDER);
  ssd1306_command(0x80);

  ssd1306_command(SSD1306_SET_MULTIPLEX_RATIO);
  ssd1306_command(63);

  ssd1306_command(SSD1306_SET_DISPLAY_OFFSET);
  ssd1306_command(0x00);

  ssd1306_command(SSD1306_SET_START_LINE_0);

  ssd1306_command(SSD1306_SET_CHARGE_PUMP);
  ssd1306_command(SSD1306_SET_CHARGE_PUMP_ENABLE);

  ssd1306_command(SSD1306_SET_SEGMENT_REMAP_1);

  ssd1306_command(SSD1306_SET_COM_OUTPUT_SCAN_INCREMENT);

  ssd1306_command(SSD1306_SET_COM_PINS_CONFIGURATION);
  ssd1306_command(0x12);

  ssd1306_command(SSD1306_SET_CONTRAST);
  ssd1306_command(0xff);

  ssd1306_command(SSD1306_SET_PRECHARGE_PERIOD);
  ssd1306_command(0xF1);

  ssd1306_command(SSD1306_SET_VCOM_DESELECT);
  ssd1306_command(0x40);

  ssd1306_command(SSD1306_DISPLAYALLON_RESUME);
  ssd1306_command(SSD1306_SET_DISPLAY_NORMAL);
  ssd1306_command(SSD1306_DISPLAY_ON);

  ssd1306_command(SSD1306_SET_MEMORY_ADDRESSING_MODE);
  ssd1306_command(SSD1306_MEMORY_ADDRESSING_MODE_HORIZONTAL);

  ssd1306_command(SSD1306_SET_COLUMN_ADDRESS);
  ssd1306_command(0x0);
  ssd1306_command(0x7f);

  ssd1306_command(SSD1306_SET_PAGE_ADDRESS);
  ssd1306_command(0x0);
  ssd1306_command(0x7);

  // uart_puts_P(PSTR("i: finished init\n"));

  // ssd1306_clear(0xff);

  ssd1306_command(SSD1306_SET_MEMORY_ADDRESSING_MODE);
  ssd1306_command(SSD1306_MEMORY_ADDRESSING_MODE_PAGE);

  ssd1306_command(SSD1306_SET_PAGE_START_ADDRESS_1);
  ssd1306_command(SSD1306_SET_COLUMN_ADDRESS_LOW_4B_0);
  ssd1306_command(SSD1306_SET_COLUMN_ADDRESS_HIGH_4B_0);

  i2c_start(&i2c, MIDAS_ADDRESS);
  i2c_write(&i2c, 0x40);
  i2c_write(&i2c, 0x0);
  i2c_write(&i2c, 0x0);
  i2c_write(&i2c, 0x0);
  i2c_write(&i2c, 0x0);
  i2c_write(&i2c, 0x0);
  i2c_write(&i2c, 0x0);
  i2c_write(&i2c, 0x0);
  i2c_write(&i2c, 0x0);
  i2c_stop(&i2c);

  DDRB = 0b11111111;
  for (;;) {
    PORTB = 0b00000000;
    _delay_ms(1000);
    PORTB = 0b11111111;
    _delay_ms(1000);
  }

  return 0;
}

#endif // MAIN_C
