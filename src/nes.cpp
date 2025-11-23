#include <bitset>
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
  virtual void tick() = 0;
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

struct ROM {
  std::vector<uint8_t> data;

  ROM() {}

  void load(const std::vector<uint8_t> &program) { data = program; }
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
    if (address >= 0x8000 && !rom.data.empty()) {
      std::uint16_t offset = (address - 0x8000) % rom.data.size();
      return rom.data[offset];
    }

    throw std::out_of_range("Invalid memory access at address: " +
                            std::to_string(address));
  }

  void write(uint16_t address, uint8_t value) {
    // RAM
    if (address < 0x8000) {
      ram.data[address] = value;
    }
  }
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
    std::cout << "--------------------------------------------------\n";
    std::cout << "PC: " << std::hex << static_cast<int>(PC) << "\n";

    uint8_t opcode = bus->read(PC);
    std::cout << "Opcode: " << std::hex << static_cast<int>(opcode) << "\n";
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

  // Flags methods
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

struct System {
  Bus bus;
  CPU6502 cpu;
  Clock clock;

  System() : cpu(&bus) { clock.subscribe(&cpu); }

  void load_rom(const std::vector<uint8_t> &data) { bus.rom.load(data); }

  void reset() { cpu.reset(); }

  void run() {
    while (true) {
      clock.tick();
    }
  }
};

std::vector<uint8_t> get_rom_image() {
  std::vector<uint8_t> rom_image(0x8000, 0x00);
  // basic program
  rom_image[0] = 0xA9;
  rom_image[1] = 0x80;
  rom_image[2] = 0xA9;
  rom_image[3] = 0x00;
  rom_image[4] = 0xA9;
  rom_image[5] = 0xFF;
  rom_image[6] = 0x00;

  // reset vector at $FFFC/$FFFD
  uint16_t entry = 0x8000;
  rom_image[0x7FFC] = entry & 0xFF;        // low
  rom_image[0x7FFD] = (entry >> 8) & 0xFF; // high

  return rom_image;
};

int main() {
  System system;

  std::vector<uint8_t> rom_image = get_rom_image();
  system.load_rom(rom_image);

  system.reset();

  while (true) {
    char key;
    std::cin >> key;

    switch (key) {
    case 'n':
      system.clock.tick();
      break;
    default:
      return 0;
    };
  }
  return 0;
}
