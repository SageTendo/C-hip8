# C-hip8: A CHIP-8 Emulator

## Overview

**C-hip8** is a CHIP-8 emulator implemented in C, utilizing the [Raylib](https://www.raylib.com/) library for graphics rendering and input handling. The CHIP-8 is a virtual machine developed in the 1970s to simplify game development on early computers. This project emulates the CHIP-8 system, enabling classic games and programs to run on modern hardware.

## Features

- **Complete CHIP-8 Instruction Set**: Implements all standard CHIP-8 opcodes.
- **Display Rendering**: Uses Raylib for efficient graphical output.
- **Keyboard Input Handling**: Maps the original CHIP-8 keypad to the modern keyboard layout.
- ~**Sound Support**: Emulates the CHIP-8's sound capabilities.~ To be implemented

## Getting Started

### Prerequisites

- **C Compiler**: Ensure you have a C compiler installed (e.g., `gcc`).
- **Raylib Library**: Install the Raylib development library for your platform.

### Installation

1. **Clone the Repository**:

   ```bash
   git clone https://github.com/SageTendo/C-hip8.git
   cd C-hip8
   ```

2. **Install Raylib**:

   Follow the [official Raylib installation guide](https://www.raylib.com/cheatsheet/cheatsheet.html) to set up Raylib on your system.

3. **Build the Emulator**:

   ```bash
   make
   ```

### Running the Emulator

To run the emulator with a CHIP-8 ROM:

```bash
./build/chip8 path/to/rom
```

Replace `path/to/rom` with the actual path to your CHIP-8 game file.

### Keyboard Mapping

The original CHIP-8 keypad is mapped to your keyboard as follows:

```
CHIP-8 Keypad:        Emulator Keypad:
+---+---+---+---+     +---+---+---+---+
| 1 | 2 | 3 | C |     | 1 | 2 | 3 | 4 |
+---+---+---+---+     +---+---+---+---+
| 4 | 5 | 6 | D |     | Q | W | E | R |
+---+---+---+---+     +---+---+---+---+
| 7 | 8 | 9 | E |     | A | S | D | F |
+---+---+---+---+     +---+---+---+---+
| A | 0 | B | F |     | Z | X | C | V |
+---+---+---+---+     +---+---+---+---+
```

### Sample ROMs

For testing purposes, you can find a collection of CHIP-8 ROMs [here](https://github.com/kripod/chip8-roms).

## Acknowledgements

- [Chip8 Technical Reference](http://devernay.free.fr/hacks/chip8/C8TECH10.HTM)
- [Guide to making a CHIP-8 emulator](https://tobiasvl.github.io/blog/write-a-chip-8-emulator/)
- [Raylib Library](https://www.raylib.com/)
