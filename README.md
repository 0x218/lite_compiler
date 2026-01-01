# lite_compiler (a C++ Compiler)

lite_compiler is a light weight programming language, written in C++.

## Pre-requisites

Requires `nasm` and `ld` on a Linux operating system.

## Building

```bash
git clone https://github.com/0x218/lite_compiler
cd lite_compiler
mkdir build
cmake -S . -B build
cmake --build build
```

Executable will be `litecpp` in the `build/` directory.


