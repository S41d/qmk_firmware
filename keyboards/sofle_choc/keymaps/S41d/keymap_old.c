/* Copyright 2023 Brian Low *
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
#include "doggo.h"
#include "spaceship.h"

enum {
    LAYER_MAIN,
    LAYER_SYMB,
    LAYER_MISC,
    LAYER_GAME,
    LAYER_NUMBER,
    LAYER_GAME_INV,
    LAYER_TYPE,
};

enum{
    L_G = LAYER_GAME,
    L_g = LAYER_GAME_INV,
    L_O = LAYER_MISC,
    L_M = LAYER_MAIN,
    L_N = LAYER_NUMBER,
    L_S = LAYER_SYMB,
    L_T = LAYER_TYPE,
};

enum custom_keycodes {
  C_KC_ALT = QK_USER_30,
  C_TAB,
};

static bool custom_ctrl_tab = false;
static bool custom_alt_active = false;
static bool shift_held = false;
static bool game_mode = false;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
    * QWERTY
    * ,-----------------------------------------.                   ,-----------------------------------------.
    * |  `   |   1  |   2  |   3  |   4  |   5  |                   |   6  |   7  |   8  |   9  |   0  |PrtScr|
    * |------+------+------+------+------+------|                   |------+------+------+------+------+------|
    * | Tab  |   Q  |   W  |   E  |   R  |   T  |                   |   Y  |   U  |   I  |   O  |   P  |  \   |
    * |------+------+------+------+------+------|                   |------+------+------+------+------+------|
    * | ESC  |   A  |   S  |   D  |   F  |   G  |-------.   ,-------|   H  |   J  |   K  |   L  |   ;  |  '   |
    * |------+------+------+------+------+------|  Mute |   | Pause |------+------+------+------+------+------|
    * | LGUI |   Z  |   X  |   C  |   V  |   B  |-------|   |-------|   N  |   M  |   ,  |   .  |   /  | RGUI |
    * `-----------------------------------------/       /    \      \-----------------------------------------'
    *            | TT_2 | LALT | LSFT | LSPC | /Enter  /      \BkSpc \  | RSPC | RSFT | RALT | TT_2 |
    *            |      |      |      |      |/       /        \      \ |      |      |      |      |
    *            `----------------------------------'           '------''---------------------------'
    */
    [LAYER_MAIN] = LAYOUT(
        TG(L_T),        KC_1,   KC_2,           KC_3,    KC_4,              KC_5,                                        KC_6,            KC_7,     KC_8,            KC_9,          KC_0,     KC_DEL,
        KC_TAB,         KC_Q,   KC_W,           KC_E,    KC_R,              KC_T,                                        KC_Y,            KC_U,     KC_I,            KC_O,          KC_P,     KC_GRV,
        CTL_T(KC_ESC),  KC_A,   KC_S,  LT(L_N, KC_D),    KC_F,              KC_G,                                        KC_H,            KC_J,     KC_K,            KC_L,          KC_SCLN,  KC_QUOT,
        KC_BSLS,        KC_Z,   KC_X,           KC_C,    KC_V,              KC_B,           KC_SPC,          KC_MUTE,    KC_N,            KC_M,     KC_COMM,         KC_DOT,        KC_SLSH,  TG(L_N),
                                KC_LGUI, MT(MOD_LALT, TG(L_N)), KC_LSFT, LT(L_S, KC_SPC), LT(L_O, KC_ENT), LT(L_O, KC_BSPC),    LT(L_S, KC_SPC), KC_RSFT,  OSM(MOD_RALT),   TG(L_G)
                               // KC_LGUI, KC_LALT, OSM(MOD_LSFT), LT(1, KC_SPC), LT(2, KC_ENT), LT(2, KC_BSPC),   LT(1, KC_SPC),  OSM(MOD_RSFT),     OSM(MOD_RALT),   TG(LAYER_GAME)
    ),
    [LAYER_SYMB] = LAYOUT(
        _______,  KC_F1,     KC_F2,      KC_F3,      KC_F4,      KC_F5,                          KC_F6,      KC_F7,      KC_F8,      KC_F9,    KC_F10,     KC_F11,
        C_TAB,    KC_EXLM,   KC_AT,      KC_HASH,    KC_DLR,     KC_PERC,                        KC_CIRC,    KC_AMPR,    KC_ASTR,    KC_LPRN,  KC_RPRN,    KC_F12,
        _______,  KC_QUES,   KC_LBRC,    KC_LPRN,    KC_LCBR,    KC_EQL,                         KC_EXLM,    KC_RCBR,    KC_RPRN,    KC_RBRC,  KC_COLN,    KC_DQUO,
        _______,  _______,   _______,    KC_UNDS,    KC_MINUS,   KC_PLUS,   _______, _______,    KC_TILD,    KC_PIPE,    KC_LT,      KC_GT,    _______,    _______,
                             _______,    _______,    _______,    KC_SPC,    _______, C(KC_BSPC), KC_SPC,     _______,    _______,    _______
    ),
    [LAYER_MISC] = LAYOUT(
        OS_TOGG,        RGB_M_P,   RGB_M_B,    RGB_M_R,    RGB_M_SW,   _______,                        _______,     _______,    _______,    _______,   _______,   KC_PSCR,
        _______,        _______,   _______,    _______,    RGB_MOD,    RGB_RMOD,                       _______,     UC_NEXT,    _______,    _______,   _______,   _______,
        _______,        _______,   _______,    _______,    RGB_VAI,    RGB_VAD,                        KC_LEFT,     KC_DOWN,    KC_UP,      KC_RIGHT,  _______,   _______,
        _______,        _______,   _______,    _______,    RGB_SPI,    RGB_SPD,   _______,  _______,   _______,     _______,    _______,    _______,   _______,   _______,
                                   _______,    _______,    _______,    _______,   _______,  A(KC_F12), _______,     _______,    _______,    _______
    ),
    [LAYER_GAME] = LAYOUT(
        KC_U,               KC_T,    KC_1,     KC_2,      KC_3,    KC_4,                                                            KC_5,       KC_6,       KC_7,     KC_8,       KC_9,   KC_0,
        KC_TAB,             KC_2,    KC_Q,     KC_W,      KC_E,    KC_R,                                                            KC_T,       KC_Y,       KC_U,     KC_I,       KC_O,   KC_P,
        CTL_T(KC_ESC),      KC_LSFT, KC_A,     KC_S,      KC_D,    KC_F,                                                            KC_G,       KC_H,       KC_J,     KC_K,       KC_L,   KC_SCLN,
        TT(LAYER_GAME_INV), KC_G,    KC_Z,     KC_X,      KC_C,    KC_V,                    KC_MUTE,         KC_MPLY,               KC_B,       KC_N,       KC_M,     KC_COMM,    KC_DOT, KC_SLSH,
                                     KC_LGUI,  KC_LALT,   KC_LALT, KC_SPC, LT(2, KC_ENT),   LT(2, KC_BSPC),  LT(1, KC_SPC),         KC_RSFT,    KC_RALT,  _______
    ),
    [LAYER_GAME_INV] = LAYOUT(
        _______,        KC_9,   KC_8,     KC_7,      KC_6,    KC_5,                                     KC_5,           KC_6,       KC_7,     KC_8,       KC_9,   KC_0,
        KC_TAB,         KC_O,   KC_I,     KC_U,      KC_Y,    KC_T,                                     KC_T,           KC_Y,       KC_U,     KC_I,       KC_O,   KC_P,
        CTL_T(KC_ESC),  KC_L,   KC_K,     KC_J,      KC_H,    KC_G,                                     KC_G,           KC_H,       KC_J,     KC_K,       KC_L,   KC_SCLN,
        _______,        KC_DOT, KC_COMM,  KC_M,      KC_N,    KC_B,         KC_MUTE,          KC_MPLY,  KC_B,           KC_N,       KC_M,     KC_COMM,    KC_DOT, KC_SLSH,
                                KC_LCTL,  KC_LALT,   KC_LALT, KC_SPC, LT(2, KC_ENT),   LT(2, KC_BSPC),  LT(1, KC_SPC),  KC_RSFT,    KC_RALT,  _______
    ),
    [LAYER_NUMBER] = LAYOUT(
        _______,        _______,   _______,    _______,    _______,    _______,                        _______,     KC_NUM,     KC_PSLS,    KC_PAST,   KC_PMNS,   _______,
        _______,        _______,   _______,    _______,    _______,    _______,                        KC_PSLS,     KC_7,       KC_8,       KC_9,      KC_PPLS,   _______,
        _______,        _______,   _______,    _______,    _______,    _______,                        KC_PAST,     KC_4,       KC_5,       KC_6,      KC_PEQL,   _______,
        _______,        _______,   _______,    _______,    _______,    _______,   _______,  _______,   KC_PMNS,     KC_1,       KC_2,       KC_3,      KC_PENT,   _______,
                                   _______,    _______,    _______,    _______,   _______,  _______,   _______,     KC_0,       _______,    _______
    ),
    [LAYER_TYPE] = LAYOUT(
        _______,        KC_1,   KC_2,    KC_3,    KC_4,             KC_5,                                        KC_6,           KC_7,              KC_8,            KC_9,          KC_0,     KC_DEL,
        KC_TAB,         KC_Q,   KC_W,    KC_E,    KC_R,             KC_T,                                        KC_Y,           KC_U,              KC_I,            KC_O,          KC_P,     KC_GRV,
        CTL_T(KC_ESC),  KC_A,   KC_S,    KC_D,    KC_F,             KC_G,                                        KC_H,           KC_J,              KC_K,            KC_L,          KC_SCLN,  KC_QUOT,
        KC_BSLS,        KC_Z,   KC_X,    KC_C,    KC_V,             KC_B,       KC_SPC,        KC_MUTE,          KC_N,           KC_M,              KC_COMM,         KC_DOT,        KC_SLSH,  TG(LAYER_NUMBER),
                                KC_LGUI, KC_LALT, KC_LSFT, LT(1, KC_SPC), LT(2, KC_ENT), LT(2, KC_BSPC),   LT(1, KC_SPC),        KC_RSFT,           OSM(MOD_RALT),   TG(LAYER_GAME)
    )
};


#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    { ENCODER_CCW_CW(KC_BRIU, KC_BRID), ENCODER_CCW_CW(KC_VOLU, KC_VOLD) },
    { ENCODER_CCW_CW(UG_VALU, UG_VALD), ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    { ENCODER_CCW_CW(KC_BRIU, KC_BRID), ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    { ENCODER_CCW_CW(KC_BRIU, KC_BRID), ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    { ENCODER_CCW_CW(KC_BRIU, KC_BRID), ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    { ENCODER_CCW_CW(KC_BRIU, KC_BRID), ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    { ENCODER_CCW_CW(KC_BRIU, KC_BRID), ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
};
#endif

#if defined(TAPPING_TERM_PER_KEY)
uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case CTL_T(KC_ESC):
            return 140;
        case LT(1, KC_SPC):
        case LT(1, KC_APP):
            return 140;
        case C_KC_ALT:
            return 0;
        case MT(MOD_LALT, TG(L_N)):
            return 140;
        default:
            return TAPPING_TERM;
    }
}
#endif

#if defined(QUICK_TAP_TERM_PER_KEY)
uint16_t get_quick_tap_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case OSM(MOD_LSFT):
        case OSM(MOD_RSFT):
        case LT(1, KC_SPC):
            return 0;
        case LT(1, KC_BSPC):
        case RALT_T(KC_BSPC):
            return 100;
        default:
            return QUICK_TAP_TERM;
    }
}
#endif

#if defined(PERMISSIVE_HOLD_PER_KEY)
bool get_permissive_hold(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        default:
            return false;
    }
}
#endif

#ifdef OLED_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    if (is_keyboard_master()) {
        return OLED_ROTATION_270;
    }
    return OLED_ROTATION_0;
}


bool oled_task_user(void) {
    if (is_keyboard_master()) {
        oled_write_P(PSTR("LAYER\n"), false);
        switch (get_highest_layer(layer_state)) {
        case LAYER_MAIN:
            oled_write_ln_P(PSTR("MAIN "), false);
            break;
        case LAYER_SYMB:
            oled_write_ln_P(PSTR("SYMB "), false);
            break;
        case LAYER_MISC:
            oled_write_ln_P(PSTR("MISC "), false);
            break;
        case LAYER_NUMBER:
            oled_write_ln_P(PSTR("NUMB "), false);
            break;
        case LAYER_TYPE:
            oled_write_ln_P(PSTR("TYPE "), false);
            break;
        case LAYER_GAME:
        case LAYER_GAME_INV:
            oled_write_ln_P(PSTR("GAME "), false);
            break;
        default:
            oled_write_ln_P(PSTR("???? "), false);
        }

        if (shift_held) {
            oled_write_ln_P(PSTR("SHIFT"), false);
        } else {
            oled_write_ln_P(PSTR("-----"), false);
        }
        oled_write_ln_P(game_mode           ? PSTR("GAME ") : PSTR("     "), false);
        led_t led_state = host_keyboard_led_state();

        oled_write_ln_P(led_state.num_lock  ? PSTR("NUML ") : PSTR("     "), false);
        oled_write_ln_P(led_state.caps_lock ? PSTR("CAPS ") : PSTR("     "), false);

        render_luna(0, 13);
    } else {
        render_space();
    }
    return false;
}


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (get_mods() == MOD_MASK_SHIFT) {
        tap_code16(KC_CAPS);
        return true;
    }

    switch (keycode) {
    case KC_LSFT:
    case KC_RSFT:
        break;
    case OSM(MOD_LSFT):
    case OSM(MOD_RSFT):
        if (record->event.pressed) {
            if (shift_held) {
                tap_code16(KC_CAPS);
                return false;
            } else {
                shift_held = true;
            }
        } else {
            shift_held = false;
        }
        break;
    case C_KC_ALT:
        custom_alt_active = record->event.pressed;
        if (!custom_alt_active) {
            unregister_mods(MOD_BIT_LALT);
        }
        return false;
    case C_TAB:
        if (record->event.pressed && !custom_ctrl_tab) {
            custom_ctrl_tab = true;
            register_code(KC_LCTL);
            tap_code(KC_TAB);
            return false;
        }
        if (!record->event.pressed && !custom_ctrl_tab) {
            unregister_code(KC_LCTL);
            return false;
        }
        if (record->event.pressed) {
            tap_code(KC_TAB);
            return false;
        }
        return false;
    case LT(1, KC_SPC):
        if (custom_ctrl_tab && !record->event.pressed) {
            unregister_code(KC_LCTL);
            custom_ctrl_tab = false;
        }
        break;
    case CTL_T(KC_ESC):
        if (record->tap.count && record->event.pressed && host_keyboard_led_state().caps_lock) {
            tap_code16(KC_CAPS);
        }
    case KC_LCTL:
    case KC_RCTL:
        isSneaking = record->event.pressed;
        break;
    case KC_SPC:
        isJumping = record->event.pressed;
        if (isJumping) showedJump = false;
        break;
    }

    if (custom_alt_active && record->event.pressed) {
        switch(keycode) {
        case KC_4:

        case KC_C:

        case KC_A:
        case KC_Z:
        case KC_S:

        case KC_E:
        case KC_R:
        case KC_D:
        case KC_F:

        case KC_U:
        case KC_J:
        case KC_H:

        case KC_I:
        case KC_K:

        case KC_O:
        case KC_P:
            register_mods(MOD_BIT_RALT);
            register_code(keycode);
            unregister_mods(MOD_BIT_RALT);
            return false;
        case C_KC_ALT:
            break;
        default:
            register_mods(MOD_BIT_LALT);
        }

    }

    return true;
}


// End of space oled stuff
#endif


void post_process_record_user(uint16_t keycode, keyrecord_t *record) {

    if (record->event.pressed) {
        switch(keycode) {
        case CTL_T(KC_ESC):
            if (game_mode && layer_state_is(LAYER_MAIN)) layer_move(LAYER_GAME);
            break;
        case LT(2, KC_ENT):
            if (game_mode) {
                if (layer_state_is(LAYER_GAME))      layer_move(LAYER_MAIN);
                else if (layer_state_is(LAYER_MAIN)) layer_move(LAYER_GAME);
            }
            break;
        case TG(LAYER_GAME):
            if (record->event.pressed) game_mode = !game_mode;
            break;
        }
    }
}

// void keyboard_post_init_user(void) {
//     rgblight_sethsv_noeeprom(HSV_PINK);
// }
