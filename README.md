# Assembler

This is an assembler for a made up assembly language. The machine has a memory with 216 16-bit words, a program counter register, PC and an accumulator registerm, ACC, both with 16 bits. There are three instruction types:

 1. Opcode
 2. Opcode Address
 3. Opcode Address Address

The supported operations are shown in the figure below:

![instructions](rsc/instructions.png)

The language also supports the `PUBLIC` and `EXTERN` directives. These may be used to modularize code. It is necessary to add a `BEGIN` before any section, followed by all public and extern definitions, and an `END` after all sections if the code is written in modules. 

If your program is a single file it must not include `BEGIN...END`, `PUBLIC` or `EXTERN`.

## First Steps

This program depends on cmake, make and g++ to build. It uses C++11. Please install cmake, make and C++11 before proceeding.

### Compiling

To compile the project, follow the steps below.

First, run cmake to generate the makefiles:
```
cmake -B build
```

Then, go into the build dir, and run make (you may add `-j<cores>` to speed up compilation):
```
cd build && make
```

After that, the program is compiled and available in the src folder of the build dir.
```
cd src && ls montador
```

You may copy it to the folder you would like to use and run it as following. The asm_file may be the absolute or relative path to the assembly source code file. It must have an .asm extension. The `montador` will generate an .o file in the same folder as the source file if it succeeds:
```
./montador <asm_file>
```

This file must be linked into an .obj file to be run by the simulator.

## Running Unit Tests

The project was developed through an TDD approach, thus, it contains a thorough test suite, which is built with the executable. To run it, access the tests folder in the build dir and run the following command:

```
./montador_tst
```

## Build tools

* [CMake](https://cmake.org/)
* [Make](https://www.gnu.org/software/make/)

## Contributing

This repository doesn't accept contributions until December 2021. If you must contribute, please reach out for the author.

## Authors

* **Mateus Berardo** - *Initial Work* - [MatTerra](https://github.com/MatTerra)

Also check out the [contributors](graphs/contributors).

## License

The author reserves all rights to the code hereby provided. It is strictly prohibited to copy or modify the code provided. It is allowed to use the code for educational purposes only and only if the author is credited. For any other use or more permissive conditions, contact the author. Any exceptions made by the author for third-parties does not mean changes in this license's terms for other people.

## Acknoledgments

* **Billie Thompson** - *README template* - [PurpleBooth](https://github.com/PurpleBooth)

