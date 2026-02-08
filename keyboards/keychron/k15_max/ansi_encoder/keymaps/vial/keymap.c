/* Copyright 2024 @ Keychron (https://www.keychron.com)
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

enum layers {
    WIN_BASE,
};
// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [WIN_BASE] = LAYOUT_ansi_90(
        KC_MUTE,  KC_ESC,   KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,   KC_INS,             KC_DEL,
        MC_1,     KC_GRV,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,  KC_EQL,   KC_BSPC,            KC_PGUP,
        MC_2,     KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,  KC_RBRC,  KC_BSLS,            KC_PGDN,
        MC_3,     KC_CAPS,  KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,            KC_ENT,             KC_HOME,
        MC_4,     KC_LSFT,            KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,  KC_RSFT,  KC_UP,
        MC_5,     KC_LCTL,  _______,            KC_LALT,  KC_SPC,  MO(_______),                    KC_SPC,             KC_RALT,  KC_RCTL,            KC_LEFT,  KC_DOWN,  KC_RGHT),
};

enum {
    MY_ENCODER_LEFT = QK_USER,
    MY_ENCODER_RIGHT,
};

#if defined(ENCODER_MAP_ENABLE)
    const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
        [WIN_BASE]  = { ENCODER_CCW_CW(MY_ENCODER_LEFT, MY_ENCODER_RIGHT)},
    };
#endif // ENCODER_MAP_ENABLE

bool osm_shift_active = false;

bool is_alt_tab_active = false;

void oneshot_mods_changed_user(uint8_t mods) {
    if (mods & MOD_MASK_SHIFT) {
        osm_shift_active = true;
    } else {
        osm_shift_active = false;
    }
}

bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    hsv_t hsv = {128, 255, 30}; // cyan
    switch(get_highest_layer(layer_state|default_layer_state)) {
        case 1:
            hsv = (hsv_t){191, 255, 130}; // purple
            break;
        case 2:
            hsv = (hsv_t){85, 255, 130}; // green
            break;
        case 3:
            hsv = (hsv_t){36, 255, 130}; // gold
            break;
        case 4:
            hsv = (hsv_t){170, 255, 130}; // blue
            break;
        case 5:
            hsv = (hsv_t){0, 255, 130}; // red
            break;
        case 6:
            hsv = (hsv_t){191, 255, 130}; // purple
            break;
        case 7:
            hsv = (hsv_t){201, 255, 130}; // magenta
            break;
        case 8:
            hsv = (hsv_t){148, 255, 130}; // azure
            break;
    }

    hsv.v = 130;
    rgb_t rgb = hsv_to_rgb(hsv);
    rgb_matrix_set_color_all(rgb.r, rgb.g, rgb.b);

    if (osm_shift_active) {
        rgb_matrix_set_color(22, RGB_WHITE);
        rgb_matrix_set_color(37, RGB_WHITE);
        rgb_matrix_set_color(53, RGB_WHITE);
        rgb_matrix_set_color(68, RGB_WHITE);
        rgb_matrix_set_color(69, RGB_WHITE);
        rgb_matrix_set_color(54, RGB_WHITE);
        rgb_matrix_set_color(38, RGB_WHITE);
        rgb_matrix_set_color(23, RGB_WHITE);
    }
    if (is_caps_word_on()) {
        rgb_matrix_set_color(22, RGB_MAGENTA);
        rgb_matrix_set_color(37, RGB_MAGENTA);
        rgb_matrix_set_color(53, RGB_MAGENTA);
        rgb_matrix_set_color(68, RGB_MAGENTA);
        rgb_matrix_set_color(69, RGB_MAGENTA);
        rgb_matrix_set_color(54, RGB_MAGENTA);
        rgb_matrix_set_color(38, RGB_MAGENTA);
        rgb_matrix_set_color(23, RGB_MAGENTA);
        return false;
    }
    if (is_alt_tab_active) {
        rgb_matrix_set_color(3, RGB_GREEN);
        rgb_matrix_set_color(4, RGB_GREEN);
        rgb_matrix_set_color(5, RGB_GREEN);
        rgb_matrix_set_color(6, RGB_RED);

        rgb_matrix_set_color(7, RGB_RED);
        rgb_matrix_set_color(8, RGB_GREEN);
        rgb_matrix_set_color(9, RGB_GREEN);
        rgb_matrix_set_color(10, RGB_GREEN);
        return false;
    }
    return false;
}

bool caps_word_press_user(uint16_t keycode) {
    switch (keycode) {
        // Keycodes that continue Caps Word, with shift applied.
        case KC_A ... KC_Z:
        case KC_MINS:
        case KC_SLASH: // `-` on German keyboard
            add_weak_mods(MOD_BIT(KC_LSFT));  // Apply shift to next key.
            return true;

            // Keycodes that continue Caps Word, without shifting.
        case KC_1 ... KC_0:
        case KC_BSPC:
        case KC_DEL:
        case KC_UNDS:
            return true;

        default:
            return false;  // Deactivate Caps Word.
    }
}

bool skip_next = false; // One tick on the rotary encoder somehow activated twice -> ignore the second one

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case MY_ENCODER_LEFT:
            if (skip_next) {
                skip_next = false;
                return false;
            }
            skip_next = true;
            register_code(KC_LALT);
            is_alt_tab_active = true;
            register_code(KC_LSFT);
            tap_code(KC_TAB);
            unregister_code(KC_LSFT);
            return false;
        case MY_ENCODER_RIGHT:
            if (skip_next) {
                skip_next = false;
                return false;
            }
            skip_next = true;
            register_code(KC_LALT);
            is_alt_tab_active = true;
            tap_code(KC_TAB);
            return false;
    }

    if (is_alt_tab_active) {
        unregister_code(KC_LALT);
        is_alt_tab_active = false;
        return false;
    }

    switch (keycode) {
        case KC_ESC:
            if (osm_shift_active) {
                clear_oneshot_mods();
                return false;
            }
            break;
        case HYPR_T(KC_Q): // hack to make the "qu" macro work for caps word - not sure whether still necessary
            if (record->tap.count && record->event.pressed) {
                if (is_caps_word_on()) {
                    SEND_STRING(SS_LSFT("qu"));
                } else {
                    tap_code(KC_Q);
                    tap_code(KC_U);
                }
            } else if (record->event.pressed) {
                if (is_caps_word_on()) {
                    SEND_STRING(SS_LSFT("q"));
                } else {
                    tap_code(KC_Q);
                }
            }
            return false;
        case LT(5,KC_F13): // hack to use F13 as alt repeat key
            if (record->tap.count) {
                alt_repeat_key_invoke(&record->event);
                return false;
            }
            break;
        case LT(6,KC_F14): // hack to use F14 as repeat key
            if (record->tap.count) {
                repeat_key_invoke(&record->event);
                return false;
            }
            break;
    }

    return true;
}

