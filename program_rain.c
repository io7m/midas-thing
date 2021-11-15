#ifndef PROGRAM_RAIN_C
#define PROGRAM_RAIN_C

#include <stdlib.h>

#include "program.h"
#include "program_rain.h"
#include "rom.h"

struct raindrop_t {
  uint8_t x;
  uint8_t y;
  uint8_t speed;
};

typedef enum {
  RAIN_THUNDER_IDLE,
  RAIN_THUNDER_START,
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
  r->x = random();
  r->y = 0;
  r->speed = RAIN_SPEED_MINIMUM + (random() & RAIN_SPEED_MAXIMUM);
}

static void program_rain_init(struct program_context_t *context) {
  struct ssd1306_t *const display = context->display;

  ssd1306_set_invert_off(display);

  rain_thunder = RAIN_THUNDER_IDLE;
  rain_title_time = 30;
  for (uint8_t i = 0; i < RAIN_DROP_COUNT; ++i) {
    struct raindrop_t *const r = &rain_drops[i];
    program_rain_init_drop(r);
    r->y = random() & (FRAMEBUFFER_HEIGHT - 1);
  }
}

static void
program_rain_render_thunder(struct ssd1306_t *const display,
                            struct framebuffer_t *const framebuffer) {

  framebuffer_rom_blit_data.blit_width = 16;
  framebuffer_rom_blit_data.blit_height = 32;
  framebuffer_rom_blit_data.source_x = 32;
  framebuffer_rom_blit_data.source_y = 96;
  framebuffer_rom_blit_data.target_x = rain_thunder_x;
  framebuffer_rom_blit_data.target_y = 16;

  switch (rain_thunder) {
  case RAIN_THUNDER_IDLE: {
    if (random() < 3) {
      rain_thunder = RAIN_THUNDER_START;
    }
    break;
  }
  case RAIN_THUNDER_START: {
    rain_thunder_x = random() & (FRAMEBUFFER_WIDTH - 1);
    framebuffer_rom_blit_data.target_x = rain_thunder_x;
    rain_thunder = RAIN_THUNDER_FLASH1;
    ssd1306_set_invert_on(display);
    framebuffer_blit(framebuffer, &framebuffer_rom_blit_data);
    break;
  }
  case RAIN_THUNDER_FLASH1: {
    rain_thunder = RAIN_THUNDER_PAUSE1;
    ssd1306_set_invert_off(display);
    framebuffer_blit(framebuffer, &framebuffer_rom_blit_data);
    break;
  }
  case RAIN_THUNDER_PAUSE1: {
    rain_thunder = RAIN_THUNDER_FLASH2;
    ssd1306_set_invert_on(display);
    framebuffer_blit(framebuffer, &framebuffer_rom_blit_data);
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
    const uint8_t x = random();
    const uint8_t y = (random() & (RAIN_HORIZON_Y_HEIGHT - 1)) + RAIN_HORIZON_Y;
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

static program_sleep_t program_rain_run(struct program_context_t *context) {
  struct ssd1306_t *const display = context->display;
  struct framebuffer_t *const framebuffer = context->framebuffer;

  framebuffer_init(framebuffer);

  if (buttons_changed(context->buttons) && button_0_set(context->buttons)) {
    rain_thunder = RAIN_THUNDER_START;
  }

  program_rain_update_drops();
  program_rain_render_thunder(display, framebuffer);
  program_rain_render_title(framebuffer);
  program_rain_render_background(framebuffer);
  program_rain_render_drops(framebuffer);
  return PROGRAM_NO_SLEEP;
}

static PGM_P program_rain_name(void) { return PSTR("rain"); }

const struct program_t program_rain = {
    .name = &program_rain_name,
    .init = &program_rain_init,
    .run = &program_rain_run,
};

#endif // PROGRAM_RAIN_C
