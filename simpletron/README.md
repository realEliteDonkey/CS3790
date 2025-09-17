# SIMPLETRON V2

SIMPLETRON V2 is a simulated computer system implemented in C, designed for educational purposes. It features a custom instruction set, memory paging, and a simple command-line interface for loading and executing SML (Simpletron Machine Language) programs.

## Features

- **Memory:** 10,000 words, organized into 100 pages of 100 words each.
- **Registers:** Accumulator, Instruction Counter, Instruction Register, Index Register.
- **Instruction Set:** 24 operations, including arithmetic, branching, indexed addressing, and I/O.
- **Program Input:** Supports both manual entry and loading from SML files.
- **Core Dump:** On HALT, prints register values and memory pages.
- **Sample Programs:** Includes SML files for min/max, array sum, and GCD calculations.

## Project Structure
. ├── arraysum.sml # Sample SML program: array sum ├── gcd.sml # Sample SML program: GCD ├── minmax.sml # Sample SML program: min/max ├── outline.txt # Project and instruction set outline ├── src/ │ ├── main.c # Entry point, user interface │ ├── simpletron.c # Core execution and memory dump │ ├── simpletron_opcode.c# Opcode implementations │ └── simpletron_utils.c # Program input utilities ├── include/ │ ├── errors.h # Error codes │ ├── opcode.h # Opcode definitions │ ├── op_func.h # Opcode function declarations │ ├── simpletron.h # Simpletron struct and prototypes │ └── simpletron_utils.h # Utility function declarations └── ...


## Building

To build the project, use the provided build system or compile manually:

```sh
gcc -Iinclude -o bin/simpletron [main.c](http://_vscodecontentref_/12) [simpletron.c](http://_vscodecontentref_/13) [simpletron_opcode.c](http://_vscodecontentref_/14) [simpletron_utils.c](http://_vscodecontentref_/15)

Running
Run the Simpletron executable:
./bin/simpletron

You will be prompted to either:

Load an SML program from a file (e.g., minmax.sml)
Enter instructions manually
SML Instruction Set
Each instruction is a 6-digit signed integer:

First 2 digits: Opcode
Last 4 digits: Operand (address or immediate value)
Example:

200050 // LOAD [50]

See outline.txt for the full opcode list.

Example SML Programs
minmax.sml: Finds the minimum and maximum of user inputs.
arraysum.sml: Sums an array of numbers.
gcd.sml: Computes the greatest common divisor.

Author:
Kaile Jones