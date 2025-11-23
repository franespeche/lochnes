#include "core/cpu6502.h"
#include "core/bus.h"
#include "common/types.h"
#include <bitset>
#include <iostream>

CPU6502::CPU6502(Bus *b) : bus(b) {}

void CPU6502::tick() {
  std::cout << "--------------------------------------------------\n";
  std::cout << "PC: " << std::hex << static_cast<int>(PC) << "\n";

  uint8_t opcode = bus->read(PC);
  std::cout << "Opcode: " << std::hex << static_cast<int>(opcode) << "\n";
  execute(opcode);
  PC++;

  std::cout << "P: " << std::bitset<8>(P) << "\n";
}

void CPU6502::reset() {
  SP = 0xFD;
  P = I;

  uint8_t lo = read(RESET_VECTOR_LO);
  uint8_t hi = read(RESET_VECTOR_HI);
  PC = static_cast<uint16_t>(hi) << 8 | lo;
}

void CPU6502::setFlag(uint8_t f, bool cond) {
  if (cond) {
    P |= f;
  }
}

void CPU6502::clearFlag(uint8_t f, bool cond) {
  if (cond) {
    P &= ~f;
  }
}

bool CPU6502::hasFlag(uint8_t f) {
  return (P & f) != 0;
}

uint8_t CPU6502::read(uint16_t address) {
  return bus->read(address);
}

void CPU6502::write(uint16_t address, uint8_t value) {
  bus->write(address, value);
}

void CPU6502::execute(uint8_t opcode) {
  switch (opcode) {
  case 0xA9: // LDA Immediate
    A = read(++PC);
    std::cout << "PC: " << std::hex << static_cast<int>(PC) << '\n';
    std::cout << "LDA: A = " << static_cast<int>(A) << "\n";
    setFlag(Z, A == 0x00);
    setFlag(N, A & (1 << 7));
    break;
  case 0x00: // NOP (No Operation)
    break;
  default:
    std::cerr << "Unknown opcode: " << std::hex << static_cast<int>(opcode)
              << "\n";
  }
}

