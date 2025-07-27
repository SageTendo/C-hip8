#include "chip8.h"
#include "debug.h"
#include "keypad.h"
#include "screen.h"
#include "speaker.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char **argv) {
  char *rom_filename = NULL;
  if (argc < 2) {
    fprintf(stderr, "Not enough arguments provided...\n");
    fprintf(stderr, "Usage: %s <rom> [-d : Debug mode]\n", argv[0]);
    return ERR;
  }

  // Initialize debugger
  if (argc > 2) {
    if (strcmp(argv[2], "-d") == 0) {
      debugger_init();
      logger_init();
    }
  }

  // Setup Chip8 system
  rom_filename = argv[1];
  Chip8 *chip8 = initialize();
  const int FPS = 60;
  if (chip8 != NULL) {
    load_rom(chip8, rom_filename);
    init_screen(640, 480, FPS);
    init_speaker(chip8);
    log_info("System initialised...");
  } else {
    return ERR;
  }

  // Main program loop
  while (chip8->running) {
    BeginDrawing();
    if (!chip8->paused) {
      print_sys_info(chip8);
      cycle_cpu(chip8, FPS);
    }

    if (chip8->reset)
      reset(chip8);

    if (chip8->draw) {
      update_screen(chip8->buffer);
      chip8->draw = false;
    }

    handle_input(chip8);
    handle_sound(chip8);
    update_timers(chip8);
    EndDrawing();
  }

  close_screen();
  close_speaker(chip8);
  free(chip8);
  return SUCCESS;
}
