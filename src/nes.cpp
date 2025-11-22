#include <iostream>
#include <vector>

uint16_t RESET_VECTOR_LO = 0xFFFC;
uint16_t RESET_VECTOR_HI = 0xFFFD;

enum StatusFlag {
  C = (1 << 0), // Carry
  Z = (1 << 1), // Zero
  I = (1 << 2), // Interrupt Disable
  D = (1 << 3), // Decimal Mode
  B = (1 << 4), // Break Command
  O = (1 << 5), // Overflow
  N = (1 << 6), // Negative
};

struct IClockConsumer {
  virtual ~IClockConsumer() = default;
  virtual void tick() = 0; // called every master tick
};

struct RAM {
  static constexpr uint16_t SIZE = 0x0800; // 2 KB RAM
  uint8_t data[SIZE];

  RAM() {
    for (uint16_t i = 0; i < SIZE; i++) {
      data[i] = 0;
    }
  }
};

// Test ROM with a simple program that loads a value into the accumulator
struct ROM {
  static constexpr uint16_t SIZE = 0x4000; // 16 KB PRG
  uint8_t data[SIZE];

  ROM() {
    for (uint16_t i = 0; i < SIZE; i++) {
      data[i] = 0;
    }
    data[0x0000] = 0xA9; // LDA Immediate
    data[0x0001] = 0x80;
    data[0x0002] = 0xA9; // LDA Immediate
    data[0x0003] = 0x00;
    data[0x0004] = 0xA9; // LDA Immediate
    data[0x0005] = 0xFF;
    data[0x0006] = 0x00; // NOP (No Operation)

    // TODO: check this!
    // Reset vector at CPU 0xFFFC/0xFFFD → ROM offsets 0x3FFC/0x3FFD
    constexpr uint16_t RESET_PC = 0x8000;

    data[0x3FFC] = static_cast<uint8_t>(RESET_PC & 0x00FF);        // low byte
    data[0x3FFD] = static_cast<uint8_t>((RESET_PC >> 8) & 0x00FF); // high byte
  }
};

struct Bus {
  RAM ram;
  ROM rom;

  uint8_t read(uint16_t address) {
    // RAM
    if (address < 0x8000) {
      return ram.data[address];
    }

    // ROM
    std::uint16_t offset = (address - 0x8000) % ROM::SIZE;
    return rom.data[offset];
  }

  void write(uint16_t address, uint8_t value) {
    // RAM
    if (address < 0x8000) {
      ram.data[address] = value;
    }
  }
};

struct Instruction {
  uint8_t opcode;     // Opcode of the instruction
  uint8_t cyclesLeft; // Number of cycles for the instruction
};

struct CPU6502 : IClockConsumer {
  Bus *bus = nullptr;

  uint8_t A = 0x00;
  uint8_t X = 0x00;
  uint8_t Y = 0x00;
  uint8_t SP = 0x00;    // Stack Pointer ($0100 to $01FF)
  uint8_t P = 0x00;     // Processor Status
  uint16_t PC = 0x0000; // Program Counter

  CPU6502(Bus *b) : bus(b) {}

  void tick() {
    uint8_t opcode = bus->read(PC);
    execute(opcode);
    PC++;

    std::cout << "P: " << std::bitset<8>(P) << "\n";
  }

  void reset() {
    SP = 0xFD;
    P = I;

    uint8_t lo = read(RESET_VECTOR_LO);
    uint8_t hi = read(RESET_VECTOR_HI);
    PC = static_cast<uint16_t>(hi) << 8 | lo;
  }

  // Set flag if condition is true
  void setFlag(uint8_t f, bool cond) {
    if (cond) {
      P |= f;
    }
  }
  void clearFlag(uint8_t f, bool cond) {
    if (cond) {
      P &= ~f;
    }
  }
  bool hasFlag(uint8_t f) { return (P & f) != 0; }

  // Memory access methods
  uint8_t read(uint16_t address) { return bus->read(address); }
  void write(uint16_t address, uint8_t value) { bus->write(address, value); }

  void execute(uint8_t opcode) {
    switch (opcode) {
    case 0xAD: {
      uint8_t hi = read(PC++);
      uint8_t lo = read(PC++);
      uint16_t addr = (hi << 8) | lo;
      A = read(addr);
      std::cout << "LDA: A = " << static_cast<int>(A) << "\n";
      setFlag(Z, A == 0x00);
      setFlag(N, A & (1 << 7));
    } break;
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
};

struct Clock {
  uint64_t master_cycles = 0;

  void subscribe(IClockConsumer *c) { consumers.push_back(c); }

  void tick() {
    for (auto *c : consumers) {
      c->tick();
    }
    master_cycles++;
  }

private:
  std::vector<IClockConsumer *> consumers;
};

int main() {
  Bus bus;

  CPU6502 cpu(&bus);
  cpu.reset();

  Clock clock;
  clock.subscribe(&cpu);

  for (int i = 0; i <= 10; i++) {
    std::cout << "--------" << "tick " << i << "--------\n";
    clock.tick();
    std::cout << "\n";
  }

  return 0;
}
