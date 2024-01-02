# Shell Project

This project implements a basic shell with modularized components.

## Directory Structure

- `builtins/`: Directory for built-in command implementations.
- `executor/`: Directory for execution-related functionalities.
- `parser/`: Directory for parsing functionalities.
- `scanner/`: Directory for scanning and tokenizing.
- `source/`: Directory for source handling.
- `main.c`: Main entry point of the shell.
- `initsh.c`: Initialization routines for the shell.
- `shell/`: Core functionalities of the shell.
- `node/`: Directory for command structure representation.
- `prompt.c`: Managing the shell prompt appearance.
- `symtab/`: Directory for symbol table-related files.

## Usage

To use the shell, compile the source files and link them together.

For example:
```bash
gcc main.c initsh.c prompt.c executor/executor.c parser/parser.c scanner/scanner.c source/source.c -o my_shell
