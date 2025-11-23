#pragma once

#include <cstdint>

// Constants
constexpr uint16_t RESET_VECTOR_LO = 0xFFFC;
constexpr uint16_t RESET_VECTOR_HI = 0xFFFD;

// Status flags
enum StatusFlag {
  C = (1 << 0), // Carry
  Z = (1 << 1), // Zero
  I = (1 << 2), // Interrupt Disable
  D = (1 << 3), // Decimal Mode
  B = (1 << 4), // Break Command
  O = (1 << 5), // Overflow
  N = (1 << 6), // Negative
};

// Clock consumer interface
struct IClockConsumer {
  virtual ~IClockConsumer() = default;
  virtual void tick() = 0;
};

