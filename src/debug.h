#ifndef DEBUG_H
#define DEBUG_H

#include "chip8.h"

/// @brief Initializes the debugger
void debugger_init(void);

/// @return Checks if debugger is enabled
bool is_debugger_enabled(void);

/// @brief Prints system information
/// @param c8 The Chip8 instance to print information for
void print_sys_info(Chip8 *c8);

#endif