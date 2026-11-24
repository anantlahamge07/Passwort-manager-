#ifndef CRYPTO_H
#define CRYPTO_H

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <sodium.h>

#define KEY_SIZE 32
#define NONCE_SIZE 24
#define SALT_SIZE 16
#define TAG_SIZE 16

// to initialize the libsodium
bool crypto_init();

// to derive the key used for encryption using Argon2id
bool derive_key(const char* master_password, size_t len_of_password, size_t len_of_salt, const uint8_t* salt, uint8_t* buf);

// to generate cryptographically secure random bytes
bool generate_random_bytes(uint8_t* buf, size_t size);

// to encrypt the data
// Note: the output buffer must have minimum size len(plain_text) + TAG_SIZE
size_t encrypt_data(const uint8_t* plain_text, size_t len_of_plaintext, const uint8_t* key, const uint8_t* nonce, uint8_t* output, size_t output_size);

size_t decrypt_data(const uint8_t* ciphertext, size_t len_ciphertext, const uint8_t* key, const uint8_t* nonce, uint8_t* output, size_t output_size);

#endif