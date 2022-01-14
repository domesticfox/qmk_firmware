/*
Copyright 2019 @foostan
Copyright 2020 Drashna Jaelre <@drashna>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H
#include <stdio.h>


enum {
	WIN_A,
	F11,
	F12,
	QW_DEL,
	CM_DEL,
};

qk_tap_dance_action_t tap_dance_actions[] = {
	[WIN_A] = ACTION_TAP_DANCE_DOUBLE(KC_A, KC_LGUI),
	[F11] = ACTION_TAP_DANCE_DOUBLE(KC_F5, KC_F11),
	[F12] = ACTION_TAP_DANCE_DOUBLE(KC_F6, KC_F12),	
	[QW_DEL] = ACTION_TAP_DANCE_LAYER_MOVE(KC_DEL,1),
	[CM_DEL] = ACTION_TAP_DANCE_LAYER_MOVE(KC_DEL,0),

};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	//colemak
  [0] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      XXXXXXX,    KC_Q,    KC_W,    KC_F,    KC_P,    KC_B,                         KC_J,    KC_L,    KC_U,    KC_Y, KC_SCLN,  XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                |------------+--------+--------+--------+--------+--------|
   XXXXXXX, TD(WIN_A), ALT_T(KC_R), CTL_T(KC_S), SFT_T(KC_T), KC_G,         KC_M, RSFT_T(KC_N),CTL_T(KC_E), ALT_T(KC_I), KC_O, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX, KC_Z,  ALGR_T(KC_X),    KC_C,    KC_D,    KC_V,                         KC_K,    KC_H, KC_COMM,  ALGR_T(KC_DOT), KC_SLSH,  XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                   LT(2, KC_TAB), XXXXXXX,  LT(3,KC_SPC),    KC_ENT,   TD(QW_DEL), KC_BSPC
                                      //`--------------------------'  `--------------------------'

  ),
  //qwerty	
  [1] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      XXXXXXX,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                         KC_Y,    KC_U,    KC_I,    KC_O, KC_P,     XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX, TD(WIN_A), ALT_T(KC_S), CTL_T(KC_D), SFT_T(KC_F), KC_G,         KC_H,    RSFT_T(KC_J),    CTL_T(KC_K), ALT_T(KC_L), KC_SCLN, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX,    KC_Z,    ALGR_T(KC_X),    KC_C,    KC_V,    KC_B,                         KC_N,    KC_M, KC_COMM,  ALGR_T(KC_DOT), KC_SLSH,  XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                  LT(2, KC_TAB), XXXXXXX,  LT(4,KC_SPC),     KC_ENT,   TD(CM_DEL), LT(3, KC_BSPC)
                                      //`--------------------------'  `--------------------------'

  ),

  //navigation
  [2] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, C(S(KC_ESC)),                 C(KC_Y), XXXXXXX,  KC_UP,   XXXXXXX, XXXXXXX,  XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX, C(KC_A), C(KC_S), KC_LALT, KC_LCTL, KC_LSFT,                      XXXXXXX, KC_LEFT, KC_DOWN, KC_RIGHT, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX, C(KC_Z), C(KC_X), C(KC_C), C(KC_V), G(S(KC_S)),                  KC_INS,   KC_HOME, KC_PGDN, KC_PGUP, KC_END,   XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          _______, XXXXXXX,  KC_SPC,     KC_ENT,   _______, _______
                                      //`--------------------------'  `--------------------------'
  ),

  //num - fn - symbol
  [3] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       XXXXXXX, KC_F1,   KC_F2,   KC_F3,   KC_F4,  TD(F11),                     TD(F12),   KC_F7,   KC_F8,   KC_F9,   KC_F10,   XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX,  KC_1,    KC_2,    KC_3,    SFT_T(KC_4),   KC_5,                         KC_6,    RSFT_T(KC_7),    KC_8,    KC_9,    KC_0,     XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX, KC_ESC, KC_CAPS, KC_LNG1, KC_QUOT, KC_GRV,                      KC_MINS, KC_EQL, KC_LBRC, KC_RBRC, KC_BSLS, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                       _______,   XXXXXXX,  XXXXXXX,    XXXXXXX, XXXXXXX, _______
                                      //`--------------------------'  `--------------------------'
  /*),
  


 //numpad
  [4] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      XXXXXXX, XXXXXXX,   XXXXXXX, XXXXXXX, XXXXXXX, KC_LNG1,                      KC_NUM, KC_P7,   KC_P8,   KC_P9,   XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_PAST,                      KC_PPLS, KC_P4,   KC_P5,   KC_P6,   XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_PSLS,                      KC_PMNS, KC_P1,   KC_P2,   KC_P3,   XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                         XXXXXXX, XXXXXXX,  _______,     KC_P0, KC_PDOT, XXXXXXX
                                      //`--------------------------'  `--------------------------'
 
	*/
 )
};

#ifdef OLED_ENABLE

#define _BASE 0
#define _QWERTY 1
#define _NAV 2
#define _SYM 3
//#define _NUM 4


void oled_render_layer_state(void) {
    oled_write_P(PSTR("Layer: "), false);
    switch (layer_state) {
        case _BASE:
            oled_write_ln_P(PSTR("Colemak"), false);
            break;
		case _QWERTY:
            oled_write_ln_P(PSTR("QWERTY"), false);
            break;
        case _NAV:
            oled_write_ln_P(PSTR("Navigate"), false);
            break;
        case _SYM:
            oled_write_ln_P(PSTR("Symbol"), false);
            break;
        //case _NUM:
        //    oled_write_ln_P(PSTR("Numpad"), false);
        //    break;
		default:
		oled_write_ln_P(PSTR("Adjust"), false);
    }
}

char keylog_str[24] = {};

const char code_to_name[60] = {
    ' ', ' ', ' ', ' ', 'a', 'b', 'c', 'd', 'e', 'f',
    'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p',
    'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
    '1', '2', '3', '4', '5', '6', '7', '8', '9', '0',
    'R', 'E', 'B', 'T', '_', '-', '=', '[', ']', '\\',
    '#', ';', '\'', '`', ',', '.', '/', ' ', ' ', ' '};

void set_keylog(uint16_t keycode, keyrecord_t *record) {
  char name = ' ';
    if ((keycode >= QK_MOD_TAP && keycode <= QK_MOD_TAP_MAX) ||
        (keycode >= QK_LAYER_TAP && keycode <= QK_LAYER_TAP_MAX)) { keycode = keycode & 0xFF; }
  if (keycode < 60) {
    name = code_to_name[keycode];
  }

  // update keylog
  snprintf(keylog_str, sizeof(keylog_str), "%dx%d, k%2d : %c",
           record->event.key.row, record->event.key.col,
           keycode, name);
}

void oled_render_keylog(void) {
    oled_write(keylog_str, false);
}

void render_bootmagic_status(bool status) {
    /* Show Ctrl-Gui Swap options */
    static const char PROGMEM logo[][2][3] = {
        {{0x97, 0x98, 0}, {0xb7, 0xb8, 0}},
        {{0x95, 0x96, 0}, {0xb5, 0xb6, 0}},
    };
    if (status) {
        oled_write_ln_P(logo[0][0], false);
        oled_write_ln_P(logo[0][1], false);
    } else {
        oled_write_ln_P(logo[1][0], false);
        oled_write_ln_P(logo[1][1], false);
    }
}


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
    set_keylog(keycode, record);
  }
  return true;
}
#endif // OLED_ENABLE
