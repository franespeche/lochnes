#pragma once

#include <cstdint>
#include <vector>

// Function to create a ROM image from a program vector
std::vector<uint8_t> make_rom_image(const std::vector<uint8_t> &program);

// Basic test program
extern const std::vector<uint8_t> SAMPLE_PROGRAM;
