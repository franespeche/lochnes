#pragma once

#include <cstdint>

struct RAM {
  static constexpr uint16_t SIZE = 0x0800; // 2 KB RAM
  uint8_t data[SIZE];

  RAM();
};

