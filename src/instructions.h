#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H

#include "chip8_types.h"

// Function prototypes for CHIP-8 operations
void cls(Chip8 *c8);
int ret(Chip8 *c8);
void sys_addr(Chip8 *c8);
int call_addr(Chip8 *c8);
void jmp_addr(Chip8 *c8);
void se_vx_byte(Chip8 *c8);
void sne_vx_byte(Chip8 *c8);
void se_vx_vy(Chip8 *c8);
void ld_vx_byte(Chip8 *c8);
void add_vx_byte(Chip8 *c8);
void ld_vx_vy(Chip8 *c8);
void or_vx_vy(Chip8 *c8);
void and_vx_vy(Chip8 *c8);
void xor_vx_vy(Chip8 *c8);
void add_vx_vy(Chip8 *c8);
void sub_vx_vy(Chip8 *c8);
void shr_vx(Chip8 *c8);
void subn_vx_vy(Chip8 *c8);
void shl_vx(Chip8 *c8);
void sne_vx_vy(Chip8 *c8);
void ld_i_addr(Chip8 *c8);
void jp_v0_addr(Chip8 *c8);
void rnd_vx_kk(Chip8 *c8);
void drw_vx_vy_nibble(Chip8 *c8);
void skp_vx(Chip8 *c8);
void sknp_vx(Chip8 *c8);
void ld_vx_k(Chip8 *c8);
void ld_vx_dt(Chip8 *c8);
void ld_dt_vx(Chip8 *c8);
void ld_st_vx(Chip8 *c8);
void add_i_vx(Chip8 *c8);
void ld_f_vx(Chip8 *c8);
void ld_b_vx(Chip8 *c8);
void ld_i_vx(Chip8 *c8);
void ld_vx_i(Chip8 *c8);

#endif