#include "../src/chip8.h"
#include "../src/debug.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

// Custom assertion function
#define custom_assert(condition, message)                                      \
  if (!(condition)) {                                                          \
    fprintf(stderr, "Assertion failed: %s\n", message);                        \
    print_sys_info(c8); /* Optional: print system state */                     \
    exit(EXIT_FAILURE); /* Terminate the program */                            \
  }

void test_0xxx(Chip8 *c8);
void test_00e0(Chip8 *c8);
void test_00ee(Chip8 *c8);
void test_1xxx(Chip8 *c8);
void test_2xxx(Chip8 *c8);
void test_3xkk(Chip8 *c8);
void test_4xkk(Chip8 *c8);
void test_5xy0(Chip8 *c8);
void test_6xkk(Chip8 *c8);
void test_7xkk(Chip8 *c8);
void test_8xy0(Chip8 *c8);
void test_8xy1(Chip8 *c8);
void test_8xy2(Chip8 *c8);
void test_8xy3(Chip8 *c8);
void test_8xy4(Chip8 *c8);
void test_8xy5(Chip8 *c8);
void test_8xy6(Chip8 *c8);
void test_8xy7(Chip8 *c8);
void test_8xye(Chip8 *c8);
void test_9xy0(Chip8 *c8);
void test_annn(Chip8 *c8);
void test_bnnn(Chip8 *c8);
void test_cxkk(Chip8 *c8);
void test_dxyn(Chip8 *c8);
void test_ex9e(Chip8 *c8);
void test_exa1(Chip8 *c8);
void test_fx07(Chip8 *c8);
void test_fx0a(Chip8 *c8);
void test_fx15(Chip8 *c8);
void test_fx18(Chip8 *c8);
void test_fx1e(Chip8 *c8);
void test_fx29(Chip8 *c8);
void test_fx33(Chip8 *c8);
void test_fx55(Chip8 *c8);
void test_fx65(Chip8 *c8);

int main() {
  srand(1);

  Chip8 *chip8 = initialize();
  if (chip8 == NULL) {
    return ERR;
  }

  test_0xxx(chip8);
  test_00e0(chip8);
  test_00ee(chip8);
  test_1xxx(chip8);
  test_2xxx(chip8);
  test_3xkk(chip8);
  test_4xkk(chip8);
  test_5xy0(chip8);
  test_6xkk(chip8);
  test_7xkk(chip8);
  test_8xy0(chip8);
  test_8xy1(chip8);
  test_8xy2(chip8);
  test_8xy3(chip8);
  test_8xy4(chip8);
  test_8xy5(chip8);
  test_8xy6(chip8);
  test_8xy7(chip8);
  test_8xye(chip8);
  test_9xy0(chip8);
  test_annn(chip8);
  test_bnnn(chip8);
  test_cxkk(chip8);
  test_dxyn(chip8);
  test_ex9e(chip8);
  test_exa1(chip8);
  test_fx07(chip8);
  test_fx0a(chip8);
  test_fx15(chip8);
  test_fx18(chip8);
  test_fx1e(chip8);
  test_fx29(chip8);
  test_fx33(chip8);
  test_fx55(chip8);
  test_fx65(chip8);

  printf("All tests passsed...");

  free(chip8);
  return 0;
}

void test_0xxx(Chip8 *c8) {
  // Set up the opcode for the test
  c8->opcode = 0x0123;
  execute_instruction(c8);
  custom_assert(c8->pc == (c8->opcode & 0x0FFF), "0x0XXX: PC not updated");
  reset(c8);
}

void test_00e0(Chip8 *c8) {
  // TODO: Add test to check if the screen is cleared
  reset(c8);
}

void test_00ee(Chip8 *c8) {
  // Make subroutine call
  c8->opcode = 0x2123;
  execute_instruction(c8);

  // Make return
  c8->opcode = 0x00EE;
  execute_instruction(c8);
  custom_assert(c8->pc == 0x200, "0x00EE: Return failed");
  custom_assert(c8->sp == 0, "0x00EE: Stack pointer not decremented");
  reset(c8);
}

void test_1xxx(Chip8 *c8) {
  // Set up the opcode for the test
  c8->opcode = 0x1123;
  execute_instruction(c8);
  custom_assert(c8->pc == 0x123, "0x1XXX: PC not updated");
  reset(c8);
}

void test_2xxx(Chip8 *c8) {
  uint16_t old_pc;
  int old_sp;

  old_pc = c8->pc;
  old_sp = c8->sp;
  c8->opcode = 0x2123;
  execute_instruction(c8);

  custom_assert(c8->pc == (c8->opcode & 0x0FFF),
                "0x2XXX: PC points to incorrect addr");
  custom_assert(c8->sp == 1, "0x2XXX: Stack pointer not incrmeented");
  custom_assert(c8->stack[old_sp] == old_pc, "0x2XXX: Incorrect addr on stack");
  reset(c8);
}

void test_3xkk(Chip8 *c8) {
  uint16_t old_pc;

  // Test True condition
  old_pc = c8->pc;
  c8->registers[1] = 0x5;
  c8->opcode = 0x3105;
  execute_instruction(c8);
  custom_assert(old_pc + 2 == c8->pc, "0x3105: PC not incremented");
  reset(c8);

  // Test False condition
  c8->registers[1] = 0x5;
  c8->opcode = 0x3101;
  execute_instruction(c8);
  custom_assert(c8->pc == 0x200, "0x3101: PC changed");
  reset(c8);
}

void test_4xkk(Chip8 *c8) {
  uint16_t old_pc;

  // Test True condition
  old_pc = c8->pc;
  c8->registers[1] = 0x5;
  c8->opcode = 0x4106;
  execute_instruction(c8);
  custom_assert(old_pc + 2 == c8->pc, "0x4106: PC not incremented");
  reset(c8);

  // Test False condition
  c8->registers[1] = 0x5;
  c8->opcode = 0x4105;
  execute_instruction(c8);
  custom_assert(c8->pc == 0x200, "0x4101: PC changed");
  reset(c8);
}

void test_5xy0(Chip8 *c8) {
  uint16_t old_pc;

  old_pc = c8->pc;
  c8->opcode = 0x5010;
  execute_instruction(c8);
  custom_assert(old_pc + 2 == c8->pc, "0x5010: PC not incremented");
  reset(c8);
}

void test_6xkk(Chip8 *c8) {
  c8->opcode = 0x6010;
  execute_instruction(c8);

  custom_assert(c8->registers[0] == 0x10, "0x6010: Register not updated");
  reset(c8);
}

void test_7xkk(Chip8 *c8) {
  c8->registers[0] = 0x5;
  c8->opcode = 0x7010;
  execute_instruction(c8);

  custom_assert(c8->registers[0] == 0x15,
                "0x7010: Value not added to register");
  reset(c8);
}

void test_8xy0(Chip8 *c8) {
  c8->registers[0] = 0x5;
  c8->registers[1] = 0xF;
  c8->opcode = 0x8010;
  execute_instruction(c8);

  custom_assert(c8->registers[0] == 0xF,
                "0x801F: Expected value of 0xF in reg 0");
  reset(c8);
}

void test_8xy1(Chip8 *c8) {
  c8->registers[0] = 0x5;
  c8->registers[1] = 0x3;
  c8->opcode = 0x8011;
  execute_instruction(c8);

  custom_assert(c8->registers[0] == (0x5 | 0x3),
                "0x8011: Expected value of (0x5 bit-OR 0x3) in reg 0");
  reset(c8);
}

void test_8xy2(Chip8 *c8) {
  c8->registers[0] = 0x5;
  c8->registers[1] = 0x3;
  c8->opcode = 0x8012;
  execute_instruction(c8);

  custom_assert(c8->registers[0] == (0x5 & 0x3),
                "0x8012: Expected value of (0x5 bit-AND 0x3) in reg 0");
  reset(c8);
}

void test_8xy3(Chip8 *c8) {
  c8->registers[0] = 0x5;
  c8->registers[1] = 0x3;
  c8->opcode = 0x8013;
  execute_instruction(c8);

  custom_assert(c8->registers[0] == (0x5 ^ 0x3),
                "0x8013: Expected value of (0x5 bit-XOR 0x3) in reg 0");
  reset(c8);
}

void test_8xy4(Chip8 *c8) {
  c8->registers[0] = 0x5;
  c8->registers[1] = 0x3;
  c8->opcode = 0x8014;
  execute_instruction(c8);

  custom_assert(c8->registers[0] == 0x8,
                "0x8014: Expected value of (0x5 + 0x3) in reg 0");
  custom_assert(c8->registers[0xF] == 0x0, "0x8014: Overflow flag set");
  reset(c8);

  // Test overflow
  c8->registers[0] = 0xFF;
  c8->registers[1] = 0x3;
  c8->opcode = 0x8014;
  execute_instruction(c8);

  custom_assert(c8->registers[0] == ((0xFF + 0x3) & 0xFF),
                "0x8014 (overflow): Expected value of (0xFF + 0x3) in reg 0");
  custom_assert(c8->registers[0xF] == 0x1, "0x8014: Overflow flag not set");
  reset(c8);
}

void test_8xy5(Chip8 *c8) {
  c8->registers[0] = 0x5;
  c8->registers[1] = 0x3;
  c8->opcode = 0x8015;
  execute_instruction(c8);

  custom_assert(c8->registers[0] == 0x2,
                "0x8015: Expected value of (0x5 - 0x3) in reg 0");
  custom_assert(c8->registers[0xF] == 0x1, "0x8015: Borrow flag not set");
  reset(c8);

  // Test underflow
  c8->registers[0] = 0x3;
  c8->registers[1] = 0xFF;
  c8->opcode = 0x8015;
  execute_instruction(c8);

  custom_assert(c8->registers[0] == ((0x3 - 0xFF) & 0xFF),
                "0x8015 (underflow): Expected value of (0x3 - 0xF) in reg 0");
  custom_assert(c8->registers[0xF] == 0x0, "0x8015: Borrow flag set");
  reset(c8);
}

void test_8xy6(Chip8 *c8) {
  // SHR Vx {, Vy}
  c8->registers[0] = 0x4;
  c8->opcode = 0x8016;
  execute_instruction(c8);

  custom_assert(c8->registers[0] == 0x2,
                "0x8016: Expected value of (0x4 >> 1) in reg 0");
  custom_assert(c8->registers[0xF] == 0x0, "0x8016: Overflow flag set");
  reset(c8);

  // Test overflow
  c8->registers[0] = 0x3;
  c8->opcode = 0x8016;
  execute_instruction(c8);

  custom_assert(c8->registers[0] == 0x1,
                "0x8016 (overflow): Expected value of (0x1 >> 1) in reg 0");
  custom_assert(c8->registers[0xF] == 0x1, "0x8016: Overflow flag not set");
  reset(c8);
}

void test_8xy7(Chip8 *c8) {
  c8->registers[0] = 0x5;
  c8->registers[1] = 0x3;
  c8->opcode = 0x8017;
  execute_instruction(c8);

  custom_assert(c8->registers[0] == 0xFE,
                "0x8017: Expected value of (0x3 - 0x5) = 0xFE in reg 0");
  reset(c8);

  // Test underflow
  c8->registers[0] = 0x3;
  c8->registers[1] = 0xFF;
  c8->opcode = 0x8017;
  execute_instruction(c8);

  custom_assert(c8->registers[0] == 0xFC,
                "0x8017 (underflow): Expected value of (0xFF - 0x3) = 0x02 in "
                "reg 0");
  custom_assert(c8->registers[0xF] == 0x1, "0x8017: Borrow flag not set");
  reset(c8);
}

void test_8xye(Chip8 *c8) {
  c8->registers[0] = 0x5;
  c8->opcode = 0x801E;
  execute_instruction(c8);

  custom_assert(c8->registers[0] == 0xA,
                "0x801E: Expected value of (0x5 << 1) in reg 0");
  custom_assert(c8->registers[0xF] == 0x0, "0x801E: Overflow flag set");

  // Test overflow
  c8->registers[0] = 0xFF;
  c8->opcode = 0x801E;
  execute_instruction(c8);

  custom_assert(c8->registers[0] == 0xFE,
                "0x801E (overflow): Expected value of (0xFF << 1) in reg 0");
  custom_assert(c8->registers[0xF] == 0x1, "0x801E: Overflow flag not set");
  reset(c8);
}

void test_9xy0(Chip8 *c8) {
  c8->registers[0] = 0x5;
  c8->registers[1] = 0x3;
  c8->opcode = 0x9000;
  execute_instruction(c8);

  custom_assert(c8->pc + 2 == 0x202, "0x9000: PC not incremented");
  reset(c8);

  // Test false condition
  c8->registers[0] = 0x5;
  c8->registers[1] = 0x5;
  c8->opcode = 0x9000;
  execute_instruction(c8);

  custom_assert(c8->pc == 0x200, "0x9000: PC incremented");
}

void test_annn(Chip8 *c8) {
  c8->opcode = 0xA123;
  execute_instruction(c8);

  custom_assert(c8->IRegister == 0x123, "0xA000: IRegister not set");
  reset(c8);
}

void test_bnnn(Chip8 *c8) {
  c8->registers[0] = 0xA;
  c8->opcode = 0xB123;
  execute_instruction(c8);

  custom_assert(c8->pc == 0x12D, "0xB000: PC not set to 0x133");
  reset(c8);
}

void test_cxkk(Chip8 *c8) {
  c8->opcode = 0xC123;

  srand(1);
  execute_instruction(c8);
  srand(1);
  custom_assert(c8->registers[1] == 0x23, "0xC000: Reg 1 not correctly set");
  reset(c8);
}

void test_dxyn(Chip8 *c8) {
  // TODO: Add test to check if the screen is updated
  c8->opcode = 0xD123;
}

void test_ex9e(Chip8 *c8) {
  // SKP Vx
  c8->opcode = 0xE09E;
  c8->registers[0] = 0xA;
  c8->keyboard[0xA] = true;
  execute_instruction(c8);

  custom_assert(c8->pc == 0x202, "0xE09E: Key not pressed");
  reset(c8);
}

void test_exa1(Chip8 *c8) {
  // SKNP Vx
  c8->opcode = 0xE0A1;
  c8->registers[0] = 0xA;
  c8->keyboard[0xB] = true;
  execute_instruction(c8);

  custom_assert(c8->pc == 0x202, "0xE0A1: Key pressed");
  reset(c8);
}

void test_fx07(Chip8 *c8) {
  // LD Vx, DT
  c8->opcode = 0xF007;
  execute_instruction(c8);
  custom_assert(c8->registers[0] == 0x0, "0xF007: Reg 0 not correctly set");
  reset(c8);
}

void test_fx0a(Chip8 *c8) {
  // TODO: Add test for waiting for key press
  // c8->opcode = 0xF00A;
  // execute_instruction(c8);
  // // handle_input(c8);
  // print_sys_info(c8);
}

void test_fx15(Chip8 *c8) {
  //  LD DT, Vx
  c8->opcode = 0xF015;
  c8->registers[0] = 0x5;
  execute_instruction(c8);
  custom_assert(c8->delay_timer == c8->registers[0],
                "0xF015: Delay timer not set");
  reset(c8);
}

void test_fx18(Chip8 *c8) {
  // LD ST, Vx
  c8->opcode = 0xF018;
  c8->registers[0] = 0x5;
  execute_instruction(c8);
  custom_assert(c8->sound_timer == c8->registers[0],
                "0xF018: Sound timer not set");
  reset(c8);
}

void test_fx1e(Chip8 *c8) {
  // ADD I, Vx
  c8->registers[0] = 0x5;
  c8->IRegister = 0x10;
  c8->opcode = 0xF01E;
  execute_instruction(c8);
  custom_assert(c8->IRegister == 0x15,
                "0xF01E: IRegister not updated correctly");
  reset(c8);
}

void test_fx29(Chip8 *c8) {
  // LD F, Vx
  c8->opcode = 0xF029;
  c8->registers[0] = 0x0;
  execute_instruction(c8);
  custom_assert(c8->IRegister == 0x0,
                "0xF029: IRegister not set to correct location for '0'");

  c8->opcode = 0xF029;
  c8->registers[0] = 0x5;
  execute_instruction(c8);
  custom_assert(c8->IRegister == 0x19,
                "0xF029: IRegister not set to correct location for '5'");

  c8->opcode = 0xF029;
  c8->registers[0] = 0xA;
  execute_instruction(c8);
  custom_assert(c8->IRegister == 0x32,
                "0xF029: IRegister not set to correct location for 'A'");

  c8->opcode = 0xF029;
  c8->registers[0] = 0xF;
  execute_instruction(c8);
  custom_assert(c8->IRegister == 0x4B,
                "0xF029: IRegister not set to correct location for 'F'");
  reset(c8);
}

void test_fx33(Chip8 *c8) {
  // LD B, Vx
  c8->registers[0] = 123;
  c8->opcode = 0xF033;
  execute_instruction(c8);

  uint8_t hundreds = (c8->registers[0] / 100) % 10;
  uint8_t tens = (c8->registers[0] / 10) % 10;
  uint8_t units = c8->registers[0] % 10;

  custom_assert(c8->memory[c8->IRegister] == hundreds,
                "0xF033: Incorrect hundreds digit");
  custom_assert(c8->memory[c8->IRegister + 1] == tens,
                "0xF033: Incorrect tens digit");
  custom_assert(c8->memory[c8->IRegister + 2] == units,
                "0xF033: Incorrect units digit");
  reset(c8);
}

void test_fx55(Chip8 *c8) {
  // LD [I], Vx
  c8->IRegister = 0x0;
  c8->registers[0] = 0x0;
  c8->registers[1] = 0x1;
  c8->registers[2] = 0x2;
  c8->registers[3] = 0x3;
  c8->registers[4] = 0x4;
  c8->registers[5] = 0x5;
  c8->registers[6] = 0x6;
  c8->registers[7] = 0x7;
  c8->registers[8] = 0x8;
  c8->registers[9] = 0x9;
  c8->registers[10] = 0xA;
  c8->registers[11] = 0xB;
  c8->registers[12] = 0xC;
  c8->registers[13] = 0xD;
  c8->registers[14] = 0xE;
  c8->registers[15] = 0xF;

  // Store V0 to VX in memory starting at address I
  c8->opcode = 0xFF55;
  execute_instruction(c8);

  for (int reg = 0; reg <= 0xF; reg++) {
    custom_assert(c8->memory[c8->IRegister + reg] == c8->registers[reg],
                  "0xF055: Register not stored correctly");
  }
}

void test_fx65(Chip8 *c8) {
  // LD Vx, [I]
  // Load V0 to VX from memory starting at address I
  c8->IRegister = 0x0;
  c8->opcode = 0xFF65;
  execute_instruction(c8);

  for (int reg = 0; reg <= 0xF; reg++) {
    custom_assert(c8->registers[reg] == reg,
                  "0xF065: Register not loaded correctly");
  }
  reset(c8);
}