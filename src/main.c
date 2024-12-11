#include "chip8.h"
#include "debug.h"
#include "keypad.h"
#include "screen.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char **argv) {
  char *rom_filename;
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
  Chip8 *chip8 = initialize();
  if (chip8 != NULL) {
    load_rom(chip8, argv[1]);
    init_screen(640, 480, 30);
  } else {
    return ERR;
  }

  // Main program loop
  while (!closeable()) {
    while (chip8->running) {
      print_sys_info(chip8);
      fetch_opcode(chip8);
      execute_instruction(chip8);

      handle_input(chip8);
      {
        // Exit the program
        if (key_pressed(KEY_ESCAPE)) {
          goto terminate;
        }

        // Reset Chip8
        if (key_pressed(KEY_R)) {
          reset(chip8);
        }

        // Toggle running
        if (key_pressed(KEY_P)) {
          chip8->running = !chip8->running;
        }
      }
      // Render buffer
      update_screen(chip8->buffer);
    }

    if (key_pressed(KEY_P)) {
      chip8->running = !chip8->running;
    }

    // Prevent the program from hanging
    update_screen(chip8->buffer);
  }

terminate:
  close_screen();
  free(chip8);
  printf("All systems go...\n");
  return SUCCESS;
}
