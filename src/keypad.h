#ifndef KEYPAD_H
#define KEYPAD_H

#include "chip8_types.h"
#include "raylib.h"
#include "stdint.h"

void handle_input(Chip8 *c8);
int wait_for_key(Chip8 *c8);

#endif