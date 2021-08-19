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

enum layer_names {
    _QWERTY,
    _LOWER,
    _RAISE,
    _ADJUST
};

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
};

/* Tap dance declarations */
enum {
    TD_BSPACE,
};

// Tap Dance definitions
qk_tap_dance_action_t tap_dance_actions[] = {
    // Tap once for backspace, twice for ctrl + backspace
    [TD_BSPACE] = ACTION_TAP_DANCE_DOUBLE(KC_BSPACE, LCTL(KC_BSPACE)),
};

/* Give the space cadet enter a new name since we will tweak it to work with
 * space */
#define KC_SFTSPC KC_SFTENT

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_QWERTY] = LAYOUT_split_3x7_4(
        KC_TAB,         KC_Q,   KC_W,   KC_F,   KC_P,   KC_B,    KC_LPRN,      KC_RPRN,    KC_J     , KC_L   , KC_U   , KC_Y   , KC_SLASH , KC_EQUAL,
        KC_GESC,         KC_A,   KC_R,   KC_S,   KC_T,   KC_G,    KC_LBRC,      KC_RBRC,    KC_K     , KC_N   , KC_E   , KC_I   , KC_O     , KC_QUOT,
        LCTL_T(KC_BSLS), KC_Z,   KC_X,   KC_C,   KC_D,   KC_V,    MO(_LOWER),   MO(_RAISE),  KC_M     , KC_H   , KC_COMM, KC_DOT , KC_SCOLON, KC_MINS,
                                    KC_LGUI, MO(_ADJUST), TD(TD_BSPACE), KC_DELETE,     KC_ENT, KC_SFTSPC, MO(_ADJUST), KC_RALT
    ),
    [_LOWER] = LAYOUT_split_3x7_4(
        _______, KC_AT,   _______,   _______,  _______, _______, _______,    OP_ARROW, _______, _______, _______, _______, _______, RESET,
        _______, KC_LEFT, KC_DOWN, KC_UP, KC_RGHT, _______, _______,    _______, _______, _______, _______, _______, _______, _______,
        _______, _______,  _______,  _______,  _______, _______, _______,    _______, _______, _______, _______, _______, _______, _______,
                                  _______,  _______, _______, _______,    _______, _______, _______, _______
    ),
    [_RAISE] = LAYOUT_split_3x7_4(
        _______, KC_EXLM, KC_AT, KC_HASH, KC_DLR, KC_PERC, _______,    _______, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, _______,
        _______, KC_1,     KC_2,   KC_3,   KC_4,   KC_5, _______,    _______,   KC_6,   KC_7,   KC_8,   KC_9,   KC_0, _______,
        _______, KC_F1,   KC_F2,  KC_F3,  KC_F4,  KC_F5, _______,    _______,  KC_F6,  KC_F7,  _______,  _______, _______, _______,
                                _______, _______, _______, _______,    _______, _______, _______, _______
    ),
    [_ADJUST] = LAYOUT_split_3x7_4(
        _______, _______, _______, _______, _______, _______, _______,    _______, _______, _______, XP(ue,Ue), _______, _______, _______,
        _______, XP(ae,Ae), _______, XP(ss,ss), _______, _______, _______,    _______, _______, _______, _______, _______, XP(oe,Oe), _______,
        KC_LSHIFT, _______, _______, LCTL(KC_INSERT), _______, LSFT(KC_INSERT), _______,    _______, _______, _______, _______, _______, _______, KC_RSHIFT,
                                   _______, _______, _______, _______,    _______, _______, _______, _______
    )
};

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

