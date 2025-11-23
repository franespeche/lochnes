#include "utils.h"
#include <stdexcept>

std::vector<uint8_t> make_rom_image(const std::vector<uint8_t> &program) {
  if (program.size() >= 0x7FFC) {
    throw std::runtime_error("Program too large");
  }

  std::vector<uint8_t> rom_image(0x8000, 0x00);

  for (size_t i = 0; i < program.size(); ++i) {
    rom_image[i] = program[i];
  }

  // reset vector at $FFFC/$FFFD
  uint16_t entry = 0x8000;
  rom_image[0x7FFC] = entry & 0xFF;        // low
  rom_image[0x7FFD] = (entry >> 8) & 0xFF; // high

  return rom_image;
}

// basic program
const std::vector<uint8_t> SAMPLE_PROGRAM = {0xA9, 0x80, 0xA9, 0x00,
                                             0xA9, 0xFF, 0x00};
