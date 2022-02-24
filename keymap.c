/* Copyright 2021 'David Sunshine'
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

#define _MODDH   0
#define _SYMBOL  1
#define _NUMBER  2
#define _ADJUST  3

/* Special defines for the home row keys */
/* Left Hand */
#define MT_A LSFT_T(KC_A)
#define MT_R LCTL_T(KC_R)
#define MT_S LALT_T(KC_S)
#define MT_T LGUI_T(KC_T)
/* Right Hand */
#define MT_N RGUI_T(KC_N)
#define MT_E RALT_T(KC_E)
#define MT_I RCTL_T(KC_I)
#define MT_O RSFT_T(KC_O)

/* Special defines for the thumbs */
#define LT_ENT LT(_SYMBOL, KC_ENT)
#define LT_SPC LT(_NUMBER, KC_SPC)

/* Special defines for German characters */
#define DE_AE XP(ae, Ae)
#define DE_SS XP(ss, ss)
#define DE_UE XP(ue, Ue)
#define DE_OE XP(oe, Oe)

enum unicode_names {
    ae,
    Ae,
    oe,
    Oe,
    ue,
    Ue,
    ss
};

const uint32_t PROGMEM unicode_map[] = {
    [ae] = 0x00E4,
    [Ae] = 0x00C4,
    [oe] = 0x00F6,
    [Oe] = 0x00D6,
    [ue] = 0x00FC,
    [Ue] = 0x00DC,
    [ss] = 0x00DF
};


enum custom_keycodes {
    OP_ARROW = SAFE_RANGE,
    SYMBOL,
    NUMBER,
    ADJUST,
};

LEADER_EXTERNS();

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_MODDH] = LAYOUT_split_3x7_4(
        KC_NO,   KC_Q,    KC_W,    KC_F,     KC_P,   KC_B,   KC_NO,         KC_NO,     KC_J,  KC_L,     KC_U,    KC_Y,    KC_QUOT,  KC_NO,
        KC_NO,   MT_A,    MT_R,    MT_S,     MT_T,   KC_G,   KC_NO,         KC_NO,     KC_K,  MT_N,     MT_E,    MT_I,       MT_O,  KC_NO,
        KC_NO,   KC_Z,    KC_X,    KC_C,     KC_D,   KC_V, KC_HOME,         KC_LEAD,   KC_M,  KC_H,  KC_COMM,  KC_DOT,  KC_SCOLON,  KC_NO,
                                   KC_NO,  KC_ESC, LT_ENT,  KC_TAB,         KC_BSPC, LT_SPC, KC_UP,    KC_NO
    ),
    [_SYMBOL] = LAYOUT_split_3x7_4(
        _______, KC_AT,   KC_EXLM, KC_HASH,  KC_PERC, KC_PIPE,   _______,    _______, KC_MINUS, KC_LCBR, KC_RCBR, OP_ARROW, KC_EQUAL, _______,
        _______, KC_LEFT, KC_DOWN,   KC_UP,  KC_RGHT, KC_DLR,    _______,    _______,  KC_UNDS, KC_LPRN, KC_RPRN, KC_SLASH, KC_QUES,  _______,
        _______, KC_CIRC, _______, KC_TILD,   KC_GRV, KC_BSLASH, _______,    _______,  KC_ASTR, KC_LBRC, KC_RBRC, KC_AMPR,  KC_PLUS,  _______,
                                   _______,  _______, _______,   _______,    KC_DEL,  _______, _______, _______
    ),
    [_NUMBER] = LAYOUT_split_3x7_4(
        _______, _______, _______, _______, _______, _______, _______,    _______, _______, KC_7, KC_8, KC_9, _______, _______,
        _______, _______, _______, _______, _______, _______, _______,    _______,    KC_0, KC_4, KC_5, KC_6, _______, _______,
        _______, _______, _______, _______, _______, _______, _______,    _______, _______, KC_1, KC_2, KC_3, _______, _______,
                                   _______, _______, _______, _______,    _______, _______, _______, _______
    ),
    [_ADJUST] = LAYOUT_split_3x7_4(
        _______,     _______, _______, _______,         _______, _______,         _______,    _______, _______, _______, DE_UE, _______, _______,     _______,
        _______,       DE_AE, _______,   DE_SS,       _______, _______,         _______,    _______, _______, _______, _______,   _______, DE_OE,   _______,
        KC_LSHIFT,   _______, _______, LCTL(KC_INSERT), _______, LSFT(KC_INSERT), _______,    _______, _______, _______, _______,   _______, _______,   KC_RSHIFT,
                                                       _______, _______, _______, _______,    _______, _______, _______, _______
    )
};

/* If _SYMBOL and _NUMBER are active at the same time change to the _ADJUST
 * layer */
layer_state_t layer_state_set_user(layer_state_t state) {
      return update_tri_layer_state(state, _SYMBOL, _NUMBER, _ADJUST);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case OP_ARROW:
            if (record->event.pressed) {
                // When OP_ARROW is pressed
                SEND_STRING("->");
            } else {
                // When OP_ARROW is released
            }
            break;
    }
    return true; // continue normal processing (we did not replace or alter any functionality)
}


void matrix_scan_user(void) {
  LEADER_DICTIONARY() {
    leading = false;
    leader_end();

    SEQ_ONE_KEY(KC_Q) {
      register_code(KC_LGUI);
      register_code(KC_LSFT);
      register_code(KC_Q);
      unregister_code(KC_Q);
      unregister_code(KC_LSFT);
      unregister_code(KC_LGUI);
    }
    SEQ_TWO_KEYS(KC_I, KC_A) {
      register_code(KC_LGUI);
      register_code(KC_1);
      unregister_code(KC_1);
      unregister_code(KC_LGUI);
    }
    SEQ_TWO_KEYS(KC_I, KC_R) {
      register_code(KC_LGUI);
      register_code(KC_2);
      unregister_code(KC_2);
      unregister_code(KC_LGUI);
    }
    SEQ_TWO_KEYS(KC_I, KC_S) {
      register_code(KC_LGUI);
      register_code(KC_3);
      unregister_code(KC_3);
      unregister_code(KC_LGUI);
    }
    SEQ_TWO_KEYS(KC_I, KC_T) {
      register_code(KC_LGUI);
      register_code(KC_4);
      unregister_code(KC_4);
      unregister_code(KC_LGUI);
    }
    SEQ_TWO_KEYS(KC_I, KC_G) {
      register_code(KC_LGUI);
      register_code(KC_5);
      unregister_code(KC_5);
      unregister_code(KC_LGUI);
    }
  }
}
