#pragma once

#include <cstdint>
#include "types.h"

struct Bus;

struct CPU6502 : IClockConsumer {
  Bus *bus = nullptr;

  uint8_t A = 0x00;
  uint8_t X = 0x00;
  uint8_t Y = 0x00;
  uint8_t SP = 0x00;    // Stack Pointer ($0100 to $01FF)
  uint8_t P = 0x00;     // Processor Status
  uint16_t PC = 0x0000; // Program Counter

  CPU6502(Bus *b);
  void tick() override;
  void reset();

  // Flags methods
  void setFlag(uint8_t f, bool cond);
  void clearFlag(uint8_t f, bool cond);
  bool hasFlag(uint8_t f);

  // Memory access methods
  uint8_t read(uint16_t address);
  void write(uint16_t address, uint8_t value);

  void execute(uint8_t opcode);
};

