#ifndef PROGRAM_3CARD_C
#define PROGRAM_3CARD_C

#include "program_3card.h"
#include "program.h"
#include "rom.h"
#include "transitions.h"

#include <stdint.h>

typedef enum {
  CARD_WAITING,
  CARD_SHUFFLING,
  CARD_SELECTION,
  CARD_REVEAL
} card_state_t;

struct card_t {
  uint8_t x;
  uint8_t y;
  uint8_t z;
  uint8_t flags;
};

typedef enum { CARD_HIDDEN = 0b00000001, CARD_LADY = 0b00000010 } card_flag_t;

static uint8_t card_selection;
static card_state_t card_state = CARD_WAITING;
static struct card_t cards[3];

#define CARD_START_0_X 32
#define CARD_START_1_X (CARD_START_0_X + 16 + 8)
#define CARD_START_2_X (CARD_START_1_X + 16 + 8)

static void program_3card_init(struct program_context_t *context) {
  struct ssd1306_t *const display = context->display;
  ssd1306_set_invert_off(display);

  card_selection = 0;
  card_state = CARD_WAITING;

  cards[0].x = CARD_START_0_X;
  cards[0].y = 16;
  cards[0].z = 2;
  cards[0].flags = CARD_LADY;

  cards[1].x = CARD_START_1_X;
  cards[1].y = 16;
  cards[1].z = 1;
  cards[1].flags = 0;

  cards[2].x = CARD_START_2_X;
  cards[2].y = 16;
  cards[2].z = 0;
  cards[2].flags = 0;
}

static void program_3card_render_cards(struct program_context_t *context) {
  struct framebuffer_t *const framebuffer = context->framebuffer;

  framebuffer_rom_blit_data.source_image_height = ROM_HEIGHT;
  framebuffer_rom_blit_data.source_image_width = ROM_WIDTH;

  /*
   * Render the cards in Z order. No attempt is made at efficiency, we just
   * traverse the list of cards three times in order to render them in
   * the right order.
   */

  for (uint8_t z = 0; z < 3; ++z) {
    for (uint8_t index = 0; index < 3; ++index) {
      const struct card_t *const card = &cards[index];
      if (card->z != z) {
        continue;
      }

      framebuffer_rom_blit_data.blit_width = 16;
      framebuffer_rom_blit_data.blit_height = 24;
      framebuffer_rom_blit_data.source_x = 80;
      framebuffer_rom_blit_data.source_y = 104;

      framebuffer_rom_blit_data.target_x = card->x;
      framebuffer_rom_blit_data.target_y = card->y;
      framebuffer_blit(framebuffer, &framebuffer_rom_blit_data);

      /*
       * If the card is hidden, don't render an icon.
       */

      if ((card->flags & CARD_HIDDEN) == CARD_HIDDEN) {
        continue;
      }

      /*
       * If the card is the lady, render a happy face.
       */

      if ((card->flags & CARD_LADY) == CARD_LADY) {
        framebuffer_rom_blit_data.blit_width = 8;
        framebuffer_rom_blit_data.blit_height = 8;
        framebuffer_rom_blit_data.source_x = 96;
        framebuffer_rom_blit_data.source_y = 104;
        framebuffer_rom_blit_data.target_x = card->x + 4;
        framebuffer_rom_blit_data.target_y = card->y + 8;
        framebuffer_blit(framebuffer, &framebuffer_rom_blit_data);
      }

      /*
       * If the card isn't the lady, render an X.
       */

      if ((card->flags & CARD_LADY) == 0) {
        framebuffer_rom_blit_data.blit_width = 8;
        framebuffer_rom_blit_data.blit_height = 8;
        framebuffer_rom_blit_data.source_x = 96;
        framebuffer_rom_blit_data.source_y = 112;
        framebuffer_rom_blit_data.target_x = card->x + 4;
        framebuffer_rom_blit_data.target_y = card->y + 8;
        framebuffer_blit(framebuffer, &framebuffer_rom_blit_data);
      }
    }
  }
}

static program_sleep_t program_3card_run(struct program_context_t *context) {
  struct framebuffer_t *const framebuffer = context->framebuffer;
  framebuffer_init(framebuffer);

  switch (card_state) {
  case CARD_WAITING: {
    framebuffer_render_text_P(framebuffer, PSTR("W"), 0, 0);

    /*
     * Show the cards.
     */

    for (uint8_t index = 0; index < 3; ++index) {
      struct card_t *const card = &cards[index];
      card->flags &= ~CARD_HIDDEN;
    }

    /*
     * If the button is pressed, shuffling begins and all cards are hidden.
     */

    if (buttons_changed(context->buttons) && button_1_set(context->buttons)) {
      card_state = CARD_SHUFFLING;
      for (uint8_t index = 0; index < 3; ++index) {
        struct card_t *const card = &cards[index];
        card->flags |= CARD_HIDDEN;
      }
      return PROGRAM_NO_SLEEP;
    }

    /*
     * Render the cards.
     */

    program_3card_render_cards(context);
    framebuffer_render_text_P(framebuffer, PSTR("B TO GO!"), CARD_START_0_X,
                              48);
    return PROGRAM_SLEEP;
  }

  case CARD_SHUFFLING: {
    framebuffer_render_text_P(framebuffer, PSTR("S"), 0, 0);

    program_3card_render_cards(context);
    card_state = CARD_SELECTION;
    return PROGRAM_NO_SLEEP;
  }

  case CARD_SELECTION: {
    framebuffer_render_text_P(framebuffer, PSTR("X"), 0, 0);

    program_3card_render_cards(context);

    if (buttons_changed(context->buttons)) {
      if (button_0_set(context->buttons)) {
        if (card_selection == 0) {
          card_selection = 2;
        } else {
          card_selection = card_selection - 1;
        }
      } else if (button_2_set(context->buttons)) {
        if (card_selection == 2) {
          card_selection = 0;
        } else {
          card_selection = card_selection + 1;
        }
      } else if (button_1_set(context->buttons)) {
        card_state = CARD_REVEAL;
        return PROGRAM_NO_SLEEP;
      }
    }

    switch (card_selection) {
    case 0: {
      framebuffer_render_text_P(framebuffer, PSTR("^"), CARD_START_0_X + 4, 52);
      break;
    }
    case 1: {
      framebuffer_render_text_P(framebuffer, PSTR("^"), CARD_START_1_X + 4, 52);
      break;
    }
    case 2: {
      framebuffer_render_text_P(framebuffer, PSTR("^"), CARD_START_2_X + 4, 52);
      break;
    }
    }

    return PROGRAM_SLEEP;
  }
  case CARD_REVEAL: {
    framebuffer_render_text_P(framebuffer, PSTR("R"), 0, 0);

    if (buttons_changed(context->buttons)) {
      if (button_1_set(context->buttons)) {
        card_state = CARD_WAITING;
        return PROGRAM_NO_SLEEP;
      }
    }

    /*
     * Show the cards.
     */

    for (uint8_t index = 0; index < 3; ++index) {
      struct card_t *const card = &cards[index];
      card->flags &= ~CARD_HIDDEN;
    }

    program_3card_render_cards(context);
    return PROGRAM_SLEEP;
  }
  }

  return PROGRAM_SLEEP;
}

static PGM_P program_3card_name(void) { return PSTR("3card"); }

const struct program_t program_3card = {
    .name = &program_3card_name,
    .init = &program_3card_init,
    .run = &program_3card_run,
};

#endif // PROGRAM_3CARD_C
