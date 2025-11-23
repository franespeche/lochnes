#pragma once

#include <cstdint>
#include <vector>
#include "types.h"

struct Clock {
  uint64_t master_cycles = 0;

  void subscribe(IClockConsumer *c);
  void tick();

private:
  std::vector<IClockConsumer *> consumers;
};

