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

bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    if (is_caps_word_on()) {
        for (uint8_t i = led_min; i < led_max; i = i + 2) {
            rgb_matrix_set_color(i, RGB_WHITE);
        }
        return false;
    }

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
        default:
            return false;
    }

    hsv.v = 130;
    rgb_t rgb = hsv_to_rgb(hsv);
    rgb_matrix_set_color_all(rgb.r, rgb.g, rgb.b);

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
bool is_alt_tab_active = false;
uint16_t alt_tab_timer = 0;

bool is_ctrl_tab_active = false;
uint16_t ctrl_tab_timer = 0;

void matrix_scan_user(void) {
  if (is_alt_tab_active) {
    if (timer_elapsed(alt_tab_timer) > 800) {
      unregister_code(KC_LALT);
      is_alt_tab_active = false;
    }
  }
  if (is_ctrl_tab_active) {
    if (timer_elapsed(ctrl_tab_timer) > 800) {
      unregister_code(KC_LCTL);
      is_ctrl_tab_active = false;
    }
  }
};

bool encoder_update_user(uint8_t index, bool clockwise) {
    if (get_highest_layer(layer_state|default_layer_state) == 5) {
        register_code(KC_LALT);
        if (clockwise) {
            tap_code(KC_RIGHT);
        } else {
            tap_code(KC_LEFT);
        }
        unregister_code(KC_LALT);
    } else if (get_highest_layer(layer_state|default_layer_state) == 3) {
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
        alt_tab_timer = timer_read();
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
        ctrl_tab_timer = timer_read();
    }
    return false;
};
/* ------------- rotary encoder stuff ---------------- */
