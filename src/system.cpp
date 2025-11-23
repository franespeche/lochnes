#include "system.h"

System::System() : cpu(&bus) {
  clock.subscribe(&cpu);
}

void System::load_rom(const std::vector<uint8_t> &data) {
  bus.rom.load(data);
}

void System::reset() {
  cpu.reset();
}

void System::run() {
  while (true) {
    clock.tick();
  }
}

