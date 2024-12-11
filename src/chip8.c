#include "chip8.h"

/**
 * @brief Allocate memory for a new Chip8 instance and initialize its state.
 *
 * Initializes the Chip8 stack, memory, registers, and keypad state.
 * Loads the sprite data into memory. Initializes the program counter to 0x200,
 * which is the start of program memory. Initializes the stack pointer to 0.
 *
 * @return A pointer to the newly allocated Chip8 instance. Returns NULL if
 * memory allocation fails.
 */
Chip8 *initialize() {
  Chip8 *c8 = NULL;

  c8 = malloc(sizeof(Chip8));
  if (c8 == NULL) {
    log_error("Error: Failed to allocate memory for Chip8 instance.");
    return NULL;
  }

  memset(c8->stack, 0, sizeof(c8->stack));
  memset(c8->memory, 0, sizeof(c8->memory));
  memset(c8->registers, 0, sizeof(c8->registers));
  memset(c8->keypad, 0, sizeof(c8->keypad));

  c8->IRegister = 0;
  c8->opcode = 0;
  c8->pc = 0x200; // Start of program memory
  c8->sp = 0;
  c8->delay_timer = DELAY_TIMER;
  c8->sound_timer = SOUND_TIMER;

  // Load sprite data into memory
  for (int i = 0; i < 0x80; i++) {
    c8->memory[0x0 + i] = sprite_data[i];
  }

  // Init flags
  c8->running = true;
  return c8;
}

/**
 * @brief Load ROM into Chip8 memory starting at address 0x200.
 *
 * This function opens a ROM file and reads its contents into
 * the Chip8's memory starting from the address 0x200. If the file
 * cannot be opened, it returns an error status.
 *
 * @param c8 The Chip8 instance to load the ROM into.
 * @param rom_filename The name of the ROM file to load.
 * @return Status of the operation (0 -> Success, 1 -> Error).
 */
int load_rom(Chip8 *c8, const char *rom_filename) {
  char ch;
  FILE *fp = NULL;

  log_info(fmt("Loading ROM: %s", rom_filename));

  fp = fopen(rom_filename, "r");
  if (fp == NULL) {
    log_error(fmt("Failed to open ROM file: %s", rom_filename));
    return ERR;
  }

  int index = 0x200;
  while (!feof(fp)) {
    ch = getc(fp);
    c8->memory[index++] = ch;
  }
  fclose(fp);

  log_info(fmt("Loaded ROM: %s", rom_filename));
  return SUCCESS;
}

/**
 * @brief Resets the Chip8 instance to its initial state.
 *
 * This function initializes the Chip8 system by clearing the stack,
 * memory, registers, and keypad state. It sets the I register,
 * opcode, program counter, and stack pointer to their default
 * starting values. The key_pressed flag is also reset to false.
 *
 * @param c8 A pointer to the Chip8 instance to reset.
 */
void reset(Chip8 *c8) {
  memset(c8->stack, 0, sizeof(c8->stack));
  memset(c8->registers, 0, sizeof(c8->registers));
  memset(c8->keypad, 0, sizeof(c8->keypad));
  memset(c8->buffer, 0, sizeof(c8->buffer));

  c8->IRegister = 0;
  c8->opcode = 0;
  c8->pc = 0x200;
  c8->sp = 0;
}

/**
 * @brief Fetches the next opcode from memory and stores it in the Chip8
 * instance.
 *
 * This function fetches the next two bytes from memory and stores them in the
 * Chip8 instance's opcode field. It then returns 1 if the opcode was not zero,
 * indicating that the opcode was successfully fetched and is ready to be
 * executed.
 *
 * @param c8 A pointer to the Chip8 instance.
 * @return 1 if the opcode was successfully fetched, 0 if the opcode was zero.
 */
int fetch_opcode(Chip8 *c8) {
  c8->opcode = (c8->memory[c8->pc] << 8) | c8->memory[c8->pc + 1];

  log_info(fmt("Fetched instruction: %04X", c8->opcode));
  return (c8->opcode != 0x0);
}

/**
 * Executes the current opcode stored in the Chip8 system.
 *
 * This function decodes the opcode and performs the appropriate
 * operation based on the Chip8 instruction set. It updates the
 * program counter and other registers as necessary to reflect
 * the result of the executed instruction.
 *
 * @param c8 A pointer to the Chip8 instance containing the opcode
 *           and system state.
 * @return SUCCESS if the instruction was executed successfully,
 *         ERR if an error occurred (e.g., stack overflow/underflow).
 */
int execute_instruction(Chip8 *c8) {
  switch (c8->opcode & 0xF000) {
  case 0x0000:
    if (c8->opcode == 0x00E0) {
      cls(c8);
    } else if (c8->opcode == 0x00EE) {
      ret(c8);
    } else {
      sys_addr(c8);
    }
    break;

  case 0x1000:
    jmp_addr(c8);
    break;
  case 0x2000:
    call_addr(c8);
    break;
  case 0x3000:
    se_vx_byte(c8);
    break;
  case 0x4000:
    sne_vx_byte(c8);
    break;
  case 0x5000:
    se_vx_vy(c8);
    break;
  case 0x6000:
    ld_vx_byte(c8);
    break;
  case 0x7000:
    add_vx_byte(c8);
    break;

  case 0x8000:
    switch (c8->opcode & 0x000F) {
    case 0x0:
      ld_vx_vy(c8);
      break;
    case 0x1:
      or_vx_vy(c8);
      break;
    case 0x2:
      and_vx_vy(c8);
      break;
    case 0x3:
      xor_vx_vy(c8);
      break;
    case 0x4:
      add_vx_vy(c8);
      break;
    case 0x5:
      sub_vx_vy(c8);
      break;
    case 0x6:
      shr_vx(c8);
      break;
    case 0x7:
      subn_vx_vy(c8);
      break;
    case 0xE:
      shl_vx(c8);
      break;
    default:
      log_error(fmt("Unknown opcode: %04X\n", c8->opcode));
      return ERR;
    }
    break;

  case 0x9000:
    sne_vx_vy(c8);
    break;
  case 0xA000:
    ld_i_addr(c8);
    break;
  case 0xB000:
    jp_v0_addr(c8);
    break;
  case 0xC000:
    rnd_vx_kk(c8);
    break;
  case 0xD000:
    drw_vx_vy_nibble(c8);
    break;

  case 0xE000:
    switch (c8->opcode & 0x00FF) {
    case 0x9E:
      skp_vx(c8);
      break;
    case 0xA1:
      sknp_vx(c8);
      break;
    default:
      return ERR;
    }
    break;

  case 0xF000:
    switch (c8->opcode & 0x00FF) {
    case 0x07:
      ld_vx_dt(c8);
      break;
    case 0x0A:
      ld_vx_k(c8);
      break;
    case 0x15:
      ld_dt_vx(c8);
      break;
    case 0x18:
      ld_st_vx(c8);
      break;
    case 0x1E:
      add_i_vx(c8);
      break;
    case 0x29:
      ld_f_vx(c8);
      break;
    case 0x33:
      ld_b_vx(c8);
      break;
    case 0x55:
      ld_i_vx(c8);
      break;
    case 0x65:
      ld_vx_i(c8);
      break;
    default:
      log_error(fmt("Unknown opcode: %04X\n", c8->opcode));
      return ERR;
    }
    break;

  default:
    log_error(fmt("Unknown opcode: %04X\n", c8->opcode));
    return ERR;
  }

  log_info(fmt("Executed instruction: %04X", c8->opcode));
  return SUCCESS;
}

void update_timers(Chip8 *c8) {
  if (c8->delay_timer > 0) {
    c8->delay_timer--;
    c8->sound_timer--;
  } else {
    c8->delay_timer = DELAY_TIMER;
    c8->sound_timer = SOUND_TIMER;
  }
}
