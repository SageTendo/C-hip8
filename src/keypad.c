#include "keypad.h"
#include "chip8_types.h"

static const uint8_t KEYMAP[16] = {
    KEY_ONE, KEY_TWO, KEY_THREE, KEY_FOUR, KEY_Q, KEY_W, KEY_E, KEY_R,
    KEY_A,   KEY_S,   KEY_D,     KEY_F,    KEY_Z, KEY_X, KEY_C, KEY_V};

void handle_input(Chip8 *c8) {
  for (int i = 0x0; i <= 0xF; i++) {
    if (key_pressed(KEYMAP[i])) {
      c8->keyboard[i] = true;
    } else {
      c8->keyboard[i] = false;
    }
  }
}

bool key_pressed(int keycode) { return IsKeyPressed(keycode); }