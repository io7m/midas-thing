#ifndef MAIN2_C
#define MAIN2_C

#include <avr/io.h>
#include <avr/pgmspace.h>
#include <util/delay.h>
#include <util/twi.h>

#include <stdint.h>

#include "format.h"
#include "framebuffer.h"
#include "i2c.h"
#include "logo.h"
#include "rom.h"
#include "ssd1306.h"
#include "uart.h"

#define MIDAS_ADDRESS 0x3C

static struct ssd1306_t ssd1306;

#ifdef PANIC_DEBUG
static void panic_if(uint8_t i, const char *message) {
  if (i == 0) {
    char buffer[8] = {0};
    uart_putchar('E');
    uart_putchar(' ');
    uart_puts_P(message);
    uart_putchar(' ');
    buffer[formatU8X(buffer, ssd1306.i2c.status)] = 0;
    uart_puts(buffer);
    uart_putchar('\n');

    DDRB = 0b11111111;
    for (;;) {
      PORTB = 0b00000000;
      _delay_ms(50);
      PORTB = 0b11111111;
      _delay_ms(50);
    }
  }
}

#define PANIC_STRINGIFY(x) #x
#define PANIC_TOSTRING(x) PANIC_STRINGIFY(x)
#define PANIC_ON_FAILURE(e) (panic_if((e), PSTR(PANIC_TOSTRING(__LINE__))))
#else
#define PANIC_ON_FAILURE(e) (e)
#endif

static struct framebuffer_t framebuffer;

int main(void) {
  uart_init();

  /*
   * Enable pull-up resistors on port D (the pins attached to the i2c bus).
   */

  DDRD = 0b00000000;
  PORTD = 0b11111111;

  ssd1306_init(&ssd1306, MIDAS_ADDRESS);
  framebuffer_init(&framebuffer);

  PANIC_ON_FAILURE(ssd1306_display_off(&ssd1306));
  PANIC_ON_FAILURE(ssd1306_set_clock_divider(&ssd1306, 0x80));
  PANIC_ON_FAILURE(ssd1306_set_multiplex_ratio(&ssd1306, 63));
  PANIC_ON_FAILURE(ssd1306_set_display_offset(&ssd1306, 0x00));
  PANIC_ON_FAILURE(ssd1306_set_display_start_line(&ssd1306, 0x00));
  PANIC_ON_FAILURE(
      ssd1306_set_charge_pump(&ssd1306, SSD1306_SET_CHARGE_PUMP_ENABLE));
  PANIC_ON_FAILURE(
      ssd1306_set_segment_remap(&ssd1306, SSD1306_SEGMENT_REMAP_1));
  PANIC_ON_FAILURE(ssd1306_set_com_output_scan(
      &ssd1306, SSD1306_SET_COM_OUTPUT_SCAN_DECREMENT));
  PANIC_ON_FAILURE(ssd1306_set_com_pins_configuration(&ssd1306, 0x12));
  PANIC_ON_FAILURE(ssd1306_set_contrast(&ssd1306, 0xff));
  PANIC_ON_FAILURE(ssd1306_set_precharge_period(&ssd1306, 0xF1));
  PANIC_ON_FAILURE(ssd1306_set_vcom_deselect(&ssd1306, 0x40));
  PANIC_ON_FAILURE(ssd1306_display_all_on_resume(&ssd1306));
  PANIC_ON_FAILURE(ssd1306_set_invert_off(&ssd1306));
  PANIC_ON_FAILURE(ssd1306_display_on(&ssd1306));

  PANIC_ON_FAILURE(ssd1306_set_memory_addressing_mode(
      &ssd1306, SSD1306_MEMORY_ADDRESSING_MODE_HORIZONTAL));
  PANIC_ON_FAILURE(ssd1306_set_column_address(&ssd1306, 0x0, 0x7f));
  PANIC_ON_FAILURE(ssd1306_set_page_address(&ssd1306, 0x0, 0x7));

  PANIC_ON_FAILURE(ssd1306_clear(&ssd1306, 0));

  PANIC_ON_FAILURE(ssd1306_set_contrast(&ssd1306, 0));

  PANIC_ON_FAILURE(ssd1306_set_memory_addressing_mode(
      &ssd1306, SSD1306_MEMORY_ADDRESSING_MODE_PAGE));

  PANIC_ON_FAILURE(ssd1306_set_page_column_address(&ssd1306, 48));
  PANIC_ON_FAILURE(ssd1306_set_page_start_address(&ssd1306, 2));

  for (uint8_t p = 0; p < 32; ++p) {
    PANIC_ON_FAILURE(i2c_start(&ssd1306.i2c, MIDAS_ADDRESS));
    PANIC_ON_FAILURE(i2c_write(&ssd1306.i2c, 0x40));
    const uint8_t logo_item = pgm_read_byte(logo + p);
    PANIC_ON_FAILURE(i2c_write(&ssd1306.i2c, logo_item));
    i2c_stop(&ssd1306.i2c);
  }

  PANIC_ON_FAILURE(ssd1306_set_page_column_address(&ssd1306, 48));
  PANIC_ON_FAILURE(ssd1306_set_page_start_address(&ssd1306, 3));

  for (uint8_t p = 32; p < 64; ++p) {
    PANIC_ON_FAILURE(i2c_start(&ssd1306.i2c, MIDAS_ADDRESS));
    PANIC_ON_FAILURE(i2c_write(&ssd1306.i2c, 0x40));
    const uint8_t logo_item = pgm_read_byte(logo + p);
    PANIC_ON_FAILURE(i2c_write(&ssd1306.i2c, logo_item));
    i2c_stop(&ssd1306.i2c);
  }

  PANIC_ON_FAILURE(ssd1306_set_page_column_address(&ssd1306, 48));
  PANIC_ON_FAILURE(ssd1306_set_page_start_address(&ssd1306, 4));

  for (uint8_t p = 64; p < 96; ++p) {
    PANIC_ON_FAILURE(i2c_start(&ssd1306.i2c, MIDAS_ADDRESS));
    PANIC_ON_FAILURE(i2c_write(&ssd1306.i2c, 0x40));
    const uint8_t logo_item = pgm_read_byte(logo + p);
    PANIC_ON_FAILURE(i2c_write(&ssd1306.i2c, logo_item));
    i2c_stop(&ssd1306.i2c);
  }

  PANIC_ON_FAILURE(ssd1306_set_page_column_address(&ssd1306, 48));
  PANIC_ON_FAILURE(ssd1306_set_page_start_address(&ssd1306, 5));

  for (uint8_t p = 96; p < 128; ++p) {
    PANIC_ON_FAILURE(i2c_start(&ssd1306.i2c, MIDAS_ADDRESS));
    PANIC_ON_FAILURE(i2c_write(&ssd1306.i2c, 0x40));
    const uint8_t logo_item = pgm_read_byte(logo + p);
    PANIC_ON_FAILURE(i2c_write(&ssd1306.i2c, logo_item));
    i2c_stop(&ssd1306.i2c);
  }

  _delay_ms(1000);

  {
    struct framebuffer_blit_t blit;
    blit.source = rom;
    blit.source_flash = 1;
    blit.source_image_width = ROM_WIDTH;
    blit.source_image_height = ROM_HEIGHT;
    blit.source_x = 0;
    blit.source_y = 96;
    blit.target_x = 48;
    blit.target_y = 8;
    blit.blit_width = 32;
    blit.blit_height = 32;
    framebuffer_blit(&framebuffer, &blit);
  }

  for (uint8_t i = 0; i < 8; ++i) {
    struct framebuffer_blit_t blit;
    blit.source = rom;
    blit.source_flash = 1;
    blit.source_image_width = ROM_WIDTH;
    blit.source_image_height = ROM_HEIGHT;
    blit.source_x = i * 8;
    blit.source_y = 0;
    blit.target_x = 32 + (i * 8);
    blit.target_y = 48;
    blit.blit_width = 8;
    blit.blit_height = 8;
    framebuffer_blit(&framebuffer, &blit);
  }

  PANIC_ON_FAILURE(framebuffer_send(&ssd1306, &framebuffer));

  DDRB = 0b11111111;
  for (;;) {
    PORTB = 0b00000000;
    _delay_ms(16);
    PORTB = 0b11111111;
    _delay_ms(16);
  }

  return 0;
}

#endif // MAIN2_C
