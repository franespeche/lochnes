#include "core/bus.h"
#include <stdexcept>
#include <string>

uint8_t Bus::read(uint16_t address) {
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

void Bus::write(uint16_t address, uint8_t value) {
  // RAM
  if (address < 0x8000) {
    ram.data[address] = value;
  }
}

