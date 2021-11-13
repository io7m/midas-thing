#ifndef PROGRAM_RAIN_C
#define PROGRAM_RAIN_C

#include "program_rain.h"
#include "program.h"
#include "rom.h"

struct raindrop_t {
  uint8_t x;
  uint8_t y;
  uint8_t speed;
};

typedef enum {
  RAIN_THUNDER_IDLE,
  RAIN_THUNDER_FLASH1,
  RAIN_THUNDER_PAUSE1,
  RAIN_THUNDER_FLASH2
} rain_thunder_state_t;

#define RAIN_DROP_COUNT 8
#define RAIN_SPEED_MINIMUM 7
#define RAIN_SPEED_MAXIMUM 10

static struct raindrop_t rain_drops[RAIN_DROP_COUNT];
static uint8_t rain_title_time;
static rain_thunder_state_t rain_thunder;
static uint8_t rain_thunder_x;

static void program_rain_init_drop(struct raindrop_t *const r) {
  r->x = rom_random_8();
  r->y = 0;
  r->speed = RAIN_SPEED_MINIMUM + (rom_random_8() & RAIN_SPEED_MAXIMUM);
}

static void program_rain_init(struct ssd1306_t *const display,
                              struct framebuffer_t *const framebuffer) {
  ssd1306_set_invert_off(display);

  rain_thunder = RAIN_THUNDER_IDLE;
  rain_title_time = 30;
  for (uint8_t i = 0; i < RAIN_DROP_COUNT; ++i) {
    struct raindrop_t *const r = &rain_drops[i];
    program_rain_init_drop(r);
    r->y = rom_random_8() & (FRAMEBUFFER_HEIGHT - 1);
  }
}

static void
program_rain_render_thunder(struct ssd1306_t *const display,
                            struct framebuffer_t *const framebuffer) {

  struct framebuffer_blit_t rain_thunder_blit;
  rain_thunder_blit.blit_width = 16;
  rain_thunder_blit.blit_height = 32;
  rain_thunder_blit.source = rom;
  rain_thunder_blit.source_flash = 1;
  rain_thunder_blit.source_image_width = ROM_WIDTH;
  rain_thunder_blit.source_image_height = ROM_HEIGHT;
  rain_thunder_blit.source_x = 32;
  rain_thunder_blit.source_y = 96;
  rain_thunder_blit.target_x = rain_thunder_x;
  rain_thunder_blit.target_y = 16;

  switch (rain_thunder) {
  case RAIN_THUNDER_IDLE: {
    if (rom_random_8() < 3) {
      rain_thunder_x = rom_random_8() & (FRAMEBUFFER_WIDTH - 1);
      rain_thunder_blit.target_x = rain_thunder_x;
      rain_thunder = RAIN_THUNDER_FLASH1;
      ssd1306_set_invert_on(display);
      framebuffer_blit(framebuffer, &rain_thunder_blit);
    }
    break;
  }
  case RAIN_THUNDER_FLASH1: {
    rain_thunder = RAIN_THUNDER_PAUSE1;
    ssd1306_set_invert_off(display);
    framebuffer_blit(framebuffer, &rain_thunder_blit);
    break;
  }
  case RAIN_THUNDER_PAUSE1: {
    rain_thunder = RAIN_THUNDER_FLASH2;
    ssd1306_set_invert_on(display);
    framebuffer_blit(framebuffer, &rain_thunder_blit);
    break;
  }
  case RAIN_THUNDER_FLASH2: {
    rain_thunder = RAIN_THUNDER_IDLE;
    ssd1306_set_invert_off(display);
    break;
  }
  }
}

#define RAIN_HORIZON_Y_HEIGHT (FRAMEBUFFER_HEIGHT / 4)
#define RAIN_HORIZON_Y (FRAMEBUFFER_HEIGHT - RAIN_HORIZON_Y_HEIGHT)

static void program_rain_render_title(struct framebuffer_t *const framebuffer) {
  if (rain_title_time > 0) {
    framebuffer_render_text_P(framebuffer, PSTR("HEAVY RAIN"), 24, 28);
    --rain_title_time;
  }
}

static void
program_rain_render_background(struct framebuffer_t *const framebuffer) {
  for (uint8_t x = 0; x < FRAMEBUFFER_WIDTH; ++x) {
    framebuffer_set(framebuffer, x, RAIN_HORIZON_Y, 1);
  }

  for (uint8_t q = 0; q < RAIN_DROP_COUNT; ++q) {
    const uint8_t x = rom_random_8();
    const uint8_t y =
        (rom_random_8() & (RAIN_HORIZON_Y_HEIGHT - 1)) + RAIN_HORIZON_Y;
    framebuffer_set(framebuffer, x, y, 1);
  }
}

static void program_rain_render_drops(struct framebuffer_t *const framebuffer) {
  for (uint8_t i = 0; i < RAIN_DROP_COUNT; ++i) {
    const struct raindrop_t *const r = &rain_drops[i];
    const uint8_t y0 = r->y;
    const uint8_t y1 = y0 + (r->speed >> 1);
    framebuffer_render_vline(framebuffer, r->x, y0, y1, 1);
  }
}

static void program_rain_update_drops() {
  for (uint8_t i = 0; i < RAIN_DROP_COUNT; ++i) {
    struct raindrop_t *const r = &rain_drops[i];
    r->y += r->speed;
    if (r->y >= FRAMEBUFFER_HEIGHT) {
      program_rain_init_drop(r);
    }
  }
}

static void program_rain_run(struct ssd1306_t *const display,
                             struct framebuffer_t *const framebuffer) {
  framebuffer_init(framebuffer);

  program_rain_update_drops();

  program_rain_render_thunder(display, framebuffer);
  program_rain_render_title(framebuffer);
  program_rain_render_background(framebuffer);
  program_rain_render_drops(framebuffer);

  framebuffer_send(display, framebuffer);
}

const struct program_t program_rain = {
    .init = &program_rain_init,
    .run = &program_rain_run,
};

#endif // PROGRAM_RAIN_C
