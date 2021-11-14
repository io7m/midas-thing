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
#include "program_rain.h"
#include "program_stats.h"
#include "rom.h"
#include "ssd1306.h"
#include "transitions.h"
#include "uart.h"

#define MIDAS_ADDRESS 0x3C

static struct ssd1306_t ssd1306;
static struct framebuffer_t framebuffer;

static const struct program_t *const programs[] = {&program_rain,
                                                   &program_stats};
static const uint8_t program_count =
    sizeof(programs) / sizeof(struct program_t *);

#ifdef PANIC_DEBUG
static void panic_if(uint8_t i, const char *message) {
  if (i == 0) {
    char format_buffer[FORMAT_U16_SIZE_BASE2];
    uart_putchar('E');
    uart_putchar(' ');
    uart_puts_P(message);
    uart_putchar(' ');
    buffer[formatU8X(format_buffer, ssd1306.i2c.status)] = 0;
    uart_puts(format_buffer);
    uart_putchar('\n');

    for (;;) {

    }
  }
}

#define PANIC_STRINGIFY(x) #x
#define PANIC_TOSTRING(x) PANIC_STRINGIFY(x)
#define PANIC_ON_FAILURE(e) (panic_if((e), PSTR(PANIC_TOSTRING(__LINE__))))
#else
#define PANIC_ON_FAILURE(e) (e)
#endif

int main(void) {
  uart_init();

  /*
   * Enable pull-up resistors on port D (the pins attached to the i2c bus).
   */

  DDRD = 0b00000000;
  PORTD = 0b11111111;

  /*
   * Configure some pins as button inputs. Configure the internal pull-up
   * resistors on the button inputs.
   */

  DDRB &= ~(0b00000111);
  PORTB |= (0b00000111);
  DDRD &= ~(0b10000000);
  PORTD |= (0b10000000);

  ssd1306_init(&ssd1306, MIDAS_ADDRESS);
  framebuffer_init(&framebuffer);

  PANIC_ON_FAILURE(ssd1306_display_off(&ssd1306));
  PANIC_ON_FAILURE(ssd1306_set_clock_divider(&ssd1306, 0b00000000));
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

  PANIC_ON_FAILURE(framebuffer_send(&ssd1306, &framebuffer));

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

  framebuffer_render_text_P(&framebuffer, PSTR("IO7M"), 48, 44);
  PANIC_ON_FAILURE(framebuffer_send(&ssd1306, &framebuffer));

  _delay_ms(1000);
  transition_vbars(&ssd1306, &framebuffer);

  framebuffer_init(&framebuffer);
  PANIC_ON_FAILURE(framebuffer_send(&ssd1306, &framebuffer));

  uint8_t program_index = 0;
  const struct program_t *program = programs[program_index];
  program->init(&ssd1306, &framebuffer);

  uint16_t time = 60;
  for (;;) {
    program->run(&ssd1306, &framebuffer);

    if (time == 0) {
      time = 60;
      program_index = (program_index + 1) % program_count;
      program = programs[program_index];
      transition_vbars(&ssd1306, &framebuffer);
      program->init(&ssd1306, &framebuffer);
    }
    --time;
    _delay_ms(16);
  }

  return 0;
}

#endif // MAIN2_C
