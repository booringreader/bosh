# Shell Project

This project implements a basic shell with modularized components.

## Directory Structure

- `scanner/`: Directory for scanning and tokenizing.
- `source/`: Directory for source handling.
- `main.c`: Main entry point of the shell.
- `shell/`: Core functionalities of the shell.
- `prompt.c`: Managing the shell prompt appearance.

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
