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

// Fetch opcode from memory and store it in the Chip8 instance
void fetch_opcode(Chip8 *c8);

// Execute the current opcode that is stored in the Chip8 instance
int execute_instruction(Chip8 *c8);

// Update the timers of the Chip8 instance
void update_timers(Chip8 *c8);

// Execute instructions for one CPU cycle
void cycle_cpu(Chip8 *c8, int max_cycles);

#endif