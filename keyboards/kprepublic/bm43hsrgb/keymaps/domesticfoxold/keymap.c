/* Copyright 2021 bitstarr
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



const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[0] = LAYOUT(
        KC_ESC,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
        KC_TAB,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_ENT,
        KC_LSFT,          KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_UP,   KC_DOT,
        KC_LCTL, KC_LGUI, KC_LALT, KC_SPC,                 KC_SPC,              MO(2),   KC_LEFT, KC_DOWN, KC_RGHT
    ),
	#
	[1] = LAYOUT(
        KC_ESC,   KC_Q, KC_W, KC_F, KC_P, KC_B, KC_J, KC_L, KC_U, KC_Y, KC_SCLN, KC_CAPS,
        KC_DEL,   KC_A, KC_R,  KC_S,  KC_T, KC_G, KC_M, KC_N, KC_E, KC_I, KC_O,
        KC_LSFT,          KC_X, KC_C, KC_D, KC_V, KC_Z, KC_K, KC_M, KC_COMM, KC_DOT, KC_SLASH,
        KC_LCTL, KC_LGUI, KC_TAB, KC_SPC,                KC_BSPC,             KC_ENT, KC_VOLD, KC_VOLU, MO(2)
		
    ),

	#
    [2] = LAYOUT(
        RESET,   _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______,   BL_TOGG, BL_DEC,  BL_INC,  BL_STEP, _______, _______, _______, _______, _______, G(S(KC_S)),
        _______,          RGB_TOG, RGB_MOD, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD, RGB_VAI, RGB_VAD, _______, C(S(KC_ESC)),
        _______, KC_ASTG, KC_ASDN, _______,                _______,             KC_ASUP, KC_ASRP, _______, _______
    ),

};

enum myCombos {
	XC_Z,
	IO_ENT,
	COMBO_LENGTH
};

const uint16_t PROGMEM xc_combo[] = {KC_X, KC_C, COMBO_END};
const uint16_t PROGMEM io_combo[] = {KC_I, KC_O, COMBO_END};

combo_t key_combos[] = {
	[XC_Z] = COMBO(xc_combo, KC_Z),
	[IO_ENT] = COMBO(io_combo, KC_ENT),
};

uint16_t COMBO_LEN = COMBO_LENGTH;