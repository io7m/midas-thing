#ifndef PROGRAM_3CARD_C
#define PROGRAM_3CARD_C

#include "program_3card.h"
#include "program.h"
#include "rom.h"
#include "transitions.h"

#include <stdint.h>
#include <stdlib.h>

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
  uint8_t move_source_x;
  uint8_t move_target_x;
  uint8_t move_saved_y;
  uint8_t move_transition_y;
  uint8_t flags;
};

typedef enum { CARD_HIDDEN = 0b00000001, CARD_LADY = 0b00000010 } card_flag_t;

static uint8_t card_shuffle_timer;
static uint8_t card_shuffle_repeats;
static uint8_t card_shuffle_fade;
static card_state_t card_state = CARD_WAITING;
static struct card_t cards[3];
static struct card_t *cards_shuffled[3];
static struct card_t *card_selection;
static const char card_cursor[] PROGMEM = "^";
static const char card_greeting[] PROGMEM = "B TO GO!";
static const char card_win[] PROGMEM = "YOU WIN";
static const char card_lose[] PROGMEM = "YOU LOSE";

#define CARD_SHUFFLE_REPEATS 10
#define CARD_SHUFFLE_TIME 6
#define CARD_SHUFFLE_FADE 4
#define CARD_START_0_X 32
#define CARD_START_1_X (CARD_START_0_X + 16 + 8)
#define CARD_START_2_X (CARD_START_1_X + 16 + 8)
#define CARD_START_Y 16

static void program_3card_init(struct program_context_t *context) {
  struct ssd1306_t *const display = context->display;
  ssd1306_set_invert_off(display);

  card_selection = &cards[0];
  card_state = CARD_WAITING;

  cards[0].x = CARD_START_0_X;
  cards[0].y = CARD_START_Y;
  cards[0].z = 2;
  cards[0].flags = CARD_LADY;
  cards_shuffled[0] = &cards[0];

  cards[1].x = CARD_START_1_X;
  cards[1].y = CARD_START_Y;
  cards[1].z = 1;
  cards[1].flags = 0;
  cards_shuffled[1] = &cards[1];

  cards[2].x = CARD_START_2_X;
  cards[2].y = CARD_START_Y;
  cards[2].z = 0;
  cards[2].flags = 0;
  cards_shuffled[2] = &cards[2];
}

static void program_3card_render_cards(struct program_context_t *context) {
  struct framebuffer_t *const framebuffer = context->framebuffer;

  /*
   * Render the cards in Z order. No attempt is made at efficiency, we just
   * traverse the list of cards three times in order to render them in
   * the right order.
   */

  for (uint8_t z = 0; z < 3; ++z) {
    for (uint8_t index = 0; index < 3; ++index) {
      const struct card_t *const card = cards_shuffled[index];
      if (card->z != z) {
        continue;
      }

      /*
       * Blit a blank card.
       */

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

static void program_3card_shuffle_array(void) {
  for (uint8_t i = 0; i < 3; ++i) {
    const uint8_t j = (i + random()) % 3;
    struct card_t *const card = cards_shuffled[j];
    cards_shuffled[j] = cards_shuffled[i];
    cards_shuffled[i] = card;
  }

  for (uint8_t i = 0; i < 3; ++i) {
    struct card_t *const card_target = &cards[i];
    struct card_t *const card_source = cards_shuffled[i];
    card_target->move_target_x = card_source->x;
    card_target->move_source_x = card_target->x;
    card_target->move_saved_y = card_target->y;
    card_target->z = card_source->z;

    switch (random() % 3) {
    case 0:
      card_target->move_transition_y = card_target->y;
      break;
    case 1:
      card_target->move_transition_y = card_target->y - 2;
      break;
    case 2:
      card_target->move_transition_y = card_target->y + 2;
      break;
    }
  }
}

/*
 * Find the previous card. This is the card with the smallest positive x
 * delta compared to the currently selected card.
 */

static void program_3card_select_next(void) {
  int8_t delta_x = 0x7f;

  struct card_t *card_new_selection = 0;
  for (uint8_t i = 0; i < 3; ++i) {
    struct card_t *const card_candidate = &cards[i];

    if (card_candidate->x > card_selection->x) {
      const int8_t new_delta_x = abs(card_candidate->x - card_selection->x);
      if (new_delta_x < delta_x) {
        delta_x = new_delta_x;
        card_new_selection = card_candidate;
      }
    }
  }

  if (card_new_selection) {
    card_selection = card_new_selection;
  }
}

/*
 * Find the previous card. This is the card with the smallest negative x
 * delta compared to the currently selected card.
 */

static void program_3card_select_previous(void) {
  int8_t delta_x = 0x7f;

  struct card_t *card_new_selection = 0;
  for (uint8_t i = 0; i < 3; ++i) {
    struct card_t *const card_candidate = &cards[i];

    if (card_candidate->x < card_selection->x) {
      const int8_t new_delta_x = abs(card_candidate->x - card_selection->x);
      if (new_delta_x < delta_x) {
        delta_x = new_delta_x;
        card_new_selection = card_candidate;
      }
    }
  }

  if (card_new_selection) {
    card_selection = card_new_selection;
  }
}

/*
 * Find the card with the smallest x.
 */

static void program_3card_select_leftmost(void) {
  for (uint8_t i = 0; i < 3; ++i) {
    struct card_t *const card_candidate = &cards[i];
    if (card_candidate->x < card_selection->x) {
      card_selection = card_candidate;
    }
  }
}

static program_sleep_t program_3card_run(struct program_context_t *context) {
  struct framebuffer_t *const framebuffer = context->framebuffer;
  framebuffer_init(framebuffer);

  switch (card_state) {
  case CARD_WAITING: {

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
      card_shuffle_timer = CARD_SHUFFLE_TIME;
      card_shuffle_repeats = CARD_SHUFFLE_REPEATS;
      card_shuffle_fade = CARD_SHUFFLE_FADE;

      program_3card_shuffle_array();
      return PROGRAM_NO_SLEEP;
    }

    /*
     * Render the cards.
     */

    program_3card_render_cards(context);
    framebuffer_render_text_P(framebuffer, card_greeting, CARD_START_0_X, 48);
    return PROGRAM_SLEEP;
  }

  case CARD_SHUFFLING: {
    --card_shuffle_timer;
    --card_shuffle_fade;

    /*
     * Keep the card faces visible briefly when shuffling starts.
     */

    if (card_shuffle_fade > 0) {
      --card_shuffle_fade;
      if (card_shuffle_fade == 0) {
        for (uint8_t index = 0; index < 3; ++index) {
          struct card_t *const card = &cards[index];
          card->flags |= CARD_HIDDEN;
        }
      }
    }

    for (uint8_t i = 0; i < 3; ++i) {
      struct card_t *const card = &cards[i];
      const int8_t delta_x =
          (card->move_target_x - card->move_source_x) / CARD_SHUFFLE_TIME;

      card->y = card->move_transition_y;
      card->x += delta_x;
    }

    if (card_shuffle_timer == 0) {
      for (uint8_t i = 0; i < 3; ++i) {
        struct card_t *const card = &cards[i];
        card->x = card->move_target_x;
        card->y = card->move_saved_y;
      }

      card_shuffle_timer = CARD_SHUFFLE_TIME;
      program_3card_shuffle_array();
      --card_shuffle_repeats;

      if (card_shuffle_repeats == 0) {
        card_state = CARD_SELECTION;
        program_3card_select_leftmost();
      }
    }

    program_3card_render_cards(context);
    return PROGRAM_NO_SLEEP;
  }

  case CARD_SELECTION: {
    program_3card_render_cards(context);

    if (buttons_changed(context->buttons)) {
      if (button_0_set(context->buttons)) {
        program_3card_select_previous();
      } else if (button_2_set(context->buttons)) {
        program_3card_select_next();
      } else if (button_1_set(context->buttons)) {
        card_state = CARD_REVEAL;
        return PROGRAM_NO_SLEEP;
      }
    }

    framebuffer_render_text_P(framebuffer, card_cursor, card_selection->x + 4,
                              52);
    return PROGRAM_SLEEP;
  }
  case CARD_REVEAL: {
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

    /*
     * Was the chosen card the lady?
     */

    if ((card_selection->flags & CARD_LADY) == CARD_LADY) {
      framebuffer_render_text_P(framebuffer, card_win, CARD_START_0_X, 48);
    } else {
      framebuffer_render_text_P(framebuffer, card_lose, CARD_START_0_X, 48);
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
