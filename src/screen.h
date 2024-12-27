#ifndef SCREEN_H
#define SCREEN_H

#include "math.h"
#include "raylib.h"
#include "stdint.h"

void init_screen(int W, int H, int fps);
void close_screen(void);
void update_screen(uint32_t buffer[]);

#endif