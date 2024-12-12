#ifndef CHIP8_H
#include "instructions.h"
#include "logger.h"

#define CHIP8_H

///
/// @brief Initializes a Chip8 instance
/// @return A chip 8 instance
Chip8 *initialize();

/// @brief Reset the Chip8 instance
/// @param c8 A chip 8 instance to reset
void reset(Chip8 *c8);

/// @brief Load ROM into Chip8 RAM
/// @param c8 The Chip8 to load ROM into
/// @param rom_filename The name of the ROM to load into RAM
/// @return Status of the operation (0 -> Success, 1 -> Error)
int load_rom(Chip8 *c8, const char *rom_filename);

void fetch_opcode(Chip8 *c8);
int execute_instruction(Chip8 *c8);
void update_timers(Chip8 *c8);

/// @brief Handle SDL events and update the Chip8 keypad state
/// @param c8 The Chip8 instance for which to handle events
// void handle_input(Chip8 *c8);

#endif