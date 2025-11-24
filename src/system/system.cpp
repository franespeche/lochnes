#include "system/system.h"

System::System() : cpu(&bus) { clock.subscribe(&cpu); }

void System::load_rom(const std::vector<uint8_t> &data) { bus.rom.load(data); }

void System::reset() { cpu.reset(); }

void System::run(uint32_t cycles) {
  if (cycles > 0) {
    for (uint32_t i = 0; i < cycles; ++i) {
      clock.tick();
    }
    return;
  }
  while (true) {
    clock.tick();
  }
}
