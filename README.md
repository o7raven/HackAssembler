# Hack Assembler

This is a C++ implementation of an assembler for the "Hack computer" designed in the "Nand to Tetris" course.

The "Hack computer" is a simple computer architecture created in the "Nand to Tetris" project. It features a 16-bit instruction set architecture (ISA) and is designed to be simple yet powerful. The assembler provided here takes assembly code written in the "hack assembly language" and translates it into machine code that can be executed by the hack computer.

## Features

- Translates hack assembly code to machine code.
- Supports all the instructions and addressing modes defined in the hack architecture.
- Handles labels and variables defined in the assembly code.
- Generates a binary output file containing the translated machine code.

## Getting Started

1. Clone this repository:

   ```bash
   git clone https://github.com/o7raven/HackAssembler.git

## Build the asssembler
```cd HackAssembler
make
```

## Run the assembler
> Assembler.exe main.asm

The assembler argument must be only the name of the assembly program, otherwise the binary will not be created.

# Limitations

The assembler assumes that the input assembly code is written in the hack assembly language, flawless and follows the syntax and rules specified in the "Nand to Tetris" course.

# Contributing

Contributions to this project are welcome. If you find any issues or want to suggest enhancements, please open an issue or submit a pull request.

# License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.
