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

typedef enum {
	TD_NONE,
	TD_UNKNOWN,
    TD_SINGLE_TAP,
    TD_SINGLE_HOLD,
    TD_DOUBLE_TAP,
    TD_DOUBLE_HOLD,
    TD_DOUBLE_SINGLE_TAP, // Send two single taps
	
} td_state_t;

typedef struct {
    bool is_press_action;
    td_state_t state;
} td_tap_t;


// Tap Dance declarations
enum {
	TD_LY,
};

td_state_t cur_dance(qk_tap_dance_state_t *state);

// For the layers tap dance. Put it here so it can be used in any keymap
void ly_finished(qk_tap_dance_state_t *state, void *user_data);
void ly_reset(qk_tap_dance_state_t *state, void *user_data);




const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

	//colemak
	[0] = LAYOUT(
        KC_ESC,   KC_Q, KC_W, KC_F, KC_P, KC_B, KC_J, KC_L, KC_U, KC_Y, KC_SCLN, KC_QUOT,
        KC_DEL,   KC_A, KC_R,  KC_S,  KC_T, KC_G, KC_M, KC_N, KC_E, KC_I, KC_O,
        KC_LSFT,          KC_X, KC_C, KC_D, KC_V, KC_Z, KC_K, KC_M, KC_COMM, KC_DOT, TD(TD_LY),
        KC_LCTL, KC_LGUI, LT(2, KC_TAB), KC_SPC,                KC_BSPC,             KC_ENT, KC_VOLD, KC_VOLU, MO(4)
		
    ),

	#
	//qwerty
	[1] = LAYOUT(
        KC_ESC,   KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_BSPC,
        KC_CAPS,   KC_A, KC_S,  KC_D,  KC_F, KC_G, KC_H, KC_K, KC_L, KC_SCLN, KC_ENT,
        KC_LSFT,          KC_X, KC_C, KC_D, KC_V, KC_Z, KC_K, KC_M, KC_COMM, KC_DOT, TD(TD_LY),
        KC_LCTL, KC_LGUI, KC_TAB, KC_SPC,                KC_SPC,             KC_HAEN, KC_VOLD, KC_VOLU, MO(4)
		
    ),
	#
	
	//nav
	[2] = LAYOUT(
        KC_F1,   KC_F2, KC_F3, KC_F4, KC_F5, KC_F5, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12,
        KC_1,   KC_2, KC_3,  KC_4,  KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_CAPS,
        KC_LSFT,          KC_X, KC_C, KC_D, KC_V, KC_Z, KC_K, KC_M, KC_COMM, KC_UP, TO(0),
        KC_LCTL, KC_LGUI, KC_TAB, KC_SPC,                KC_SPC,             KC_RALT, KC_LEFT, KC_DOWN, KC_RGHT
		
    ),
	
	//steno
	[3] = LAYOUT(
        KC_ESC,   KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_BSPC,
        KC_CAPS,   KC_A, KC_S,  KC_D,  KC_F, KC_G, KC_H, KC_K, KC_L, KC_SCLN, KC_ENT,
        KC_LSFT,          KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, TD(TD_LY),
        KC_LCTL, KC_LGUI, KC_TAB, _______,                _______,             KC_RALT, KC_VOLD, KC_VOLU, TO(1)
		
    ),
	#
    [4] = LAYOUT(
        RGB_MOD,   _______, RGB_SAD, RGB_VAI, RGB_SAI, _______, _______, _______, _______, _______, _______, C(S(KC_ESC)),
        RGB_TOG,   RGB_HUD, RGB_VAD,  RGB_HUI,  _______, _______, _______, _______, _______, _______, _______,
        _______,          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        RESET, KC_ASTG, KC_ASDN, _______,                _______,             KC_ASUP, KC_ASRP, _______, _______
    ),
};

enum myCombos {
	XC_SNIP,
	IO_ENT,
	COMBO_LENGTH
};

const uint16_t PROGMEM xc_combo[] = {KC_X, KC_C, COMBO_END};
const uint16_t PROGMEM io_combo[] = {KC_I, KC_O, COMBO_END};

combo_t key_combos[] = {
	[XC_SNIP] = COMBO(xc_combo, G(S(KC_S))),
	[IO_ENT] = COMBO(io_combo, (KC_ENT)),
};

uint16_t COMBO_LEN = COMBO_LENGTH;


td_state_t cur_dance(qk_tap_dance_state_t *state) {
    if (state->count == 1) {
        if (!state->pressed) return TD_SINGLE_TAP;
        // Key has not been interrupted, but the key is still held. Means you want to send a 'HOLD'.
        else return TD_SINGLE_HOLD;
    } else if (state->count == 2) {
        // TD_DOUBLE_SINGLE_TAP is to distinguish between typing "pepper", and actually wanting a double tap
        // action when hitting 'pp'. Suggested use case for this return value is when you want to send two
        // keystrokes of the key, and not the 'double tap' action/macro.
        if (state->interrupted) return TD_DOUBLE_SINGLE_TAP;
        else if (state->pressed) return TD_DOUBLE_HOLD;
        else return TD_DOUBLE_TAP;
    } 
	else return TD_UNKNOWN;
}

// Create an instance of 'td_tap_t' for the 'ly' tap dance.
static td_tap_t ly_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

void ly_finished(qk_tap_dance_state_t *state, void *user_data) {
    ly_tap_state.state = cur_dance(state);
    switch (ly_tap_state.state) {
        case TD_SINGLE_TAP: 
		tap_code(KC_SLASH);
		break;
        case TD_SINGLE_HOLD:
		layer_on(2);
		break;
        case TD_DOUBLE_TAP: 
			//check to see if the layer is already on
			if (layer_state_is(1)) {
				//if already set, then switch it off
				layer_off(1);
			} else {
				//if not already set, then switch it on
				layer_on(1);
			}
		break;
        case TD_DOUBLE_HOLD: 
			if (layer_state_is(3)) {
				//if already set, then switch it off
				layer_off(3);
			} else {
				//if not already set, then switch it on
				layer_on(3);
			}
		break;
        // Last case is for fast typing. Assuming your key is `f`:
        // For example, when typing the word `buffer`, and you want to make sure that you send `ff` and not `Esc`.
        // In order to type `ff` when typing fast, the next character will have to be hit within the `TAPPING_TERM`, which by default is 200ms.
        //case TD_DOUBLE_SINGLE_TAP: 
		//	tap_code(KC_SLASH); tap_code(KC_SLASH);
		default:
		break;
    }
}

void ly_reset(qk_tap_dance_state_t *state, void *user_data) {
    if (ly_tap_state.state == TD_SINGLE_HOLD){
			layer_off(1);
	}
    ly_tap_state.state = TD_NONE;
};


// Tap Dance definitions
qk_tap_dance_action_t tap_dance_actions[] = {
	[TD_LY] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, ly_finished, ly_reset) 
};

