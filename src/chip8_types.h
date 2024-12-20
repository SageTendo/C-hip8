#ifndef CHIP8_TYPES_H
#define CHIP8_TYPES_H

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Return codes for function calls
#define SUCCESS 0
#define ERR 1

// Starting address of the program space in memory
#define PROGRAM_MEM 0x200
#define STACKSIZE 16
#define FONTSIZE 80

// IO props
#define SCREEN_WIDTH 64
#define SCREEN_HEIGHT 32

// Timers
#define DELAY_TIMER 60
#define SOUND_TIMER 60

/**
 * Represents a Chip8 system
 *
 * Stack -> 16 * 16-bit array
 * Memory Map:
 **+---------------+= 0xFFF (4095) End of Chip-8 RAM
 *|               |
 *|               |
 *|               |
 *|               |
 *|               |
 *| 0x200 to 0xFFF|
 *|     Chip-8    |
 *| Program / Data|
 *|     Space     |
 *|               |
 *|               |
 *|               |
 *+- - - - - - - -+= 0x600 (1536) Start of ETI 660 Chip-8 programs
 *|               |
 *|               |
 *|               |
 *+---------------+= 0x200 (512) Start of most Chip-8 programs
 *| 0x000 to 0x1FF|
 *| Reserved for  |
 *|  interpreter  |
 *+---------------+= 0x000 (0) Start of Chip-8 RAM
 *
 * Registers:
 * 16 General-Purpose (8-bit)
 * 1 Memory Register (16-bit)
 *
 * opcode -> The current instruction to be executed
 * pc (Program Counter) -> points to the next instruction
 * sp (Stack Pointer) -> ponits to the last memory address on the stack
 */
typedef struct {
  uint16_t stack[16];
  uint8_t memory[4096];
  uint8_t registers[16];
  uint16_t IRegister;
  uint16_t opcode;
  uint16_t pc;
  int sp;
  uint8_t delay_timer;
  uint8_t sound_timer;
  bool keypad[16];
  uint32_t buffer[SCREEN_WIDTH * SCREEN_HEIGHT];

  // Flags
  bool running;
  bool paused;
  bool reset;
  bool key_pressed;
  bool draw;
} Chip8;

// Sprite object
static const uint8_t sprite_data[FONTSIZE] = {
    0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
    0x20, 0x60, 0x20, 0x20, 0x70, // 1
    0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
    0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
    0x90, 0x90, 0xF0, 0x10, 0x10, // 4
    0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
    0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
    0xF0, 0x10, 0x20, 0x40, 0x40, // 7
    0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
    0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
    0xF0, 0x90, 0xF0, 0x90, 0x90, // A
    0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
    0xF0, 0x80, 0x80, 0x80, 0xF0, // C
    0xE0, 0x90, 0x90, 0x90, 0xE0, // D
    0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
    0xF0, 0x80, 0xF0, 0x80, 0x80  // F
};

#endif