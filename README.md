# Shell Project

This project implements a basic shell with modularized components.

## Directory Structure

- `scanner/`: Directory for scanning and tokenizing.
- `source/`: Directory for source handling.
- `main.c`: Main entry point of the shell.
- `shell/`: Core functionalities of the shell.
- `prompt.c`: Managing the shell prompt appearance.
- `parser/`: Directory for parsing functionalities.
- `node/`: Directory for command structure (AST) representation.
- `executor/`: Directory for execution-related functionalities.
<!--- 
 `builtins/`: Directory for built-in command implementations.
 `initsh.c`: Initialization routines for the shell.
 `symtab/`: Directory for symbol table-related files. 
 --->

## Usage

To use the shell, compile the source files and link them together.

```bash
gcc main.c prompt.c scanner/scanner.c source/source.c -o my_shell
```

To demonstrate a basic single-line input in the shell, use the `echo` command:

```bash
echo "This is a single-line input."
```

## License

This project is licensed under the [MIT License](LICENSE).
