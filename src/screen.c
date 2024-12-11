#include "screen.h"

#define SCREEN_WIDTH 64
#define SCREEN_HEIGHT 32
int scale;

void init_screen(int W, int H, int fps) {
  InitWindow(W, H, "Chip8 Emulator");
  SetTargetFPS(fps);
  ClearBackground(BLACK);

  scale = floor(W / SCREEN_WIDTH);
}

void draw_open(void) { BeginDrawing(); }
void draw_close(void) { EndDrawing(); }

void set_pixel(int x, int y, Color color) {
  DrawRectangle(x * scale, y * scale, scale, scale, color);
}

void update_screen(uint32_t buffer[]) {
  draw_open();
  for (int x = 0; x < SCREEN_WIDTH; x++) {
    for (int y = 0; y < SCREEN_HEIGHT; y++) {
      if (buffer[x + (y * SCREEN_WIDTH)] == 1)
        set_pixel(x, y, GREEN);
      else
        set_pixel(x, y, BLACK);
    }
  }
  DrawFPS(0, 0);
  draw_close();
}

void clear_screen(void) { ClearBackground(BLACK); }
bool closeable(void) { return WindowShouldClose(); }
void close_screen(void) { CloseWindow(); }