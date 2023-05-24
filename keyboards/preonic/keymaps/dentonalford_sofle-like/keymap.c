/* Copyright 2015-2021 Jack Humbert
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include QMK_KEYBOARD_H

// Just making some shorter names to work with
#define VOL_UP KC_KB_VOLUME_UP
#define VOL_DOWN KC_KB_VOLUME_DOWN

enum preonic_layers {
    _BASE = 0,
    _SYMBOL,
    _NUMBER,
    _NAVIGATION,
};

typedef struct {
  bool is_press_action;
  int state;
} td_tap_t;

typedef enum {
  TD_NONE,
  TD_UNKNOWN,
  TD_SINGLE_TAP,
  TD_SINGLE_HOLD
} td_state_t;

enum {
  TD_HOME_LAYER = 0
};

td_state_t cur_dance(qk_tap_dance_state_t *state);

void ql_finished(qk_tap_dance_state_t *state, void *user_data);
void ql_reset(qk_tap_dance_state_t *state, void *user_data);

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[_BASE] = LAYOUT_preonic_grid(
//| --------- | --------- | --------- | --------- | --------- | --------- ||| --------- | --------- | --------- | --------- | --------- | --------- |
    KC_GRAVE,   KC_1,       KC_2,       KC_3,       KC_4,       KC_5,         KC_6,       KC_7,       KC_8,       KC_9,       KC_0,       KC_MINUS,
//| --------- | --------- | --------- | --------- | --------- | --------- ||| --------- | --------- | --------- | --------- | --------- | --------- |
    KC_ESC,     KC_Q,       KC_W,       KC_E,       KC_R,       KC_T,         KC_Y,       KC_U,       KC_I,       KC_O,       KC_P,       KC_BSPC,
//| --------- | --------- | --------- | --------- | --------- | --------- ||| --------- | --------- | --------- | --------- | --------- | --------- |
    KC_TAB,     KC_A,       KC_S,       KC_D,       KC_F,       KC_G,         KC_H,       KC_J,       KC_K,       KC_L,       KC_SCLN,    KC_ENT,
//| --------- | --------- | --------- | --------- | --------- | --------- ||| --------- | --------- | --------- | --------- | --------- | --------- |
    OSM(MOD_LSFT), KC_Z,    KC_X,       KC_C,       KC_V,       KC_B,         KC_N,       KC_M,       KC_COMM,    KC_DOT,     KC_SLSH,    OSM(MOD_RSFT),
//| --------- | --------- | --------- | --------- | --------- | --------- ||| --------- | --------- | --------- | --------- | --------- | --------- |
    KC_MPLY,    KC_LCTL,    KC_LALT,    KC_LGUI,    OSM(MOD_LSFT), TO(1),     TD(TD_HOME_LAYER), KC_SPC, KC_RGUI, KC_RALT,    KC_RCTL,    XXXXXXX
//| --------- | --------- | --------- | --------- | --------- | --------- ||| --------- | --------- | --------- | --------- | --------- | --------- |
),

[_SYMBOL] = LAYOUT_preonic_grid(
//| --------- | --------- | --------- | --------- | --------- | --------- ||| --------- | --------- | --------- | --------- | --------- | --------- |
    XXXXXXX,    KC_1,       KC_2,       KC_3,       KC_4,       KC_5,         KC_6,       KC_7,       KC_8,       KC_9,       KC_0,       XXXXXXX,
//| --------- | --------- | --------- | --------- | --------- | --------- ||| --------- | --------- | --------- | --------- | --------- | --------- |
    KC_TRNS,    KC_QUOT,    KC_LABK,    KC_RABK,    KC_DQUO,    KC_DOT,       KC_AMPR,    KC_CIRC,    KC_LBRC,    KC_RBRC,    KC_PERC,    KC_TRNS,
//| --------- | --------- | --------- | --------- | --------- | --------- ||| --------- | --------- | --------- | --------- | --------- | --------- |
    KC_TRNS,    KC_EXLM,    KC_MINS,    KC_PLUS,    KC_EQL,     KC_HASH,      KC_PIPE,    KC_COLN,    KC_LPRN,    KC_RPRN,    KC_QUES,    KC_TRNS,
//| --------- | --------- | --------- | --------- | --------- | --------- ||| --------- | --------- | --------- | --------- | --------- | --------- |
    KC_TRNS,    TO(3),      KC_SLASH,   KC_ASTR,    KC_BSLS,    XXXXXXX,      KC_TILD,    KC_DLR,     KC_LCBR,    KC_RCBR,    KC_AT,      KC_TRNS,
//| --------- | --------- | --------- | --------- | --------- | --------- ||| --------- | --------- | --------- | --------- | --------- | --------- |
    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    TO(2),        TO(0),      KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS
//| --------- | --------- | --------- | --------- | --------- | --------- ||| --------- | --------- | --------- | --------- | --------- | --------- |
),

[_NUMBER] = LAYOUT_preonic_grid(
//| --------- | --------- | --------- | --------- | --------- | --------- ||| --------- | --------- | --------- | --------- | --------- | --------- |
    XXXXXXX,    XXXXXXX,    KC_KB_MUTE, VOL_DOWN,   VOL_UP,     XXXXXXX,      XXXXXXX,    XXXXXXX,    KC_PSLS,    KC_PAST,    KC_PMNS,    XXXXXXX,
//| --------- | --------- | --------- | --------- | --------- | --------- ||| --------- | --------- | --------- | --------- | --------- | --------- |
    KC_TRNS,    XXXXXXX,    KC_F9,      KC_F10,     KC_F11,     KC_F12,       XXXXXXX,    KC_7,       KC_8,       KC_9,       KC_PPLS,    KC_TRNS,
//| --------- | --------- | --------- | --------- | --------- | --------- ||| --------- | --------- | --------- | --------- | --------- | --------- |
    KC_TRNS,    XXXXXXX,    KC_F5,      KC_F6,      KC_F6,      KC_F7,        XXXXXXX,    KC_4,       KC_5,       KC_6,       KC_COMM,    KC_TRNS,
//| --------- | --------- | --------- | --------- | --------- | --------- ||| --------- | --------- | --------- | --------- | --------- | --------- |
    KC_TRNS,    TO(3),      KC_F1,      KC_F2,      KC_F3,      KC_F4,        KC_0,       KC_1,       KC_2,       KC_3,       KC_PDOT,    KC_TRNS,
//| --------- | --------- | --------- | --------- | --------- | --------- ||| --------- | --------- | --------- | --------- | --------- | --------- |
    KC_TRNS, KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    XXXXXXX,         TO(0),      KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS
//| --------- | --------- | --------- | --------- | --------- | --------- ||| --------- | --------- | --------- | --------- | --------- | --------- |
),

[_NAVIGATE] = LAYOUT_preonic_grid(
//| --------- | --------- | --------- | --------- | --------- | --------- ||| --------- | --------- | --------- | --------- | --------- | --------- |
    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,      XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,
//| --------- | --------- | --------- | --------- | --------- | --------- ||| --------- | --------- | --------- | --------- | --------- | --------- |
    KC_TRNS,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,      KC_HOME,    KC_PGDN,    KC_PGUP,    KC_END,     XXXXXXX,    KC_TRNS,
//| --------- | --------- | --------- | --------- | --------- | --------- ||| --------- | --------- | --------- | --------- | --------- | --------- |
    KC_TRNS,    XXXXXXX,    KC_LCTL,    KC_LALT,    KC_LGUI,    XXXXXXX,       KC_LEFT,    KC_DOWN,    KC_UP,      KC_RIGHT,   XXXXXXX,    KC_TRNS,
//| --------- | --------- | --------- | --------- | --------- | --------- ||| --------- | --------- | --------- | --------- | --------- | --------- |
    KC_TRNS,    XXXXXXX,    KC_CUT,     KC_COPY,    KC_PSTE,    XXXXXXX,       XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    KC_TRNS,
//| --------- | --------- | --------- | --------- | --------- | --------- ||| --------- | --------- | --------- | --------- | --------- | --------- |
    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    XXXXXXX,       TO(0),      KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS
//| --------- | --------- | --------- | --------- | --------- | --------- ||| --------- | --------- | --------- | --------- | --------- | --------- |
)
};

td_state_t cur_dance (qk_tap_dance_state_t *state) {
  if (state->count == 1) {
    if (!state->pressed) {
      return TD_SINGLE_TAP;
    } else {
      return TD_SINGLE_HOLD;
    }
  }
  else return TD_UNKNOWN;
}

static td_tap_t ql_tap_state = {
  .is_press_action = true,
  .state = TD_NONE
};

void ql_finished (qk_tap_dance_state_t *state, void *user_data) {
  ql_tap_state.state = cur_dance(state);
  switch (ql_tap_state.state) {
    case TD_SINGLE_TAP:
      layer_move(_BASE);
      break;
    case TD_SINGLE_HOLD:
      layer_on(_NAVIGATION);
      break;
    default:
      break;
  }
}

void ql_reset(qk_tap_dance_state_t *state, void *user_data) {
  if (ql_tap_state.state == TD_SINGLE_HOLD) {
    layer_off(_NAVIGATION);
  }

  ql_tap_state.state = TD_NONE;
}


qk_tap_dance_action_t tap_dance_actions[] = {
  [TD_HOME_LAYER] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, ql_finished, ql_reset)
};
