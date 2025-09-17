# SIMPLETRON V2

SIMPLETRON V2 is a simulated computer system implemented in C. It features a custom instruction set and a simple command-line interface for loading and executing SML (Simpletron Machine Language) programs.

## Features

- **Memory:** 10,000 words (1 word = 6 digit signed integer), organized into 100 pages of 100 words each.
- **Registers:** Accumulator, Instruction Counter, Instruction Register, Index Register.
- **Instruction Set:** 24 operations, including arithmetic, branching, indexed addressing, and I/O.
- **Program Input:** Supports both manual entry and loading from SML files.
- **Core Dump:** On HALT, prints register values and memory pages.
- **Sample Programs:** Includes SML files for min/max, array sum, and GCD calculations.

## Building
This project was built and run using custom build system (linux only).
To build the project, compile manually instead:

```sh
gcc -Iinclude -o bin/simpletron src/main.c src/simpletron.c src/simpletron_opcode.c src/simpletron_utils.c
```
## Running

Run the Simpletron executable:

```sh
./bin/simpletron
```

You will be prompted to either:

Load an SML program from a file (e.g., minmax.sml)
Enter instructions manually
SML Instruction Set
Each instruction is a 6-digit signed integer:

First 2 digits: Opcode
Last 4 digits: Operand (address or immediate value)
Example:
```
200050 // LOAD(20) -> memory[50]
```
See outline.txt for the full opcode list.

Example SML Programs
minmax.sml: Finds the minimum and maximum of user inputs.
arraysum.sml: Sums an array of numbers.
gcd.sml: Computes the greatest common divisor.

## Author:

Kaile Jones


