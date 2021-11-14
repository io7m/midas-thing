#ifndef MAIN2_C
#define MAIN2_C

#include <avr/interrupt.h>
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <util/delay.h>
#include <util/twi.h>

#include <stdint.h>

#include "buttons.h"
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
static struct buttons_t buttons;

static struct program_context_t program_context = {
    .buttons = &buttons, .display = &ssd1306, .framebuffer = &framebuffer};

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

/*
 * Initialize the display.
 */

static void main_init_display(void) {

  /*
   * Configure PORTC as an input port.
   * Enable pull-up resistors on the i2c bus pins.
   */

  DDRC = 0b00000000;
  PORTC = 0b00110000;

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
  PANIC_ON_FAILURE(ssd1306_set_precharge_period(&ssd1306, 0x22));
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
}

/*
 * Display the title.
 */

static void main_title(void) {
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

  framebuffer_render_text_P(&framebuffer, PSTR("IO7M"), 48, 44);
  PANIC_ON_FAILURE(framebuffer_send(&ssd1306, &framebuffer));

  _delay_ms(1000);
  transition_vbars(&ssd1306, &framebuffer);

  framebuffer_init(&framebuffer);
  PANIC_ON_FAILURE(framebuffer_send(&ssd1306, &framebuffer));
}

/*
 * Configure the button inputs and interrupts.
 */

static void main_init_buttons(void) {
  /*
   * Set the four button pins as inputs, and enable pull-up
   * resistors on the button pins.
   */

  DDRC &= ~(0b00001111);
  PORTC |= 0b00001111;

  /*
   * Enable interrupts for PORTC.
   */

  PCICR = (1 << PCIE1);
  PCMSK1 = 0;
  PCMSK1 |= (1 << PCINT8);
  PCMSK1 |= (1 << PCINT9);
  PCMSK1 |= (1 << PCINT10);
  PCMSK1 |= (1 << PCINT11);
  sei();
}

static void main_read_buttons(void) {
  const uint8_t pins_now = ~(PINC & 0b1111);
  const uint8_t buttons_then = buttons.buttons;

  if ((pins_now & BUTTON_0) == BUTTON_0) {
    buttons.buttons |= BUTTON_0;
  } else {
    buttons.buttons &= ~BUTTON_0;
  }

  if ((pins_now & BUTTON_1) == BUTTON_1) {
    buttons.buttons |= BUTTON_1;
  } else {
    buttons.buttons &= ~BUTTON_1;
  }

  if ((pins_now & BUTTON_2) == BUTTON_2) {
    buttons.buttons |= BUTTON_2;
  } else {
    buttons.buttons &= ~BUTTON_2;
  }

  if ((pins_now & BUTTON_3) == BUTTON_3) {
    buttons.buttons |= BUTTON_3;
  } else {
    buttons.buttons &= ~BUTTON_3;
  }

  button_set_changed(&buttons, buttons.buttons != buttons_then);
}

/*
 * The interrupt vector for buttons.
 */

ISR(PCINT1_vect) { rom_random_8(); }

int main(void) {
  uart_init();

  main_init_display();
  main_title();
  main_init_buttons();

  uint8_t program_index = 0;
  const struct program_t *program = programs[program_index];
  program->init(&program_context);

  for (;;) {
    main_read_buttons();
    program->run(&program_context);
    button_set_changed(&buttons, 0);
    PANIC_ON_FAILURE(framebuffer_send(&ssd1306, &framebuffer));
    _delay_ms(16);
  }

  return 0;
}

#endif // MAIN2_C
