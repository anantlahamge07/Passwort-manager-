# Passwort-manager

A command-line password manager written in C. It supports creating and reopening named vaults, adding credential entries, listing entries, deleting entries, and saving a vault when you lock it.

> **Development status:** The project is under active development. The crypto module provides key derivation and authenticated encryption helpers, but the vault workflow does not use them yet.
>
> **Security note:** Vault files are currently saved in readable plaintext, including passwords. Do not use this version to store real or sensitive credentials.

## Requirements

- GCC or a compatible C compiler
- GNU Make
- libsodium development headers and library
- A POSIX-like command-line environment

## Build and run

Build the application from the project directory:

```sh
make
```

This creates the `prog` executable. Start it with:

```sh
./prog
```

The application displays its commands when you enter `h` at the main menu or inside a vault. At the main menu you can create a vault, open a saved vault by name, or exit. Inside a vault you can add entries, list entries, delete an entry by ID, or lock the vault to save it and return to the main menu.

The entry listing shows each entry's ID, name, username, and URL; it masks the password. This only affects display. The password is still stored as plaintext in the vault file.

## Vault storage

Vault files use the path `vaults/<name>.vault`, relative to the program's current working directory. Create the `vaults` directory before running the program; the application does not create it.

The file format is newline-delimited plaintext: an entry count followed by each entry's ID, name, username, password, and URL, each on its own line. Fields containing newline characters are not supported. The file loader expects a well-formed file.

Changes are written when you choose **Lock the vault**. Exiting the application from the main menu does not save an active vault session.

## Crypto helpers

`src/crypto.c` provides:

- `crypto_init()` to initialize libsodium
- `derive_key()` to derive a 32-byte key from a master password and a 16-byte salt using Argon2id
- `generate_random_bytes()` for salts and nonces
- `encrypt_data()` and `decrypt_data()` using XChaCha20-Poly1305 authenticated encryption

These helpers are currently exercised by a separate crypto test, not by vault creation, loading, or saving. Consequently, they do not protect vault files yet.

Build and run the crypto test with:

```sh
make test
make run_test
```

The test executable is named `test`. Remove it with `make clean`.

## Project layout

```text
include/               Public declarations and data structures
src/main.c             Interactive command-line menus
src/credentials.c      Credential entry allocation and cleanup
src/vault_session.c    In-memory entry collection operations
src/vault_manager.c    Vault metadata helpers
src/storage.c          Plaintext vault file loading and saving
src/crypto.c           libsodium key derivation and encryption helpers
tests/test.c           Crypto helper test program
Makefile               Build, test, run, and clean targets
```

## Current limitations

- Vault metadata lookup is not implemented; the numeric vault ID is not used when reopening a vault. Existing vaults are located by name and file path.
- Vault names and fields are not encrypted, and vault files have no password protection.
- The loader expects valid input and does not yet handle malformed or truncated vault files safely.
