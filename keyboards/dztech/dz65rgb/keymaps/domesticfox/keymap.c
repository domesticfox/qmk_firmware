#include QMK_KEYBOARD_H


typedef enum {
    TD_NONE,
    TD_UNKNOWN,
    TD_SINGLE_TAP,
    TD_SINGLE_HOLD,
    TD_DOUBLE_TAP,
} td_state_t;

typedef struct {
    bool is_press_action;
    td_state_t state;
} td_tap_t;

enum {
    TD_ETC, // tap: esc, double tap: tilde, hold: caps;
    
};

enum custom_keycodes {
    LOS = SAFE_RANGE, //layout switch with autoshift toggle
};

td_state_t cur_dance(qk_tap_dance_state_t *state);

void etc_finished(qk_tap_dance_state_t *state, void *user_data);
void etc_reset(qk_tap_dance_state_t *state, void *user_data);

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
    case LOS:
        if (record->event.pressed) {
            // when keycode LOS is pressed
			tap_code16(KC_ASTG);
			if (layer_state_is(0)){
				layer_on(1); 
			} 
			else {
				layer_on(1); 
				}
        } else {
            // when keycode LOS is released

        }
        break;
    }
    return true;
};


td_state_t cur_dance(qk_tap_dance_state_t *state) {
    if (state->count == 1) {
        if (!state->pressed) return TD_SINGLE_TAP;
        else return TD_SINGLE_HOLD;
    }

    if (state->count == 2) return TD_DOUBLE_TAP;
    else return TD_UNKNOWN; 
}
	
	static td_tap_t etctap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

void etc_finished(qk_tap_dance_state_t *state, void *user_data) {
    etctap_state.state = cur_dance(state);
    switch (etctap_state.state) {
        case TD_SINGLE_TAP: register_code(KC_ESC); break;
        case TD_SINGLE_HOLD: register_code(KC_CAPS); break;
        case TD_DOUBLE_TAP: register_code16(KC_TILD); break;
		default: break;
    }
}

void etc_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (etctap_state.state) {
        case TD_SINGLE_TAP: unregister_code(KC_X); break;
        case TD_SINGLE_HOLD: unregister_code(KC_CAPS); break;
        case TD_DOUBLE_TAP: unregister_code16(KC_TILD); break;
		default: break;
    }
    etctap_state.state = TD_NONE;
}

qk_tap_dance_action_t tap_dance_actions[] = {
    [TD_ETC] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, etc_finished, etc_reset)
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_65_ansi(
        TD(TD_ETC),        KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, KC_ASTG,
        KC_TAB,         KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS, G(S(KC_S)),
        KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,  C(S(KC_ESC)),
        KC_LSFT,                 KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, KC_UP,   TO(0),
        MO(2),        KC_LGUI, KC_LALT,                            LT(2, KC_SPC),                    KC_LNG1, KC_LNG2,   KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT
    ),
	[1] = LAYOUT_65_ansi(
        TD(TD_ETC),        KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_DEL, KC_ASTG,
        KC_TAB,         KC_Q,    KC_W,  KC_F,    KC_P,    KC_B,    KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN,    KC_LBRC, KC_RBRC, KC_BSLS, G(S(KC_S)),
        KC_BSPC, KC_A,    KC_R,    KC_S,    KC_T,    KC_G,    KC_M,    KC_N,    KC_E,    KC_I,    KC_O, KC_QUOT,          KC_ENT,  C(S(KC_ESC)),
        KC_Z,                 KC_X,    KC_C,    KC_D,    KC_V,    KC_NO,    KC_K,    KC_H,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, KC_UP,   TO(1),
        KC_LCTL,        KC_LGUI, KC_LALT,                            LT(2,KC_SPC),                    KC_RALT, MO(1),   KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT
    ),
    [2] = LAYOUT_65_ansi(
        KC_GESC,        KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_DEL,  KC_HOME,
        _______,        _______, _______, _______, _______, _______, C(KC_Y), _______, _______, _______, _______, _______, _______, _______,   _______,
        _______, C(KC_A), C(KC_S), _______, C(KC_F), _______, _______, _______, _______, _______, _______, _______,          _______, _______,
        KC_LSFT,                 C(KC_Z), C(KC_X), C(KC_C), C(KC_V), _______, _______, _______, _______, _______, _______, _______, KC_VOLU, KC_MUTE,
        _______,        _______, _______,                            _______,                   _______, _______, _______, KC_MPRV, KC_VOLD, KC_MNXT
    )
};

