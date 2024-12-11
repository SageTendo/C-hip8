#ifndef SCREEN_H
#define SCREEN_H

#include "math.h"
#include "raylib.h"
#include "stdint.h"

void init_screen(int W, int H, int fps);
void clear_screen(void);
bool closeable(void);
void close_screen(void);

void draw_open(void);
void draw_close(void);
void update_screen(uint32_t buffer[]);
void draw_rectangle(int x, int y, Color color);
void set_pixel(int x, int y, Color color);

#endif