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

#pragma once
/* Encoder Configuration */
#define ENCODER_DEFAULT_POS 0x3
#define ENCODER_MAP_KEY_DELAY 2

/* SPI configuration for RGB */
#    define DRIVER_COUNT 2
#    define RGB_MATRIX_LED_COUNT 89
#    define DRIVER_CS_PINS { B8, B9 }

#    define SPI_DRIVER SPID1
#    define SPI_SCK_PIN A5
#    define SPI_MISO_PIN A6
#    define SPI_MOSI_PIN A7
#    define SNLED27351_SDB_PIN B7
#    define SNLED27351_SPI_DIVISOR 16

/* Set to infinit, which is use in USB mode by default */
#    define RGB_MATRIX_TIMEOUT RGB_MATRIX_TIMEOUT_INFINITE
/* Allow shutdown of led driver to save power */
#    define RGB_MATRIX_DRIVER_SHUTDOWN_ENABLE
#    define RGB_MATRIX_DRIVER_LOAD_ENABLE
/* Turn off backlight on low brightness to save power */
#    define RGB_MATRIX_BRIGHTNESS_TURN_OFF_VAL 32

/* Caps lock LED */
#define LED_CAPS_LOCK_PIN A13
#define LED_PIN_ON_STATE 1

/* Indications */
#    define DIM_CAPS_LOCK
#    define CAPS_LOCK_INDEX 48
#    define LOW_BAT_IND_INDEX \
        { 81, 83 }

#    define RGB_MATRIX_KEYPRESSES
#    define RGB_MATRIX_FRAMEBUFFER_EFFECTS

#    define RAW_HID_CMD 0xAB

#define MATRIX_IO_DELAY 10

#define BOTH_SHIFTS_TURNS_ON_CAPS_WORD
