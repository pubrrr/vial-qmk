// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * QWERTY
     * ,-----------------------------------------.                    ,-----------------------------------------.
     * | ESC  |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  |  `   |
     * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
     * | Tab  |   Q  |   W  |   E  |   R  |   T  |                    |   Y  |   U  |   I  |   O  |   P  | Bspc |
     * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
     * | CAPS  |   A  |   S  |   D  |   F  |   G  |-------.    ,-------|   H  |   J  |   K  |   L  |   ;  |  '   |
     * |------+------+------+------+------+------|  Mute |    | Pause |------+------+------+------+------+------|
     * |LShift|   Z  |   X  |   C  |   V  |   B  |-------|    |-------|   N  |   M  |   ,  |   .  |   /  |RShift|
     * `-----------------------------------------/       /     \      \-----------------------------------------'
     *            | LCTL | LALT | LCMD | LGUI | /Enter  /       \Space \  | RGUI | DEL  | RALT | RCTL |
     *            |      |      |      |  LT1 |/       /         \      \ | LT2  |      |      |      |
     *            `----------------------------------'           '------''---------------------------'
     */

    LAYOUT_split_4x6_5(KC_ESC, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_GRV, KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_BSPC, KC_CAPS, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_MUTE, KC_MPLY, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT, KC_LCTL, KC_LALT, KC_LCMD, LT(1, KC_LGUI), KC_ENT, KC_SPC, LT(2, KC_RGUI), KC_DEL, KC_RALT, KC_RCTL)};

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [0] = {ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_MPRV, KC_MNXT)},
};
#endif

bool osm_shift_active = false;

bool is_alt_tab_active = false;
bool is_ctrl_tab_active = false;

void oneshot_mods_changed_user(uint8_t mods) {
    if (mods & MOD_MASK_SHIFT) {
        osm_shift_active = true;
    } else {
        osm_shift_active = false;
    }
}

bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    hsv_t hsv = {0, 255, 255};
    switch(get_highest_layer(layer_state|default_layer_state)) {
        case 1:
            hsv = (hsv_t){128, 255, 130}; // cyan
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
        case 9:
            hsv = (hsv_t){21, 255, 130}; // orange
            break;
        default:
            if (osm_shift_active) {
                rgb_matrix_set_color(3, RGB_WHITE);
                rgb_matrix_set_color(10, RGB_WHITE);
                rgb_matrix_set_color(13, RGB_WHITE);
                rgb_matrix_set_color(33, RGB_WHITE);
                rgb_matrix_set_color(40, RGB_WHITE);
                rgb_matrix_set_color(43, RGB_WHITE);
            }
            if (is_caps_word_on()) {
                rgb_matrix_set_color(3, RGB_WHITE);
                rgb_matrix_set_color(4, RGB_WHITE);
                rgb_matrix_set_color(5, RGB_WHITE);
                rgb_matrix_set_color(6, RGB_WHITE);

                rgb_matrix_set_color(33, RGB_WHITE);
                rgb_matrix_set_color(34, RGB_WHITE);
                rgb_matrix_set_color(35, RGB_WHITE);
                rgb_matrix_set_color(36, RGB_WHITE);
            }
            if (is_alt_tab_active) {
                rgb_matrix_set_color(3, RGB_RED);
                rgb_matrix_set_color(4, RGB_GREEN);
                rgb_matrix_set_color(5, RGB_GREEN);
                rgb_matrix_set_color(6, RGB_GREEN);

                rgb_matrix_set_color(33, RGB_RED);
                rgb_matrix_set_color(34, RGB_GREEN);
                rgb_matrix_set_color(35, RGB_GREEN);
                rgb_matrix_set_color(36, RGB_GREEN);
                return false;
            }
            if (is_ctrl_tab_active) {
                rgb_matrix_set_color(3, RGB_RED);
                rgb_matrix_set_color(4, RGB_BLUE);
                rgb_matrix_set_color(5, RGB_BLUE);
                rgb_matrix_set_color(6, RGB_BLUE);

                rgb_matrix_set_color(33, RGB_RED);
                rgb_matrix_set_color(34, RGB_BLUE);
                rgb_matrix_set_color(35, RGB_BLUE);
                rgb_matrix_set_color(36, RGB_BLUE);
                return false;
            }
            return false;
    }

    hsv.v = 130;
    rgb_t rgb = hsv_to_rgb(hsv);
    rgb_matrix_set_color_all(rgb.r, rgb.g, rgb.b);

    if (osm_shift_active) {
        rgb_matrix_set_color(3, RGB_WHITE);
        rgb_matrix_set_color(10, RGB_WHITE);
        rgb_matrix_set_color(13, RGB_WHITE);
        rgb_matrix_set_color(33, RGB_WHITE);
        rgb_matrix_set_color(40, RGB_WHITE);
        rgb_matrix_set_color(43, RGB_WHITE);
    }
    if (is_caps_word_on()) {
        rgb_matrix_set_color(3, RGB_WHITE);
        rgb_matrix_set_color(4, RGB_WHITE);
        rgb_matrix_set_color(5, RGB_WHITE);
        rgb_matrix_set_color(6, RGB_WHITE);

        rgb_matrix_set_color(33, RGB_WHITE);
        rgb_matrix_set_color(34, RGB_WHITE);
        rgb_matrix_set_color(35, RGB_WHITE);
        rgb_matrix_set_color(36, RGB_WHITE);
        return false;
    }
    if (is_alt_tab_active) {
        rgb_matrix_set_color(3, RGB_RED);
        rgb_matrix_set_color(4, RGB_GREEN);
        rgb_matrix_set_color(5, RGB_GREEN);
        rgb_matrix_set_color(6, RGB_GREEN);

        rgb_matrix_set_color(33, RGB_RED);
        rgb_matrix_set_color(34, RGB_GREEN);
        rgb_matrix_set_color(35, RGB_GREEN);
        rgb_matrix_set_color(36, RGB_GREEN);
        return false;
    }
    if (is_ctrl_tab_active) {
        rgb_matrix_set_color(3, RGB_RED);
        rgb_matrix_set_color(4, RGB_BLUE);
        rgb_matrix_set_color(5, RGB_BLUE);
        rgb_matrix_set_color(6, RGB_BLUE);

        rgb_matrix_set_color(33, RGB_RED);
        rgb_matrix_set_color(34, RGB_BLUE);
        rgb_matrix_set_color(35, RGB_BLUE);
        rgb_matrix_set_color(36, RGB_BLUE);
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

/* ------------- rotary encoder stuff ---------------- */
// https://www.reddit.com/r/MechanicalKeyboards/comments/s52e51/added_alttab_to_my_rotary_encoder_on_my_qmk_board/
bool encoder_update_user(uint8_t index, bool clockwise) {
    if (get_highest_layer(layer_state|default_layer_state) == 5) {
        register_code(KC_LALT);
        if (clockwise) {
            tap_code(KC_RIGHT);
        } else {
            tap_code(KC_LEFT);
        }
        unregister_code(KC_LALT);
    } else if (get_highest_layer(layer_state|default_layer_state) > 2) {
        if (clockwise) {
            tap_code(KC_UP);
            tap_code(KC_UP);
            tap_code(KC_UP);
            tap_code(KC_UP);
            tap_code(KC_UP);
            tap_code(KC_UP);
            tap_code(KC_UP);
            tap_code(KC_UP);
            tap_code(KC_UP);
            tap_code(KC_UP);
        } else {
            tap_code(KC_DOWN);
            tap_code(KC_DOWN);
            tap_code(KC_DOWN);
            tap_code(KC_DOWN);
            tap_code(KC_DOWN);
            tap_code(KC_DOWN);
            tap_code(KC_DOWN);
            tap_code(KC_DOWN);
            tap_code(KC_DOWN);
            tap_code(KC_DOWN);
        }
    } else if (index == 1) {
        register_code(KC_LALT);
        is_alt_tab_active = true;
        if (clockwise) {
            tap_code(KC_TAB);
        } else {
            register_code(KC_LSFT);
            tap_code(KC_TAB);
            unregister_code(KC_LSFT);
        }
    } else if (index == 0) {
        register_code(KC_LCTL);
        is_ctrl_tab_active = true;
        if (clockwise) {
            tap_code(KC_TAB);
        } else {
            register_code(KC_LSFT);
            tap_code(KC_TAB);
            unregister_code(KC_LSFT);
        }
    }
    return false;
};
/* ------------- rotary encoder stuff ---------------- */


bool remember_last_key_user(uint16_t keycode, keyrecord_t* record, uint8_t* remembered_mods) {
    switch (keycode) {
        case KC_F13:
            return false;
        case LT(5,KC_F13):
            return false;
        case LT(6,KC_F14):
            return false;
        case LT(4,KC_R):
            set_last_keycode(KC_R);
            return false;
        case LCTL_T(KC_I):
            set_last_keycode(KC_I);
            return false;
        case LSFT_T(KC_E):
            set_last_keycode(KC_E);
            return false;
        case LALT_T(KC_A):
            set_last_keycode(KC_A);
            return false;
        case RCTL_T(KC_H):
            set_last_keycode(KC_H);
            return false;
        case RSFT_T(KC_T):
            set_last_keycode(KC_T);
            return false;
        case LALT_T(KC_N):
            set_last_keycode(KC_N);
            return false;
        default:
            return true;
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LT(3,KC_ENTER):
            if (is_alt_tab_active) {
                unregister_code(KC_LALT);
                is_alt_tab_active = false;
                return false;
            }
            if (is_ctrl_tab_active) {
                unregister_code(KC_LCTL);
                is_ctrl_tab_active = false;
                return false;
            }
            break;
        case LT(5,KC_F13):
            if (record->tap.count) {
                alt_repeat_key_invoke(&record->event);
                return false;
            }
            break;
        case LT(6,KC_F14):
            if (record->tap.count) {
                repeat_key_invoke(&record->event);
                return false;
            }
            break;
    }

    if (is_alt_tab_active) {
        unregister_code(KC_LALT);
        is_alt_tab_active = false;
    }
    if (is_ctrl_tab_active) {
        unregister_code(KC_LCTL);
        is_ctrl_tab_active = false;
    }

    return true;
}
