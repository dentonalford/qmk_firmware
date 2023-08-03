
 /* Copyright 2021 Dane Evans
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
  // SOFLE RGB
#include <stdio.h>

#include QMK_KEYBOARD_H

#define INDICATOR_BRIGHTNESS 30

#define HSV_OVERRIDE_HELP(h, s, v, Override) h, s , Override
#define HSV_OVERRIDE(hsv, Override) HSV_OVERRIDE_HELP(hsv,Override)

// Light combinations
#define SET_INDICATORS(hsv) \
	{0, 1, HSV_OVERRIDE_HELP(hsv, INDICATOR_BRIGHTNESS)}, \
    {35+0, 1, hsv}
#define SET_UNDERGLOW(hsv) \
	{1, 6, hsv}, \
    {35+1, 6,hsv}
#define SET_NUMPAD(hsv)     \
	{35+15, 5, hsv},\
	  {35+22, 3, hsv},\
	  {35+27, 3, hsv}
#define SET_NUMROW(hsv) \
	{10, 2, hsv}, \
		{20, 2, hsv}, \
		{30, 2, hsv}, \
	  {35+ 10, 2, hsv}, \
	  {35+ 20, 2, hsv}, \
	  {35+ 30, 2, hsv}
#define SET_INNER_COL(hsv)	\
	{33, 4, hsv}, \
	  {35+ 33, 4, hsv}

#define SET_OUTER_COL(hsv) \
	{7, 4, hsv}, \
	  {35+ 7, 4, hsv}
#define SET_THUMB_CLUSTER(hsv) 	\
	{25, 2, hsv}, \
	  {35+ 25, 2, hsv}
#define SET_LAYER_ID(hsv) 	\
	{0, 1, HSV_OVERRIDE_HELP(hsv, INDICATOR_BRIGHTNESS)}, \
    {35+0, 1, HSV_OVERRIDE_HELP(hsv, INDICATOR_BRIGHTNESS)}, \
		{1, 6, hsv}, \
    {35+1, 6, hsv}, \
		{7, 4, hsv}, \
	  {35+ 7, 4, hsv}, \
		{25, 2, hsv}, \
	  {35+ 25, 2, hsv}

typedef struct {
  bool is_press_action;
  int state;
} td_tap_t;

typedef enum {
  TD_NONE,
  TD_UNKNOWN,
  TD_SINGLE_TAP,
  TD_SINGLE_HOLD,
  TD_DOUBLE_TAP,
  TD_DOUBLE_HOLD,
  TD_TRIPLE_TAP,
  TD_TRIPLE_HOLD,
} td_state_t;

enum {
  TD_GAME_TOGGLE = 0,
};


enum sofle_layers {
    _BASE = 0,
    _SYML,
    _SYMR,
    _NUML,
    _NUMR,
    _NAV,
    _GAME,
};

td_state_t cur_dance(tap_dance_state_t *state);

void ql_game_toggle_finished(tap_dance_state_t *state, void *user_data);
void ql_game_toggle_reset(tap_dance_state_t *state, void *user_data);

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT(
    //| --------- | --------- | --------- | --------- | --------- | --------- |                       | --------- | --------- | --------- | --------- | --------- | --------- |
        KC_GRAVE,   KC_1,       KC_2,       KC_3,       KC_4,       TD(TD_GAME_TOGGLE),                 KC_6,       KC_7,       KC_8,       KC_9,       KC_0,       KC_MINUS,
    //| --------- | --------- | --------- | --------- | --------- | --------- |                       | --------- | --------- | --------- | --------- | --------- | --------- |
        KC_ESC,     KC_Q,       KC_W,       KC_E,       KC_R,       KC_T,                               KC_Y,       KC_U,       KC_I,       KC_O,       KC_P,       KC_BSPC,
    //| --------- | --------- | --------- | --------- | --------- | --------- |                       | --------- | --------- | --------- | --------- | --------- | --------- |
        KC_TAB,     KC_A,       KC_S,       KC_D,       KC_F,       KC_G,                               KC_H,       KC_J,       KC_K,       KC_L,       KC_SCLN,    KC_ENT,
    //| --------- | --------- | --------- | --------- | --------- | --------- | ---------\ /--------- | --------- | --------- | --------- | --------- | --------- | --------- |
        OSM(MOD_LSFT), KC_Z,   KC_X, LT(_NUMR,KC_C),LT(_SYMR,KC_V), KC_B,       KC_MPLY,    XXXXXXX,    KC_N, LT(_SYML,KC_M),LT(_NUML,KC_COMM), KC_DOT, KC_SLSH, OSM(MOD_RSFT),
    //| --------- | --------- | --------- | --------- | --------- | --------- | ---------| |--------- | --------- | -------- | --------- | --------- | --------- | --------- |
                                KC_LCTL,    KC_LALT,    KC_LGUI,  OSM(MOD_LSFT), MO(_NAV),  XXXXXXX,    KC_SPC,     KC_RGUI,   KC_RALT,    KC_RCTL
    //                        \ --------- | --------- | --------- | --------- | ---------/ \--------- | --------- | -------- | --------- | --------- /
    ),

    [_SYML] = LAYOUT(
    //| --------- | --------- | --------- | --------- | --------- | --------- |                       | --------- | --------- | --------- | --------- | --------- | --------- |
        KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,                            KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,
    //| --------- | --------- | --------- | --------- | --------- | --------- |                       | --------- | --------- | --------- | --------- | --------- | --------- |
        KC_TRNS,    KC_EXLM,    KC_AT,      KC_HASH,    KC_DLR,     KC_PERC,                            KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,
    //| --------- | --------- | --------- | --------- | --------- | --------- |                       | --------- | --------- | --------- | --------- | --------- | --------- |
        KC_TRNS,    XXXXXXX,    KC_GRV,     KC_MINS,    KC_QUOT,    KC_PIPE,                            KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,
    //| --------- | --------- | --------- | --------- | --------- | --------- | ---------\ /--------- | --------- | --------- | --------- | --------- | --------- | --------- |
        XXXXXXX,    XXXXXXX,    KC_TILD,    KC_UNDS,    KC_DQUO,    KC_BSLS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,
    //| --------- | --------- | --------- | --------- | --------- | --------- | ---------| |--------- | --------- | --------- | --------- | --------- | --------- | --------- |
                                KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS
    //                        \ --------- | --------- | --------- | --------- | ---------/ \--------- | --------- | --------- | --------- | --------- /
    ),

    [_SYMR] = LAYOUT(
    //| --------- | --------- | --------- | --------- | --------- | --------- |                       | --------- | --------- | --------- | --------- | --------- | --------- |
        KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,                            KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,
    //| --------- | --------- | --------- | --------- | --------- | --------- |                       | --------- | --------- | --------- | --------- | --------- | --------- |
        KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,                            KC_CIRC,    KC_AMPR,    KC_LBRC,    KC_RBRC,    KC_TRNS,    KC_TRNS,
    //| --------- | --------- | --------- | --------- | --------- | --------- |                       | --------- | --------- | --------- | --------- | --------- | --------- |
        KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,                            KC_RABK,    KC_EQL,     KC_LPRN,    KC_RPRN,    KC_ASTR,    KC_TRNS,
    //| --------- | --------- | --------- | --------- | --------- | --------- | ---------\ /--------- | --------- | --------- | --------- | --------- | --------- | --------- |
        KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_LABK,    KC_PLUS,    KC_LCBR,    KC_RCBR,    KC_TRNS,    KC_TRNS,
    //| --------- | --------- | --------- | --------- | --------- | --------- | ---------| |--------- | --------- | --------- | --------- | --------- | --------- | --------- |
                                KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS
    //                        \ --------- | --------- | --------- | --------- | ---------/ \--------- | --------- | --------- | --------- | --------- /
    ),

    [_NUML] = LAYOUT(
    //| --------- | --------- | --------- | --------- | --------- | --------- |                       | --------- | --------- | --------- | --------- | --------- | --------- |
        KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,                            KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,
    //| --------- | --------- | --------- | --------- | --------- | --------- |                       | --------- | --------- | --------- | --------- | --------- | --------- |
        KC_TRNS,    KC_F9,      KC_F10,     KC_F11,     KC_F12,     KC_TRNS,                            KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,
    //| --------- | --------- | --------- | --------- | --------- | --------- |                       | --------- | --------- | --------- | --------- | --------- | --------- |
        KC_TRNS,    KC_F5,      KC_F6,      KC_F7,      KC_F8,      KC_TRNS,                            KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,
    //| --------- | --------- | --------- | --------- | --------- | --------- | ---------\ /--------- | --------- | --------- | --------- | --------- | --------- | --------- |
        KC_TRNS,    KC_F1,      KC_F2,      KC_F3,      KC_F4,      KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,
    //| --------- | --------- | --------- | --------- | --------- | --------- | ---------| |--------- | --------- | --------- | --------- | --------- | --------- | --------- |
                                KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS
    //                        \ --------- | --------- | --------- | --------- | ---------/ \--------- | --------- | --------- | --------- | --------- /
    ),
    [_NUMR] = LAYOUT(
    //| --------- | --------- | --------- | --------- | --------- | --------- |                       | --------- | --------- | --------- | --------- | --------- | --------- |
        KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,                            KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,
    //| --------- | --------- | --------- | --------- | --------- | --------- |                       | --------- | --------- | --------- | --------- | --------- | --------- |
        KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,                            KC_DOT,     KC_7,       KC_8,       KC_9,       KC_ASTR,    KC_TRNS,
    //| --------- | --------- | --------- | --------- | --------- | --------- |                       | --------- | --------- | --------- | --------- | --------- | --------- |
        KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,                            KC_COMM,    KC_4,       KC_5,       KC_6,       KC_MINS,    KC_TRNS,
    //| --------- | --------- | --------- | --------- | --------- | --------- | ---------\ /--------- | --------- | --------- | --------- | --------- | --------- | --------- |
        KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_0,       KC_1,       KC_2,       KC_3,       KC_PLUS,    KC_TRNS,
    //| --------- | --------- | --------- | --------- | --------- | --------- | ---------| |--------- | --------- | --------- | --------- | --------- | --------- | --------- |
                                KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS
    //                        \ --------- | --------- | --------- | --------- | ---------/ \--------- | --------- | --------- | --------- | --------- /
    ),

    [_NAV] = LAYOUT(
    //| --------- | --------- | --------- | --------- | --------- | --------- |                       | --------- | --------- | --------- | --------- | --------- | --------- |
        KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_KB_VOLUME_UP,                    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,
    //| --------- | --------- | --------- | --------- | --------- | --------- |                       | --------- | --------- | --------- | --------- | --------- | --------- |
        KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_KB_VOLUME_DOWN,                  KC_HOME,    KC_PGDN,    KC_PGUP,    KC_END,     KC_TRNS,    KC_TRNS,
    //| --------- | --------- | --------- | --------- | --------- | --------- |                       | --------- | --------- | --------- | --------- | --------- | --------- |
        KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_DEL,     KC_BSPC,    KC_TRNS,                            KC_LEFT,    KC_DOWN,    KC_UP,      KC_RIGHT,   KC_TRNS,    KC_TRNS,
    //| --------- | --------- | --------- | --------- | --------- | --------- | ---------\ /--------- | --------- | --------- | --------- | --------- | --------- | --------- |
        KC_TRNS,    KC_TRNS,    KC_CUT,     KC_COPY,    KC_PSTE,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_PSTE,    KC_COPY,    KC_CUT,     KC_TRNS,    KC_TRNS,
    //| --------- | --------- | --------- | --------- | --------- | --------- | ---------| |--------- | --------- | --------- | --------- | --------- | --------- | --------- |
                                KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS
    //                        \ --------- | --------- | --------- | --------- | ---------/ \--------- | --------- | --------- | --------- | --------- /
    ),

    [_GAME] = LAYOUT(
    //| --------- | --------- | --------- | --------- | --------- | --------- |                       | --------- | --------- | --------- | --------- | --------- | --------- |
        KC_ESC,     KC_1,       KC_2,       KC_3,       KC_4,       TD(TD_GAME_TOGGLE),                   XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,
    //| --------- | --------- | --------- | --------- | --------- | --------- |                       | --------- | --------- | --------- | --------- | --------- | --------- |
        KC_TAB,     KC_Q,       KC_W,       KC_E,       KC_R,       KC_T,                               XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,
    //| --------- | --------- | --------- | --------- | --------- | --------- |                       | --------- | --------- | --------- | --------- | --------- | --------- |
        KC_LSFT,    KC_A,       KC_S,       KC_D,       KC_F,       KC_G,                               XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,
    //| --------- | --------- | --------- | --------- | --------- | --------- | ---------\ /--------- | --------- | --------- | --------- | --------- | --------- | --------- |
        KC_GRAVE,   KC_Z,       KC_X,       KC_C,       KC_V,       KC_B,       XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,
    //| --------- | --------- | --------- | --------- | --------- | --------- | ---------| |--------- | --------- | --------- | --------- | --------- | --------- | --------- |
                                KC_F1,      KC_F2,      KC_LALT,    KC_SPC,     KC_LCTL,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX
    //                        \ --------- | --------- | --------- | --------- | ---------/ \--------- | --------- | --------- | --------- | --------- /
    )

    // [_BLANK] = LAYOUT(
    //| --------- | --------- | --------- | --------- | --------- | --------- |                       | --------- | --------- | --------- | --------- | --------- | --------- |
    //   XXXXXXX,      XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,                            XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,
    //| --------- | --------- | --------- | --------- | --------- | --------- |                       | --------- | --------- | --------- | --------- | --------- | --------- |
    //   XXXXXXX,      XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,                            XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,
    //| --------- | --------- | --------- | --------- | --------- | --------- |                       | --------- | --------- | --------- | --------- | --------- | --------- |
    //   XXXXXXX,      XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,                            XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,
    //| --------- | --------- | --------- | --------- | --------- | --------- | ---------\ /--------- | --------- | --------- | --------- | --------- | --------- | --------- |
    //   XXXXXXX,      XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,
    //| --------- | --------- | --------- | --------- | --------- | --------- | ---------| |--------- | --------- | --------- | --------- | --------- | --------- | --------- |
                                // XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX,    XXXXXXX
    //                        \ --------- | --------- | --------- | --------- | ---------/ \--------- | --------- | --------- | --------- | --------- /
    // )
};

#ifdef RGBLIGHT_ENABLE
char layer_state_str[70];
// Now define the array of layers. Later layers take precedence

// QWERTY,
// Light on inner column and underglow
const rgblight_segment_t PROGMEM layer_qwerty_lights[] = RGBLIGHT_LAYER_SEGMENTS(
  SET_LAYER_ID(HSV_RED)

);
const rgblight_segment_t PROGMEM layer_colemakdh_lights[] = RGBLIGHT_LAYER_SEGMENTS(
  SET_LAYER_ID(HSV_PINK)
);

// _NUM,
// Light on outer column and underglow
const rgblight_segment_t PROGMEM layer_num_lights[] = RGBLIGHT_LAYER_SEGMENTS(
	SET_LAYER_ID(HSV_TEAL)

);
// _SYMBOL,
// Light on inner column and underglow
const rgblight_segment_t PROGMEM layer_symbol_lights[] = RGBLIGHT_LAYER_SEGMENTS(
	SET_LAYER_ID(HSV_BLUE)

    );
// _COMMAND,
// Light on inner column and underglow
const rgblight_segment_t PROGMEM layer_command_lights[] = RGBLIGHT_LAYER_SEGMENTS(
  SET_LAYER_ID(HSV_PURPLE)
);

//_NUMPAD
const rgblight_segment_t PROGMEM layer_numpad_lights[] = RGBLIGHT_LAYER_SEGMENTS(
	SET_INDICATORS(HSV_ORANGE),
    SET_UNDERGLOW(HSV_ORANGE),
	SET_NUMPAD(HSV_BLUE),
    {7, 4, HSV_ORANGE},
    {25, 2, HSV_ORANGE},
    {35+6, 4, HSV_ORANGE},
    {35+25, 2, HSV_ORANGE}
    );
// _SWITCHER   // light up top row
const rgblight_segment_t PROGMEM layer_switcher_lights[] = RGBLIGHT_LAYER_SEGMENTS(
	SET_LAYER_ID(HSV_GREEN),
	SET_NUMROW(HSV_GREEN)
);

const rgblight_segment_t* const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(

    layer_qwerty_lights,
	layer_num_lights,// overrides layer 1
	layer_symbol_lights,
    layer_command_lights,
	layer_numpad_lights,
	layer_switcher_lights,  // Overrides other layers
	layer_colemakdh_lights
);

layer_state_t layer_state_set_user(layer_state_t state) {
	// rgblight_set_layer_state(0, layer_state_cmp(state, _DEFAULTS) && layer_state_cmp(default_layer_state,_QWERTY));
	// rgblight_set_layer_state(7, layer_state_cmp(state, _DEFAULTS) && layer_state_cmp(default_layer_state,_COLEMAKDH));


	// rgblight_set_layer_state(1, layer_state_cmp(state, _LOWER));
	// rgblight_set_layer_state(2, layer_state_cmp(state, _RAISE));
	// rgblight_set_layer_state(3, layer_state_cmp(state, _ADJUST));
	// rgblight_set_layer_state(4, layer_state_cmp(state, _NUMPAD));
	// rgblight_set_layer_state(5, layer_state_cmp(state, _SWITCH));
    return state;
}
void keyboard_post_init_user(void) {
    // Enable the LED layers
    rgblight_layers = my_rgb_layers;

	rgblight_mode(10);// haven't found a way to set this in a more useful way

}
#endif

#ifdef OLED_ENABLE

static void render_logo(void) {
    static const char PROGMEM qmk_logo[] = {
        0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8A, 0x8B, 0x8C, 0x8D, 0x8E, 0x8F, 0x90, 0x91, 0x92, 0x93, 0x94,
        0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5, 0xA6, 0xA7, 0xA8, 0xA9, 0xAA, 0xAB, 0xAC, 0xAD, 0xAE, 0xAF, 0xB0, 0xB1, 0xB2, 0xB3, 0xB4,
        0xC0, 0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7, 0xC8, 0xC9, 0xCA, 0xCB, 0xCC, 0xCD, 0xCE, 0xCF, 0xD0, 0xD1, 0xD2, 0xD3, 0xD4, 0x00
    };

    oled_write_P(qmk_logo, false);
}

static void print_status_narrow(void) {
    // Print current mode
    oled_write_P(PSTR("\n\n"), false);
    oled_write_ln_P(PSTR("Dane\nEvans"), false);

    oled_write_ln_P(PSTR(""), false);

	//snprintf(layer_state_str, sizeof(layer_state_str), "Layer: Undef-%ld", layer_state)


    switch (get_highest_layer(default_layer_state)) {
        // case _QWERTY:
        //     oled_write_ln_P(PSTR("Qwrt"), false);
        //     break;
        // case _COLEMAK:
        //     oled_write_ln_P(PSTR("Clmk"), false);
        //     break;
        // case _COLEMAKDH:
        //     oled_write_ln_P(PSTR("CmkDH"), false);
        //     break;

        default:
            oled_write_ln_P(PSTR("Undef"), false);
    }
    oled_write_P(PSTR("\n\n"), false);
    // Print current layer
    oled_write_ln_P(PSTR("LAYER"), false);
    switch (get_highest_layer(layer_state)) {
        // case _COLEMAK:
        // case _QWERTY:
        // case _COLEMAKDH:
        //     oled_write_P(PSTR("Base\n"), false);
        //     break;
        // case _RAISE:
        //     oled_write_P(PSTR("Raise"), false);
        //     break;
        // case _LOWER:
        //     oled_write_P(PSTR("Lower"), false);
        //     break;
        // case _ADJUST:
        //     oled_write_P(PSTR("Adj\n"), false);
        //     break;
        // case _NUMPAD:
        //     oled_write_P(PSTR("Nump\n"), false);
        //     break;
        // case _SWITCH:
        //     oled_write_P(PSTR("Swit\n"), false);
        //     break;
        default:
            oled_write_ln_P(PSTR("Undef"), false);
    }
}

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    if (is_keyboard_master()) {
        return OLED_ROTATION_270;
    }
    return rotation;
}

bool oled_task_user(void) {
    if (is_keyboard_master()) {
        print_status_narrow();
    } else {
        render_logo();
    }
    return false;
}

#endif

bool process_record_user(uint16_t keycode, keyrecord_t *record) {

    // switch (keycode) {
    //     case KC_QWERTY:
    //         if (record->event.pressed) {
    //             set_single_persistent_default_layer(_QWERTY);
    //         }
    //         return false;
    //     case KC_COLEMAK:
    //         if (record->event.pressed) {
    //             set_single_persistent_default_layer(_COLEMAK);
    //         }
    //         return false;
    //     case KC_COLEMAKDH:
    //         if (record->event.pressed) {
    //             set_single_persistent_default_layer(_COLEMAKDH);
    //         }
    //         return false;
    //     case KC_LOWER:
    //         if (record->event.pressed) {
    //             layer_on(_LOWER);
    //             update_tri_layer(_LOWER, _RAISE, _ADJUST);
    //         } else {
    //             layer_off(_LOWER);
    //             update_tri_layer(_LOWER, _RAISE, _ADJUST);
    //         }
    //         return false;
    //     case KC_RAISE:
    //         if (record->event.pressed) {
    //             layer_on(_RAISE);
    //             update_tri_layer(_LOWER, _RAISE, _ADJUST);
    //         } else {
    //             layer_off(_RAISE);
    //             update_tri_layer(_LOWER, _RAISE, _ADJUST);
    //         }
    //         return false;
    //     case KC_ADJUST:
    //         if (record->event.pressed) {
    //             layer_on(_ADJUST);
    //         } else {
    //             layer_off(_ADJUST);
    //         }
    //         return false;
    //     case KC_D_MUTE:
    //         if (record->event.pressed) {
    //             register_mods(mod_config(MOD_MEH));
    //             register_code(KC_UP);
    //         } else {
    //             unregister_mods(mod_config(MOD_MEH));
    //             unregister_code(KC_UP);
    //         }
    // }
    return true;
}

td_state_t cur_dance (tap_dance_state_t *state) {
  if (state->count == 1) {
    if (!state->pressed) {
      return TD_SINGLE_TAP;
    } else {
      return TD_SINGLE_HOLD;
    }
  } else if (state->count == 2) {
    if (!state->pressed) {
      return TD_DOUBLE_TAP;
    } else {
      return TD_DOUBLE_HOLD;
    }
  } else if (state->count == 3) {
    if (!state->pressed) {
      return TD_TRIPLE_TAP;
    } else {
      return TD_TRIPLE_HOLD;
    }
  }
  else return TD_UNKNOWN;
}

static td_tap_t ql_tap_state = {
  .is_press_action = true,
  .state = TD_NONE
};

void ql_game_toggle_finished (tap_dance_state_t *state, void *user_data) {
  ql_tap_state.state = cur_dance(state);
  switch (ql_tap_state.state) {
    case TD_SINGLE_TAP:
      register_code16(KC_5);
      break;
    case TD_DOUBLE_TAP:
      tap_code16(KC_5);
      register_code16(KC_5);
      break;
    case TD_TRIPLE_TAP:
      tap_code16(KC_5);
      tap_code16(KC_5);
      register_code16(KC_5);
      break;
    case TD_TRIPLE_HOLD:
      if (IS_LAYER_ON(_GAME)) {
        layer_off(_GAME);
      } else {
        layer_on(_GAME);
      }
      break;
    default:
      break;
  }
}

void ql_game_toggle_reset(tap_dance_state_t *state, void *user_data) {
  switch(ql_tap_state.state) {
    case TD_SINGLE_TAP: unregister_code16(KC_5); break;
    case TD_DOUBLE_TAP: unregister_code16(KC_5); break;
    case TD_TRIPLE_TAP: unregister_code16(KC_5); break;
    default: break;
  }
  ql_tap_state.state = TD_NONE;
}

tap_dance_action_t tap_dance_actions[] = {
  [TD_GAME_TOGGLE] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, ql_game_toggle_finished, ql_game_toggle_reset)
};

#ifdef ENCODER_ENABLE

bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {
        if (clockwise) {
            tap_code(KC_WH_U);
        } else {
            tap_code(KC_WH_D);
        }
    } else if (index == 1) {
            if (clockwise) {
                tap_code(KC_VOLU);
            } else {
                tap_code(KC_VOLD);
            }
		}
    return true;
}

#endif
