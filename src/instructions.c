#include "instructions.h"
#include "logger.h"

// 0x00E0 -> CLS: Clear the screen
void cls(Chip8 *c8) {
  memset(c8->buffer, 0, sizeof(c8->buffer));
  c8->draw = true;
  c8->pc += 0x2;
}

// 0x00EE -> RET: Return from a subroutine
int ret(Chip8 *c8) {
  if (c8->sp <= 0) {
    log_error("Error: Stack underflow in RET instruction.");
    return ERR;
  }

  c8->pc = c8->stack[--c8->sp];
  c8->pc += 0x2;
  return SUCCESS;
}

// 0x0NNN -> SYS: Jump to address
void sys_addr(Chip8 *c8) { c8->pc = c8->opcode & 0x0FFF; }

// 0x2NNN -> CALL: Make a subroutine call
int call_addr(Chip8 *c8) {
  uint16_t nnn;

  if ((c8->sp + 1) >= STACKSIZE) {
    log_error("Error: Stack overflow in Subroutine call.");
    return ERR;
  }

  c8->stack[c8->sp++] = c8->pc;
  nnn = c8->opcode & 0x0FFF;
  c8->pc = nnn;
  return SUCCESS;
}

// 0x1NNN -> JMP: Jump to address
void jmp_addr(Chip8 *c8) { c8->pc = c8->opcode & 0x0FFF; }

// 0x3XKK -> SE: Skip next instruction if Vx == kk
void se_vx_byte(Chip8 *c8) {
  uint8_t x, kk;

  x = (c8->opcode & 0x0F00) >> 8;
  kk = (c8->opcode & 0x00FF);
  if (c8->registers[x] == kk)
    c8->pc += 0x2;
  c8->pc += 0x2;
}

// 0x4XKK -> SNE: Skip next instruction if Vx != kk
void sne_vx_byte(Chip8 *c8) {
  uint8_t x, kk;

  x = (c8->opcode & 0x0F00) >> 8;
  kk = (c8->opcode & 0x00FF);
  if (c8->registers[x] != kk)
    c8->pc += 0x2;
  c8->pc += 0x2;
}

// 0x5XY0 -> SE: Skip next instruction if Vx == Vy
void se_vx_vy(Chip8 *c8) {
  uint8_t x, y;

  x = (c8->opcode & 0x0F00) >> 8;
  y = (c8->opcode & 0x00F0) >> 4;
  if (c8->registers[x] == c8->registers[y])
    c8->pc += 0x2;
  c8->pc += 0x2;
}

// 0x6XKK -> LD: Set Vx = kk
void ld_vx_byte(Chip8 *c8) {
  uint8_t x, kk;

  x = (c8->opcode & 0x0F00) >> 8;
  kk = (c8->opcode & 0x00FF);
  c8->registers[x] = kk;
  c8->pc += 0x2;
}

// 0x7XKK -> ADD: Set Vx = Vx + kk
void add_vx_byte(Chip8 *c8) {
  uint8_t x, kk;

  x = (c8->opcode & 0x0F00) >> 8;
  kk = (c8->opcode & 0x00FF);
  c8->registers[x] += kk;
  c8->pc += 0x2;
}

// 0x8XY0 -> LD: Set Vx = Vy
void ld_vx_vy(Chip8 *c8) {
  uint8_t x, y;

  x = (c8->opcode & 0x0F00) >> 8;
  y = (c8->opcode & 0x00F0) >> 4;
  c8->registers[x] = c8->registers[y];
  c8->pc += 0x2;
}

// 0x8XY1 -> OR: Set Vx = Vx | Vy
void or_vx_vy(Chip8 *c8) {
  uint8_t x, y;

  x = (c8->opcode & 0x0F00) >> 8;
  y = (c8->opcode & 0x00F0) >> 4;
  c8->registers[x] |= c8->registers[y];
  c8->registers[0xF] = 0;
  c8->pc += 0x2;
}

// 0x8XY2 -> AND: Set Vx = Vx & Vy
void and_vx_vy(Chip8 *c8) {
  uint8_t x, y;

  x = (c8->opcode & 0x0F00) >> 8;
  y = (c8->opcode & 0x00F0) >> 4;
  c8->registers[x] &= c8->registers[y];
  c8->registers[0xF] = 0;
  c8->pc += 0x2;
}

// 0x8XY3 -> XOR: Set Vx = Vx ^ Vy
void xor_vx_vy(Chip8 *c8) {
  uint8_t x, y;

  x = (c8->opcode & 0x0F00) >> 8;
  y = (c8->opcode & 0x00F0) >> 4;
  c8->registers[x] ^= c8->registers[y];
  c8->registers[0xF] = 0;
  c8->pc += 0x2;
}

// 0x8XY4 -> ADD: Set Vx = Vx + Vy
void add_vx_vy(Chip8 *c8) {
  uint8_t x, y;

  x = (c8->opcode & 0x0F00) >> 8;
  y = (c8->opcode & 0x00F0) >> 4;

  if ((c8->registers[x] + c8->registers[y]) > 0xFF)
    c8->registers[0xF] = 1;
  else
    c8->registers[0xF] = 0;

  c8->registers[x] = (c8->registers[x] + c8->registers[y]) & 0xFF;
  c8->pc += 0x2;
}

// 0x8XY5 -> SUB: Set Vx = Vx - Vy
void sub_vx_vy(Chip8 *c8) {
  uint8_t x, y;

  x = (c8->opcode & 0x0F00) >> 8;
  y = (c8->opcode & 0x00F0) >> 4;

  if (c8->registers[x] > c8->registers[y])
    c8->registers[0xF] = 1;
  else
    c8->registers[0xF] = 0;

  c8->registers[x] = (c8->registers[x] - c8->registers[y]);
  c8->pc += 0x2;
}

// 0x8XY6 -> SHR: Set Vx = Vx >> 1
void shr_vx(Chip8 *c8) {
  uint8_t x, y;

  x = (c8->opcode & 0x0F00) >> 8;
  y = (c8->opcode & 0x00F0) >> 4;

  c8->registers[x] = c8->registers[y];
  c8->registers[0xF] = c8->registers[x] & 0x1;
  c8->registers[x] >>= 1;
  c8->pc += 0x2;
}

// 0x8XY7 -> SUBN: Set Vx = Vy - Vx
void subn_vx_vy(Chip8 *c8) {
  uint8_t x, y;

  x = (c8->opcode & 0x0F00) >> 8;
  y = (c8->opcode & 0x00F0) >> 4;

  if (c8->registers[y] > c8->registers[x])
    c8->registers[0xF] = 1;
  else
    c8->registers[0xF] = 0;

  c8->registers[x] = (c8->registers[y] - c8->registers[x]);
  c8->pc += 0x2;
}

// 0x8XYE -> SHL: Set Vx = Vx << 1
void shl_vx(Chip8 *c8) {
  uint8_t x, y;

  x = (c8->opcode & 0x0F00) >> 8;
  y = (c8->opcode & 0x00F0) >> 4;

  c8->registers[x] = c8->registers[y];
  c8->registers[0xF] = (c8->registers[x] & 0x80) >> 16;
  c8->registers[x] <<= 1;
  c8->pc += 0x2;
}

// 0x9XY0 -> SNE: Skip next instruction if Vx != Vy
void sne_vx_vy(Chip8 *c8) {
  uint8_t x, y;

  x = (c8->opcode & 0x0F00) >> 8;
  y = (c8->opcode & 0x00F0) >> 4;

  if (c8->registers[x] != c8->registers[y])
    c8->pc += 0x2;
  c8->pc += 0x2;
}

// 0xANNN -> LD: Set I = nnn
void ld_i_addr(Chip8 *c8) {
  uint16_t nnn;

  nnn = c8->opcode & 0x0FFF;
  c8->IRegister = nnn;
  c8->pc += 0x2;
}

// 0xBNNN -> JP: Jump to V0 + nnn
void jp_v0_addr(Chip8 *c8) {
  uint16_t nnn;

  nnn = c8->opcode & 0x0FFF;
  c8->pc = nnn + c8->registers[0];
}

// 0xCXKK -> RND: Set Vx = random byte AND kk
void rnd_vx_kk(Chip8 *c8) {
  uint8_t x, kk;

  x = (c8->opcode & 0x0F00) >> 8;
  kk = (c8->opcode & 0x00FF);
  c8->registers[x] = (rand() & 0xFF) & kk;
  c8->pc += 0x2;
}

// 0xDXYN -> DRW: Draw a sprite at (Vx, Vy)
void drw_vx_vy_nibble(Chip8 *c8) {
  uint8_t x, y, height, sprite, x_pos, y_pos;

  x = (c8->opcode & 0x0F00) >> 8;
  y = (c8->opcode & 0x00F0) >> 4;
  height = (c8->opcode & 0x000F);
  c8->registers[0xF] = 0;

  for (int i = 0; i < height; i++) {
    sprite = c8->memory[c8->IRegister + i];
    for (int j = 0; j < 8; j++) {
      if (sprite & (0x80 >> j)) {
        x_pos = (c8->registers[x] + j) % 64;
        y_pos = (c8->registers[y] + i) % 32;

        // Collision
        if (c8->buffer[x_pos + (y_pos * 64)] == 1)
          c8->registers[0xF] = 1;

        c8->buffer[x_pos + (y_pos * 64)] ^= 1;
      }
    }
  }

  c8->draw = true;
  c8->pc += 0x2;
}

// 0xEX9E SKP: Skip next instruction if key with the value of Vx is pressed
void skp_vx(Chip8 *c8) {
  uint8_t x;

  x = (c8->opcode & 0x0F00) >> 8;
  if (c8->keypad[c8->registers[x]])
    c8->pc += 0x2;
  c8->pc += 0x2;
}

// 0xEXA1 -> SKNP: Skip next instruction if key with the value of Vx is not
// pressed
void sknp_vx(Chip8 *c8) {
  uint8_t x;

  x = (c8->opcode & 0x0F00) >> 8;
  if (!c8->keypad[c8->registers[x]])
    c8->pc += 0x2;
  c8->pc += 0x2;
}

// 0xFX07 -> LD: Set Vx = k (Blocking for key press)
void ld_vx_k(Chip8 *c8, int key) {
  uint8_t x;

  x = (c8->opcode & 0x0F00) >> 8;
  if (key > -1) {
    c8->registers[x] = key;
    c8->pc += 0x2;
  }
}

// 0xF0A -> LD: Set Vx = delay_timer
void ld_vx_dt(Chip8 *c8) {
  uint8_t x;

  x = (c8->opcode & 0x0F00) >> 8;
  c8->registers[x] = c8->delay_timer;
  c8->pc += 0x2;
}

// 0xFX15 -> LD: Set delay_timer = Vx
void ld_dt_vx(Chip8 *c8) {
  uint8_t x;

  x = (c8->opcode & 0x0F00) >> 8;
  c8->delay_timer = c8->registers[x];
  c8->pc += 0x2;
}

// 0xFX18 -> LD: Set sound_timer = Vx
void ld_st_vx(Chip8 *c8) {
  uint8_t x;

  x = (c8->opcode & 0x0F00) >> 8;
  c8->sound_timer = c8->registers[x];
  c8->pc += 0x2;
}

// 0xFX1E -> LD: Set I = I + Vx
void add_i_vx(Chip8 *c8) {
  uint8_t x;

  x = (c8->opcode & 0x0F00) >> 8;
  c8->IRegister += c8->registers[x];
  c8->pc += 0x2;
}

// 0xFX29 -> LD: Set I = location of sprite for digit Vx
void ld_f_vx(Chip8 *c8) {
  uint8_t x;

  x = (c8->opcode & 0x0F00) >> 8;
  c8->IRegister = c8->registers[x] * 0x5;
  c8->pc += 0x2;
}

// 0xFX33 -> LD: Store BCD representation of Vx
void ld_b_vx(Chip8 *c8) {
  uint8_t x;

  x = (c8->opcode & 0x0F00) >> 8;
  c8->memory[c8->IRegister] = c8->registers[x] / 100;
  c8->memory[c8->IRegister + 1] = (c8->registers[x] / 10) % 10;
  c8->memory[c8->IRegister + 2] = c8->registers[x] % 10;
  c8->pc += 0x2;
}

// 0xFX55 -> LD: Store registers V0 to Vx in memory
void ld_i_vx(Chip8 *c8) {
  uint8_t x;

  x = (c8->opcode & 0x0F00) >> 8;
  for (int i = 0; i <= x; i++) {
    c8->memory[c8->IRegister++] = c8->registers[i];
  }

  c8->pc += 0x2;
}

// 0xFX65 -> LD: Load registers V0 to Vx from memory
void ld_vx_i(Chip8 *c8) {
  uint8_t x;

  x = (c8->opcode & 0x0F00) >> 8;
  for (int i = 0; i <= x; i++) {
    c8->registers[i] = c8->memory[c8->IRegister++];
  }

  c8->pc += 0x2;
}