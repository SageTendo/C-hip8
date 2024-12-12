#include "keypad.h"
#include "chip8_types.h"

static const uint8_t KEYMAP[16] = {
    KEY_X, KEY_ONE, KEY_TWO, KEY_THREE, KEY_Q,    KEY_W, KEY_E, KEY_A,
    KEY_S, KEY_D,   KEY_Z,   KEY_C,     KEY_FOUR, KEY_R, KEY_F, KEY_V};

void handle_input(Chip8 *c8) {
  // Exit the program
  if (IsKeyPressed(KEY_ESCAPE))
    c8->running = false;

  // Reset program
  if (!c8->paused && IsKeyPressed(KEY_O))
    c8->reset = true;

  // Pause/Resume program
  if (IsKeyPressed(KEY_P))
    c8->paused = !c8->paused;

  for (int i = 0x0; i <= 0xF; i++) {
    if (IsKeyDown(KEYMAP[i]))
      c8->keypad[i] = true;
    else
      c8->keypad[i] = false;
  }
}