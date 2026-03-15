// Copyright 2023 Danny Nguyen (danny@keeb.io)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT_all(
    KC_MUTE,          KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_DEL,  KC_INS,
    KC_F1,   KC_F2,   KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_DEL,  KC_BSPC, KC_HOME,
    KC_F3,   KC_F4,   KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS, KC_END,
    KC_F5,   KC_F6,   KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_NUHS, KC_ENT,  KC_PGUP,
    KC_F7,   KC_F8,   KC_LSFT, KC_NUBS, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, KC_UP,   KC_PGDN,
    KC_F9,   KC_F10,  KC_LCTL, KC_LALT, KC_LGUI, MO(1),   KC_SPC,  KC_SPC,           MO(1),   KC_SPC,  KC_RALT, KC_RCTL, KC_RGUI, KC_LEFT, KC_DOWN, KC_RGHT
  ),

  [1] = LAYOUT_all(
    _______,          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    RGB_HUI, RGB_HUD, QK_GESC, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______, _______, _______,
    RGB_SAI, RGB_SAD, RGB_TOG, RGB_MOD, _______, KC_UP,   _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    RGB_VAI, RGB_VAD, _______, _______, KC_LEFT, KC_DOWN, KC_RGHT, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______, _______, _______, _______, _______, _______, _______
  )
};

enum {
    FIRST_ENCODER_LEFT = QK_USER,
    FIRST_ENCODER_RIGHT
};

#ifdef ENCODER_MAP_ENABLE
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [0] = { ENCODER_CCW_CW(FIRST_ENCODER_RIGHT, FIRST_ENCODER_LEFT), ENCODER_CCW_CW(KC_VOLU, KC_VOLD) },
    [1] = { ENCODER_CCW_CW(FIRST_ENCODER_RIGHT, FIRST_ENCODER_LEFT), ENCODER_CCW_CW(KC_VOLU, KC_VOLD) },
};
#endif

bool osm_shift_active = false;
bool osm_ctl_active = false;
bool osm_ralt_active = false;

bool is_alt_tab_active = false;

void oneshot_mods_changed_user(uint8_t mods) {
    if (mods & MOD_MASK_SHIFT) {
        osm_shift_active = true;
    } else {
        osm_shift_active = false;
    }
    if (mods & MOD_MASK_CTRL) {
        osm_ctl_active = true;
    } else {
        osm_ctl_active = false;
    }
    if (mods & MOD_BIT(KC_RALT)) {
        osm_ralt_active = true;
    } else {
        osm_ralt_active = false;
    }
}

int color_value = 60;

void layer_indicator(void) {
    hsv_t hsv = {128, 255, 30}; // cyan
    switch(get_highest_layer(layer_state|default_layer_state)) {
        case 0:
            return;
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

    hsv.v = color_value;
    rgb_t rgb = hsv_to_rgb(hsv);
    rgb_matrix_set_color_all(rgb.r, rgb.g, rgb.b);
}

bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    layer_indicator();

    if (osm_shift_active) {
        hsv_t c_hsv = (hsv_t){HSV_GREEN};
        c_hsv.v = color_value;
        rgb_t c_rgb = hsv_to_rgb(c_hsv);

        rgb_matrix_set_color(29, c_rgb.r, c_rgb.g, c_rgb.b);
        rgb_matrix_set_color(30, c_rgb.r, c_rgb.g, c_rgb.b);

        rgb_matrix_set_color(98, c_rgb.r, c_rgb.g, c_rgb.b);
        rgb_matrix_set_color(99, c_rgb.r, c_rgb.g, c_rgb.b);
    }
    if (osm_ctl_active) {
        hsv_t c_hsv = (hsv_t){HSV_GREEN};
        c_hsv.v = color_value;
        rgb_t c_rgb = hsv_to_rgb(c_hsv);

        rgb_matrix_set_color(43, c_rgb.r, c_rgb.g, c_rgb.b);
        rgb_matrix_set_color(44, c_rgb.r, c_rgb.g, c_rgb.b);
        rgb_matrix_set_color(111, c_rgb.r, c_rgb.g, c_rgb.b);
    }
    if (osm_ralt_active) {
        hsv_t c_hsv = (hsv_t){HSV_GREEN};
        c_hsv.v = color_value;
        rgb_t c_rgb = hsv_to_rgb(c_hsv);

        rgb_matrix_set_color(109, c_rgb.r, c_rgb.g, c_rgb.b);
        rgb_matrix_set_color(110, c_rgb.r, c_rgb.g, c_rgb.b);
    }
    if (is_caps_word_on()) {
        hsv_t c_hsv = (hsv_t){HSV_MAGENTA};
        c_hsv.v = color_value;
        rgb_t c_rgb = hsv_to_rgb(c_hsv);

        rgb_matrix_set_color(29, c_rgb.r, c_rgb.g, c_rgb.b);
        rgb_matrix_set_color(30, c_rgb.r, c_rgb.g, c_rgb.b);
        rgb_matrix_set_color(31, c_rgb.r, c_rgb.g, c_rgb.b);
        rgb_matrix_set_color(32, c_rgb.r, c_rgb.g, c_rgb.b);
        rgb_matrix_set_color(33, c_rgb.r, c_rgb.g, c_rgb.b);
        rgb_matrix_set_color(35, c_rgb.r, c_rgb.g, c_rgb.b);

        rgb_matrix_set_color(98, c_rgb.r, c_rgb.g, c_rgb.b);
        rgb_matrix_set_color(99, c_rgb.r, c_rgb.g, c_rgb.b);
        rgb_matrix_set_color(100, c_rgb.r, c_rgb.g, c_rgb.b);
        rgb_matrix_set_color(101, c_rgb.r, c_rgb.g, c_rgb.b);
        rgb_matrix_set_color(102, c_rgb.r, c_rgb.g, c_rgb.b);
        rgb_matrix_set_color(103, c_rgb.r, c_rgb.g, c_rgb.b);
    }
    if (is_alt_tab_active) {
        rgb_matrix_set_color(3, RGB_GREEN);
        rgb_matrix_set_color(5, RGB_GREEN);
        rgb_matrix_set_color(6, RGB_RED);

        rgb_matrix_set_color(7, RGB_RED);
        rgb_matrix_set_color(9, RGB_GREEN);
    }

    // disable LDS that are between keys
    rgb_matrix_set_color(37, RGB_OFF);
    rgb_matrix_set_color(38, RGB_OFF);
    rgb_matrix_set_color(106, RGB_OFF);

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
        case FIRST_ENCODER_LEFT:
            if (skip_next) {
                skip_next = false;
                return false;
            }
            skip_next = true;

            if (IS_LAYER_ON(1)) {
                register_code(KC_LCTL);
                register_code(KC_LSFT);
                tap_code(KC_TAB);
                unregister_code(KC_LSFT);
                unregister_code(KC_LCTL);
                return false;
            }

            register_code(KC_LALT);
            is_alt_tab_active = true;
            register_code(KC_LSFT);
            tap_code(KC_TAB);
            unregister_code(KC_LSFT);
            return false;
        case FIRST_ENCODER_RIGHT:
            if (skip_next) {
                skip_next = false;
                return false;
            }
            skip_next = true;

            if (IS_LAYER_ON(1)) {
                register_code(KC_LCTL);
                tap_code(KC_TAB);
                unregister_code(KC_LCTL);
                return false;
            }

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
//        case HYPR_T(KC_Q): // hack to make the "qu" macro work for caps word - not sure whether still necessary
//            if (record->tap.count && record->event.pressed) {
//                if (is_caps_word_on()) {
//                    SEND_STRING(SS_LSFT("qu"));
//                } else {
//                    tap_code(KC_Q);
//                    tap_code(KC_U);
//                }
//            } else if (record->event.pressed) {
//                if (is_caps_word_on()) {
//                    SEND_STRING(SS_LSFT("q"));
//                } else {
//                    tap_code(KC_Q);
//                }
//            }
//            return false;
    }

    return true;
}
