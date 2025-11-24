# NES Emulator
This is a WIP C++ NES Emulator for the sake of learning

Currently, the emulator is capable of running a simple program with basic `LDA` instructions.

All the remaining opcodes had been implemented, but not tested.

Note that tests weren't tested (lol), they are just boilerplate.

## Core Implementation
Each clockable device subscribes to the main Clock.
For this, a `tick` method must be implemented.
CPU Instructions live in an `instructions_table`, with their `total_cycles` and `execute(uint_8t cycle)` function.
Note that each execute method starts from cycle `2` (and not 1). This is because cycle 1 is responsible for fetching the opcode and is being done in the CPU tick method.

# Running the basic program
To run the sample program, run `make run`.
Since this is a hobby project, I'll be adding commits whenever I have time to do so.
