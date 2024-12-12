#include "chip8.h"
#include "debug.h"
#include "keypad.h"
#include "screen.h"
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
  if (chip8 != NULL) {
    load_rom(chip8, rom_filename);
    init_screen(640, 480, 60);
    log_info("System initialised...");
  } else {
    return ERR;
  }

  // Main program loop
  while (chip8->running) {
    if (!chip8->paused) {
      print_sys_info(chip8);
      fetch_opcode(chip8);
      execute_instruction(chip8);
    }

    if (chip8->reset)
      reset(chip8);

    handle_input(chip8);
    update_screen(chip8->buffer);
    update_timers(chip8);
  }

  close_screen();
  free(chip8);
  return SUCCESS;
}
