#include "screen.h"
#include "debug.h"

#define SCREEN_WIDTH 64
#define SCREEN_HEIGHT 32

int WIDTH, HEIGHT, x_scale, y_scale;

/**
 * Initialises the Chip8 screen
 *
 * @param W Screen width
 * @param H Screen height
 * @param fps Chip8 framerate
 */
void init_screen(int W, int H, int fps) {
  InitWindow(W, H, "Chip8 Emulator");
  SetTargetFPS(fps);
  ClearBackground(BLACK);

  x_scale = floor(W / SCREEN_WIDTH);
  y_scale = floor(H / SCREEN_HEIGHT);
}

/**
 * Update the grahpics of the screen with the contents of the next frame buffer
 *
 * @param buffer Chip8 frame buffer
 */
void update_screen(uint32_t buffer[]) {
  BeginDrawing();
  for (int x = 0; x < SCREEN_WIDTH; x++) {
    for (int y = 0; y < SCREEN_HEIGHT; y++) {
      if (buffer[x + (y * SCREEN_WIDTH)] == 1)
        DrawRectangle(x * x_scale, y * y_scale, x_scale, y_scale, RAYWHITE);
      else
        DrawRectangle(x * x_scale, y * y_scale, x_scale, y_scale, BLACK);
    }
  }

  if (is_debugger_enabled())
    DrawFPS(0, 0);
  EndDrawing();
}

void close_screen(void) { CloseWindow(); }