
#include QMK_KEYBOARD_H
#include <stdio.h>
#include "crkbd.h"

// in the future, should use (1U<<_LAYER_NAME) instead, but needs to be moved to keymap,c
#define L_BASE 0
#define L_LOWER 2
#define L_RAISE 4
#define L_ADJUST 8
#define L_ADJUST_TRI 14

char layer_state_str[24];

const char *read_layer_state(void) {
  switch (layer_state)
  {
  case L_BASE:
    snprintf(layer_state_str, sizeof(layer_state_str), "Layer: ALPHA");
    break;
  case L_RAISE:
    snprintf(layer_state_str, sizeof(layer_state_str), "Layer: GAMING");
    break;
  case L_LOWER:
    snprintf(layer_state_str, sizeof(layer_state_str), "Layer: NAV/PAD");
    break;
  case 6:
    snprintf(layer_state_str, sizeof(layer_state_str), "Layer: GAMING");
    break;
  case 12:
    snprintf(layer_state_str, sizeof(layer_state_str), "Layer: AUXILIARY");
    break;
  case L_ADJUST_TRI:
    snprintf(layer_state_str, sizeof(layer_state_str), "Layer: AUXILIARY");
    break;
  default:
    snprintf(layer_state_str, sizeof(layer_state_str), "Layer: Undef-%ld", layer_state);
  }

  return layer_state_str;
}
