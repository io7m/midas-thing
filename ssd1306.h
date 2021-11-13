#ifndef SD1306_H
#define SD1306_H

#include "i2c.h"
#include <stdint.h>

#define SSD1306_SET_CONTRAST 0x81
#define SSD1306_DISPLAY_ALL_ON_RESUME 0xA4
#define SSD1306_DISPLAY_ALL_ON 0xA5
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
#define SSD1306_SET_SEGMENT_REMAP_0 0xA0
#define SSD1306_SET_SEGMENT_REMAP_1 0xA1

#define SSD1306_SET_COLUMN_ADDRESS_LOW_4B_0 0x00
#define SSD1306_SET_COLUMN_ADDRESS_HIGH_4B_0 0x10
#define SSD1306_SET_PAGE_START_ADDRESS_0 0xB0
#define SSD1306_SET_MEMORY_ADDRESSING_MODE 0x20

typedef enum {
  SSD1306_MEMORY_ADDRESSING_MODE_PAGE = 0b00000010,
  SSD1306_MEMORY_ADDRESSING_MODE_HORIZONTAL = 0b00000000,
  SSD1306_MEMORY_ADDRESSING_MODE_VERTICAL = 0b00000001
} ssd1306_memory_addressing_mode_t;

#define SSD1306_SET_CHARGE_PUMP 0x8D

typedef enum {
  SSD1306_SET_CHARGE_PUMP_ENABLE = 0x14,
  SSD1306_SET_CHARGE_PUMP_DISABLE = 0x10
} ssd1306_charge_pump_t;

#define SSD1306_EXTERNALVCC 0x1
#define SSD1306_SWITCHCAPVCC 0x2

typedef enum {
  SSD1306_SEGMENT_REMAP_0 = 0xA0,
  SSD1306_SEGMENT_REMAP_1 = 0xA1
} ssd1306_segment_remap_t;

typedef enum {
  SSD1306_SET_COM_OUTPUT_SCAN_INCREMENT = 0xC0,
  SSD1306_SET_COM_OUTPUT_SCAN_DECREMENT = 0xC8
} ssd1306_com_output_scan_direction_t;

#define SD1306_RIGHT_HORIZONTAL_SCROLL 0x26
#define SD1306_LEFT_HORIZONTAL_SCROLL 0x27
#define SD1306_DEACTIVATE_SCROLL 0x2e
#define SD1306_ACTIVATE_SCROLL 0x2f

struct ssd1306_t {
  struct i2c_t i2c;
  uint8_t address;
};

void ssd1306_init(struct ssd1306_t *const sd, uint8_t address);

uint8_t ssd1306_clear(struct ssd1306_t *const sd, uint8_t value);

uint8_t ssd1306_send_command(struct ssd1306_t *const sd, uint8_t command);

uint8_t ssd1306_display_off(struct ssd1306_t *const sd);

uint8_t ssd1306_display_on(struct ssd1306_t *const sd);

uint8_t ssd1306_display_all_on(struct ssd1306_t *const sd);

uint8_t ssd1306_display_all_on_resume(struct ssd1306_t *const sd);

uint8_t ssd1306_set_clock_divider(struct ssd1306_t *const sd, uint8_t divider);

uint8_t ssd1306_set_multiplex_ratio(struct ssd1306_t *const sd, uint8_t ratio);

uint8_t ssd1306_set_display_offset(struct ssd1306_t *const sd, uint8_t offset);

uint8_t ssd1306_set_display_start_line(struct ssd1306_t *const sd,
                                       uint8_t line);

uint8_t ssd1306_set_charge_pump(struct ssd1306_t *const sd,
                                ssd1306_charge_pump_t charge_pump);

uint8_t ssd1306_set_segment_remap(struct ssd1306_t *const sd,
                                  ssd1306_segment_remap_t segment);

uint8_t ssd1306_set_vcom_deselect(struct ssd1306_t *const sd, uint8_t deselect);

uint8_t
ssd1306_set_com_output_scan(struct ssd1306_t *const sd,
                            ssd1306_com_output_scan_direction_t direction);

uint8_t ssd1306_set_com_pins_configuration(struct ssd1306_t *const sd,
                                           uint8_t configuration);

uint8_t ssd1306_set_contrast(struct ssd1306_t *const sd, uint8_t contrast);

uint8_t ssd1306_set_precharge_period(struct ssd1306_t *const sd,
                                     uint8_t period);

uint8_t ssd1306_set_invert_on(struct ssd1306_t *const sd);

uint8_t ssd1306_set_invert_off(struct ssd1306_t *const sd);

uint8_t
ssd1306_set_memory_addressing_mode(struct ssd1306_t *const sd,
                                   ssd1306_memory_addressing_mode_t mode);

uint8_t ssd1306_set_column_address(struct ssd1306_t *const sd, uint8_t start,
                                   uint8_t end);

uint8_t ssd1306_set_page_address(struct ssd1306_t *const sd, uint8_t start,
                                 uint8_t end);

uint8_t ssd1306_set_page_start_address(struct ssd1306_t *const sd,
                                       uint8_t address);
uint8_t ssd1306_set_page_column_address(struct ssd1306_t *const sd,
                                        uint8_t address);

typedef enum {
  SSD1306_HORIZONTAL_SCROLL_RIGHT = 0x26,
  SSD1306_HORIZONTAL_SCROLL_LEFT = 0x27
} ssd1306_horizontal_scroll_t;

typedef enum {
  SSD1306_SCROLL_RATE_5 = 0b000,
  SSD1306_SCROLL_RATE_3 = 0b100,
  SSD1306_SCROLL_RATE_64 = 0b001,
  SSD1306_SCROLL_RATE_4 = 0b101,
  SSD1306_SCROLL_RATE_128 = 0b010,
  SSD1306_SCROLL_RATE_25 = 0b110,
  SSD1306_SCROLL_RATE_256 = 0b011,
  SSD1306_SCROLL_RATE_2 = 0b111
} ssd1306_scroll_rate_t;

uint8_t ssd1306_horizontal_scroll(struct ssd1306_t *const sd,
                                  ssd1306_horizontal_scroll_t direction,
                                  uint8_t page_start,
                                  ssd1306_scroll_rate_t scroll_rate,
                                  uint8_t page_end);

uint8_t ssd1306_data_start(struct ssd1306_t *const sd);
uint8_t ssd1306_data_write(struct ssd1306_t *const sd, uint8_t data);
uint8_t ssd1306_data_finish(struct ssd1306_t *const sd);

#endif // SD1306_H
