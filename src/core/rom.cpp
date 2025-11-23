#include "core/rom.h"

ROM::ROM() {}

void ROM::load(const std::vector<uint8_t> &program) {
  data = program;
}

