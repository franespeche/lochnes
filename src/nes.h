#pragma once

#include <cstdint>
#include <vector>

// Constants -------------------------------------------------------------------

extern const std::uint16_t RESET_VECTOR_LO;
extern const std::uint16_t RESET_VECTOR_HI;

// Status flags ----------------------------------------------------------------

enum StatusFlag {
  C = (1 << 0), // Carry
  Z = (1 << 1), // Zero
  I = (1 << 2), // Interrupt Disable
  D = (1 << 3), // Decimal Mode
  B = (1 << 4), // Break Command
  O = (1 << 5), // Overflow
  N = (1 << 6), // Negative
};

// Clock interface -------------------------------------------------------------

struct IClockConsumer {
  virtual ~IClockConsumer() = default;
  virtual void tick() = 0; // called every master tick
};

// RAM -------------------------------------------------------------------------

struct RAM {
  static constexpr std::uint16_t SIZE = 0x0800; // 2 KB RAM
  std::uint8_t data[SIZE];

  RAM();
};

// ROM -------------------------------------------------------------------------

struct ROM {
  static constexpr std::uint16_t SIZE = 0x4000; // 16 KB PRG
  std::uint8_t data[SIZE];

  ROM();
};

// Bus -------------------------------------------------------------------------

struct Bus {
  RAM ram;
  ROM rom;

  std::uint8_t read(std::uint16_t address);
  void write(std::uint16_t address, std::uint8_t value);
};

// CPU -------------------------------------------------------------------------

struct CPU6502 : IClockConsumer {
  Bus *bus = nullptr;

  std::uint8_t A = 0x00;
  std::uint8_t X = 0x00;
  std::uint8_t Y = 0x00;
  std::uint8_t SP = 0x00;    // Stack Pointer ($0100 to $01FF)
  std::uint8_t P = 0x00;     // Processor Status
  std::uint16_t PC = 0x0000; // Program Counter

  explicit CPU6502(Bus *b);

  // Clock
  void tick() override;

  // Control
  void reset();

  // Flag helpers
  void setFlag(std::uint8_t f, bool cond);
  void clearFlag(std::uint8_t f, bool cond);
  bool hasFlag(std::uint8_t f);

  // Memory access
  std::uint8_t read(std::uint16_t address);
  void write(std::uint16_t address, std::uint8_t value);

  // Execution
  void execute(std::uint8_t opcode);
};

// Master clock ----------------------------------------------------------------

struct Clock {
  std::uint64_t master_cycles = 0;

  void subscribe(IClockConsumer *c);
  void tick();

private:
  std::vector<IClockConsumer *> consumers;
};

// System ----------------------------------------------------------------------
struct System {
  Bus bus;
  CPU6502 cpu;
  Clock clock;

  System();

  void load_rom(const std::vector<std::uint8_t> &data);
  void reset();
  void run();
};
