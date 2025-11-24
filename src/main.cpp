#include "system/system.h"
#include "utils/utils.h"
#include <iostream>

int main() {
  System system;

  std::vector<uint8_t> rom_image = make_rom_image(SAMPLE_PROGRAM);
  system.load_rom(rom_image);

  system.reset();

  system.run(10);

  return 0;
}
