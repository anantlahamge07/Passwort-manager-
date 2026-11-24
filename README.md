# Passwort-manager

A small, interactive command-line password manager written in C. It lets you create a vault, add and list credential entries, remove entries, and save a vault when you lock it.

> **Development status:** This project is still in development. Cryptography is being implemented and is not currently available.

> **Security note:** Vault files are currently stored as readable plaintext. There is no master password, encryption, or access control. Do not use this program to store real or sensitive credentials.

## Requirements

- GCC (or a compatible C compiler)
- GNU Make
- A POSIX-like command line environment

## Build

From the project directory, run:

```sh
make
```

This compiles the sources into an executable named `test`. The Makefile enables compiler warnings and AddressSanitizer. To remove the executable:

```sh
make clean
```

## Run

```sh
./test
```

At the main prompt, enter `h` to see the available commands:

1. **Create a new vault** — enter a vault name and numeric ID, then manage entries in the new vault.
2. **Unlock an existing vault** — enter its name to load its saved entries.
3. **Exit** — close the program.

In a vault, enter `h` to show its commands:

1. **Add an entry** — enter a name, username, password, and URL. Empty values are rejected, with up to three attempts for each field.
2. **List entries** — display entry IDs, names, usernames, and URLs. Passwords are masked in this listing.
3. **Delete an entry** — enter its numeric ID.
4. **Lock the vault** — save the current session and return to the main menu.

Changes are saved when you choose **Lock the vault**. Exiting the program from the main menu does not save an active vault session.

## Vault files and data format

Vaults are read from and written to `vaults/<name>.vault`, relative to the current working directory. The `vaults` directory must already exist. The file is a plain text, newline-delimited format: an entry count followed by each entry's ID, name, username, password, and URL on separate lines.

Because fields are stored as lines without escaping, values containing newline characters are not supported reliably. The current loader also expects well-formed vault files.

## Project layout

```text
include/           Public struct and function declarations
src/main.c         Interactive command-line menus
src/credentials.c  Credential entry allocation and cleanup
src/vault_session.c In-memory entry collection operations
src/vault_manager.c Vault metadata helpers
src/storage.c      Plaintext vault file loading and saving
Makefile           Build and clean targets
```

## Current scope

Vault metadata lookup is not implemented yet, and the numeric vault ID is not used when reopening a vault. The program identifies an existing vault by its name and file path.
