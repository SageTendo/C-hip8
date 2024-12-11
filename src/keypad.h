#ifndef KEYPAD_H
#define KEYPAD_H

#include "chip8_types.h"
#include "raylib.h"
#include "stdint.h"

bool key_pressed(int keycode);
void handle_input(Chip8 *c8);

#endif