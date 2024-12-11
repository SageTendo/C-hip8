#include "debug.h"
#include "chip8_types.h"
#include <stdio.h>
#include <stdlib.h>

int debugger_enabled = 0;
void debugger_init(void) { debugger_enabled = 1; }

void print_sys_info(Chip8 *c8) {
  if (!debugger_enabled)
    return;

  if (c8 == NULL) {
    fprintf(stderr, "Error: Chip8 system is uninitialized.\n");
    return;
  }

  system("clear");

  // Print system information
  printf("===================================\n");
  printf("System Information\n");
  printf("===================================\n");
  printf("OPCODE: 0x%04X\n", c8->opcode);
  printf("PC: 0x%04X\n", c8->pc);
  printf("SP: 0x%04X\n", c8->sp);
  printf("I : 0x%04X\n", c8->IRegister);
  printf("DT: %d\n", c8->delay_timer);
  printf("ST: %d\n", c8->sound_timer);
  printf("===================================\n");

  // Print registers
  printf("Registers\n");
  for (int i = 0; i < 16; i++) {
    printf("V%X: 0x%02X  ", i, c8->registers[i]);
    if ((i + 1) % 4 == 0)
      printf("\n"); // Group by 4 for readability
  }
  printf("===================================\n");

  // Print stack
  printf("Stack\n");
  for (int i = 15; i >= 0; i--) {
    printf("|  %02d: 0x%04X  %s\n", i, c8->stack[i],
           (i == c8->sp) ? "<-- SP" : "");
  }
  printf("===================================\n");

  // Print keypad
  printf("Keypad\n");
  for (int i = 0; i < 16; i++) {
    printf("Key %2d: %s", i, c8->keypad[i] ? "X" : "");
    if ((i + 1) % 4 == 0)
      printf("\n");
  }
  printf("===================================\n");
}