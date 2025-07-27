#ifndef SPEAKER_H
#define SPEAKER_H

#include "raylib.h"
#include "chip8.h"

void init_speaker(Chip8 *c8);
void handle_sound(Chip8 *c8);
void close_speaker(Chip8 *c8);

#endif