#include "core/cpu6502.h"
#include "common/types.h"
#include "core/bus.h"
#include <bitset>
#include <iostream>

Instruction CPU6502::instruction_table[256];

void CPU6502::init_instruction_table() {
  // Clear table
  for (int i = 0; i < 256; i++) {
    instruction_table[i].total_cycles = 0;
    instruction_table[i].execute = nullptr;
  }

  instruction_table[0xEA] = {1, &CPU6502::op_nop};
  instruction_table[0xA9] = {2, &CPU6502::op_lda_imm};
}

CPU6502::CPU6502(Bus *b) : bus(b) { init_instruction_table(); }

void CPU6502::tick() {
  std::cout << "--------------------------------------------------------\n";
  std::cout << std::hex << std::uppercase << "PC: " << static_cast<int>(PC)
            << "Val: " << static_cast<int>(read(PC)) << "\n";

  if (current_cycle == 0) {
    std::cout << "\nNEW INSTRUCTION\n";
    opcode = read(PC++);
    Instruction &inst = instruction_table[opcode];
    total_cycles = inst.total_cycles;
    current_cycle = 1;
  } else {
    ++current_cycle;
  }

  Instruction &inst = instruction_table[opcode];

  if (total_cycles == 0) {
    current_cycle = 0;
    return;
  }

  std::cout << " | "
            << "A: $" << static_cast<int>(A) << " | "
            << "X: $" << static_cast<int>(X) << " | "
            << "Y: $" << static_cast<int>(Y) << " | "
            << "SP: $" << static_cast<int>(SP) << " | "
            << "P: $" << static_cast<int>(P);

  std::cout << "\nOpcode: $" << std::hex << std::uppercase
            << static_cast<int>(opcode) << " | "
            << "Cycle: " << static_cast<int>(current_cycle) << " / "
            << static_cast<int>(total_cycles) << "\n";

  if (inst.execute != nullptr)
    (this->*inst.execute)(current_cycle);

  if (current_cycle == total_cycles) {
    current_cycle = 0;
  }
}

void CPU6502::reset() {
  SP = 0xFD;
  P = I;

  uint8_t lo = read(RESET_VECTOR_LO);
  uint8_t hi = read(RESET_VECTOR_HI);
  PC = static_cast<uint16_t>(hi) << 8 | lo;
}

void CPU6502::set_flag(uint8_t f, bool cond) {
  if (cond) {
    P |= f;
  }
}

void CPU6502::clear_flag(uint8_t f, bool cond) {
  if (cond) {
    P &= ~f;
  }
}

bool CPU6502::has_flag(uint8_t f) { return (P & f) != 0; }

uint8_t CPU6502::read(uint16_t address) { return bus->read(address); }

void CPU6502::write(uint16_t address, uint8_t value) {
  bus->write(address, value);
}

// Instructions
void CPU6502::op_nop(uint8_t cycle) { (void)cycle; }
void CPU6502::op_lda_imm(uint8_t cycle) {
  switch (cycle) {
  case 2:
    A = read(PC++);
    set_flag(Z, A == 0);
    set_flag(N, A & 0x80);
    break;
  default:
    break;
  }
}
