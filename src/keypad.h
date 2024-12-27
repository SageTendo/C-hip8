#ifndef KEYPAD_H
#define KEYPAD_H

#include "chip8_types.h"
#include "raylib.h"
#include "stdint.h"

/// @brief Handle key events and update the Chip8 keypad state
/// @param c8 The Chip8 instance for which to handle events
void handle_input(Chip8 *c8);

/// @brief Listens for a key press and returns the key value
/// @param c8 The Chip8 instance for which to handle events
int wait_for_key(Chip8 *c8);

#endif