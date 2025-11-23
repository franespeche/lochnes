#include "ram.h"

RAM::RAM() {
  for (uint16_t i = 0; i < SIZE; i++) {
    data[i] = 0;
  }
}

