#include "system/system.h"
#include "utils/utils.h"
#include <iostream>

int main() {
  System system;

  std::vector<uint8_t> rom_image = make_rom_image(SAMPLE_PROGRAM);
  system.load_rom(rom_image);

  system.reset();

  while (true) {
    char key;
    std::cin >> key;

    switch (key) {
    case 'n':
      system.clock.tick();
      break;
    default:
      return 0;
    };
  }
  return 0;
}
