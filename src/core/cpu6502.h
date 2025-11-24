#pragma once

#include "common/types.h"
#include <cstdint>

struct Bus;

struct CPU6502;

struct Instruction {
  uint8_t total_cycles;
  void (CPU6502::*execute)(uint8_t cycle);
};

struct CPU6502 : IClockConsumer {
  Bus *bus = nullptr;

  uint8_t A = 0x00;
  uint8_t X = 0x00;
  uint8_t Y = 0x00;
  uint8_t SP = 0x00;    // Stack Pointer ($0100 to $01FF)
  uint8_t P = 0x00;     // Processor Status
  uint16_t PC = 0x0000; // Program Counter

  // Current instruction
  uint8_t opcode = 0;
  uint8_t current_cycle = 0; // Current cycle for the current instruction
  uint8_t total_cycles = 0;  // Total cycles for the current instruction
  uint16_t addr = 0;         // Address for the current instruction
  uint8_t fetched = 0;       // Fetched data for the current instruction

  CPU6502(Bus *b);
  void tick() override;
  void reset();

  // Flags methods
  void set_flag(uint8_t f, bool cond);
  void clear_flag(uint8_t f, bool cond);
  bool has_flag(uint8_t f);

  uint8_t read(uint16_t address);
  void write(uint16_t address, uint8_t value);

  // Instructions
  static Instruction instruction_table[256];
  void init_instruction_table();

  void op_nop(uint8_t cycle);
  void op_lda_imm(uint8_t cycle);
  void op_sta_abs(uint8_t cycle);
};
