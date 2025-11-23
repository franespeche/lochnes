#include "doctest.h"
#include "nes.h"
#include <iostream>

TEST_CASE("CPU tests") {
  System system;

  SUBCASE("simple") {
    std::cout << "Running [CPU][simple]..." << std::endl;

    system.load_rom({
        0xa9, 0x10, // LDA #$10     -> A = #$10
        0x85, 0x20, // STA $20      -> $20 = #$10
        0xa9, 0x01, // LDA #$1      -> A = #$1
        0x65, 0x20, // ADC $20      -> A = #$11
        0x85, 0x21, // STA $21      -> $21=#$11
        0xe6, 0x21, // INC $21      -> $21=#$12
        0xa4, 0x21, // LDY $21      -> Y=#$12
        0xc8,       // INY          -> Y=#$13
        0x00,       // BRK

    });

    CHECK(system.cpu.PC == 0x1000);

    /*
    CHECK(cpu->peek(0x20) == 0x10);
    CHECK(cpu->peek(0x21) == 0x12);
    CHECK(cpu->A() == 0x11);
    CHECK(cpu->Y() == 0x13);
    */
  }
