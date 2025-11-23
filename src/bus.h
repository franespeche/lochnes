#pragma once

#include <cstdint>
#include "ram.h"
#include "rom.h"

struct Bus {
  RAM ram;
  ROM rom;

  uint8_t read(uint16_t address);
  void write(uint16_t address, uint8_t value);
};

