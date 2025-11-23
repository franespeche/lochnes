#pragma once

#include <cstdint>
#include <vector>

struct ROM {
  std::vector<uint8_t> data;

  ROM();
  void load(const std::vector<uint8_t> &program);
};

