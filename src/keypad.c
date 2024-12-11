#include "keypad.h"
#include "chip8_types.h"

static const uint8_t KEYMAP[16] = {
    KEY_X, KEY_ONE, KEY_TWO, KEY_THREE, KEY_Q,    KEY_W, KEY_E, KEY_A,
    KEY_S, KEY_D,   KEY_Z,   KEY_C,     KEY_FOUR, KEY_R, KEY_F, KEY_V};

void handle_input(Chip8 *c8) {
  for (int i = 0x0; i <= 0xF; i++) {
    if (key_pressed(KEYMAP[i])) {
      c8->keypad[i] = true;
    } else {
      c8->keypad[i] = false;
    }
  }
}

bool key_pressed(int keycode) { return IsKeyDown(keycode); }
