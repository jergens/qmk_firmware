/*
Copyright 2019 @foostan
Copyright 2020 Drashna Jaelre <@drashna>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[0] = LAYOUT_split_3x6_3(KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_ESC, OSM(MOD_LSFT), KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, KC_LCTL, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_ENT, KC_LALT, TT(1), TT(2), KC_BSPC, KC_SPC, KC_RGUI),
	[1] = LAYOUT_split_3x6_3(KC_GRV, KC_PGUP, KC_HOME, KC_UP, KC_END, KC_LBRC, KC_RBRC, KC_7, KC_8, KC_9, KC_MINS, KC_EQL, KC_LSFT, KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT, KC_LPRN, KC_RPRN, KC_4, KC_5, KC_6, KC_PAST, KC_BSLS, KC_LCTL, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_PDOT, KC_1, KC_2, KC_3, KC_PSLS, KC_ENT, KC_LALT, KC_TRNS, MO(2), KC_DEL, KC_0, KC_RGUI),
	[2] = LAYOUT_split_3x6_3(KC_NO, KC_F9, KC_F10, KC_F11, KC_F12, KC_NO, KC_NO, KC_PSCR, KC_SLCK, KC_PAUS, KC_NO, RESET, KC_NO, KC_F5, KC_F6, KC_F7, KC_F8, KC_NO, KC_NO, KC_INS, KC_HOME, KC_PGUP, KC_NO, KC_NO, KC_NO, KC_F1, KC_F2, KC_F3, KC_F4, KC_NO, KC_NO, KC_DEL, KC_END, KC_PGDN, KC_NO, KC_NO, KC_NO, KC_NO, KC_TRNS, KC_MUTE, KC_VOLD, KC_VOLU)
};

#ifdef OLED_DRIVER_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
  if (!is_master) {
    return OLED_ROTATION_180;  // flips the display 180 degrees if offhand
  }
  return rotation;
}

#define L_BASE 0
#define L_LOWER 2
#define L_RAISE 4
#define L_ADJUST 8

void oled_render_layer_state(void) {
    oled_write_P(PSTR("Layer: "), false);
    switch (layer_state) {
        case L_BASE:
            oled_write_ln_P(PSTR("Letters"), false);
            break;
        case L_LOWER:
            oled_write_ln_P(PSTR("Numbers"), false);
            break;
        case L_RAISE:
            oled_write_ln_P(PSTR("Functions"), false);
            break;
        case L_ADJUST:
        case L_ADJUST|L_LOWER:
        case L_ADJUST|L_RAISE:
        case L_ADJUST|L_LOWER|L_RAISE:
            oled_write_ln_P(PSTR("Adjust"), false);
            break;
    }
}


char keylog_str[24] = {};

const char code_to_name[60] = {
    ' ', ' ', ' ', ' ', 'a', 'b', 'c', 'd', 'e', 'f',
    'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p',
    'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
    '1', '2', '3', '4', '5', '6', '7', '8', '9', '0',
    'R', 'E', 'B', 'T', '_', '-', '=', '[', ']', '\\',
    '#', ';', '\'', '`', ',', '.', '/', ' ', ' ', ' '};

void set_keylog(uint16_t keycode, keyrecord_t *record) {
  char name = ' ';
    if ((keycode >= QK_MOD_TAP && keycode <= QK_MOD_TAP_MAX) ||
        (keycode >= QK_LAYER_TAP && keycode <= QK_LAYER_TAP_MAX)) { keycode = keycode & 0xFF; }
  if (keycode < 60) {
    name = code_to_name[keycode];
  }

  // update keylog
  snprintf(keylog_str, sizeof(keylog_str), "%dx%d, k%2d : %c",
           record->event.key.row, record->event.key.col,
           keycode, name);
}

void oled_render_keylog(void) {
    oled_write(keylog_str, false);
}

void render_bootmagic_status(bool status) {
    /* Show Ctrl-Gui Swap options */
    static const char PROGMEM logo[][2][3] = {
        {{0x97, 0x98, 0}, {0xb7, 0xb8, 0}},
        {{0x95, 0x96, 0}, {0xb5, 0xb6, 0}},
    };
    if (status) {
        oled_write_ln_P(logo[0][0], false);
        oled_write_ln_P(logo[0][1], false);
    } else {
        oled_write_ln_P(logo[1][0], false);
        oled_write_ln_P(logo[1][1], false);
    }
}

void oled_render_logo(void) {
    static const char PROGMEM raw_logo[] = {
        0,  0,  4,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  4, 12, 28, 60,248,248,240,224,192,128,  0,  0,  4,  0,  0,  0,248,255,255,  0,  0,192,255,255,  3,  0,  0,  0,  0,  0,  0,128,  0,  0,  0,  0,  4,  0,  0,  0,  0,  0,  0,  0,  0, 16,  0,  0,  0,  0,  0,  0,  0,  0,  1,  0,  0,  0,  0,  0,  0,  0, 64,  0,  0,  0,  0,  0,  0,  0,  1,  0,  0,  0,255,  0,  0,  0,  0,  0,  0,252,  0,  0,  0,  0,  0,  7,  0,  0,  0,  0,  0,128,127,  0,  0,  0,  0,  0,  0,  0,  0,254,  0,  0,  0,  0,192,127,  0,  0,  0,
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,128,255,255,255,255,255,255,248,  0,  0,  0,  0,  1, 15,255,192,255,  3,  1,  0,  0,  0, 16,  0,  0,  0,224,255, 62,252,128,  0,  0,  0,  0,  0,  0,  8,  0,  0,  0,  0,  0,  0,  0,  0,  2,  0,  0,  0,  0,  0,  0,  4,  0,  0,  0,  0,  0,  0,  0, 64,  0,  0,  0,  0,  0,  0,  0,  7,253,  0,  0,  0,  0,  0,240,  1,  3,  0,  0,  0,240, 30,  0,  0,  0,128,  0,  3,  0,  0,  0,  0,128,  0,  0,  0,  0,  7,120,  0,  0,  0,  1,192,120,  0,  0, 
        0, 15, 62,124,248,240,240,224,224,224,224,224,224,224,240,240,248,252,254,255,255,255,255,127, 63, 31,  3,  0,  0,  0,  1,  0,  0,127, 31,  1,  0,  0,  0,  0,  0,  0,  0,  0,128,255,255,  0,  7,127,192,128,240,254,224,  0,  0,  0,  0,  0,  0,  2,  0,  0,  0,  0,  0,  2,  0,  0,  0,  0,  0,  0,  0,  0,128,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,192,127,  0,  0,  0,  0, 15,  1,128,  0,  0,  0,  0,  7,  0,  0,  0,192,127,  0,  0,  0,  0,  0,248, 15,  0,  0,  0,  0,248,  0,  0,  0,  0,  0,255,  0,  0,  0, 
        0,  0, 32,  0,  0,  1,  3,  7,  7,  7, 15, 15, 15, 15, 15, 15, 15,  7,  7,  7,  3,  1,  0,  0,  0, 32,  0,  0,  0,  0,  0,  0,  0,  0,  0, 64,  0,  0,  0,  2,  0,  0,  0,  0,255,255,  3,  0,  0,  0,  0,  1,  3,255,255,  0,  0,  0,  0,  0,  2,  0,  0,  0,  0,  0,  0,  0,  0,  0,  8,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 32,  0,  0,  0,  0,  0,  1,126,128,  0,  0,  0,  0,  0, 63,224,  0,  0,  0,  0,  0,224,  0,  3,  0,  0,  0,  0,  0,  0, 15,  0,  0,  0,  0,248, 15,  0,  0,  0,  0,  0,  1,  0,  0,  0,
    };
    oled_write_raw_P(raw_logo, sizeof(raw_logo));
}

void oled_task_user(void) {
    if (is_master) {
        oled_render_layer_state();
        oled_render_keylog();
    } else {
        oled_render_logo();
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
    set_keylog(keycode, record);
  }
  return true;
}
#endif // OLED_DRIVER_ENABLE
