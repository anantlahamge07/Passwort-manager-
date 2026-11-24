#include "../include/crypto.h"
#include <stdlib.h>
#include <sodium.h>

bool crypto_init() {
    if (sodium_init() < 0) {
        return false;
    }
    return true;
}

bool derive_key(const char* master_password, size_t len_of_password, const uint8_t* salt, size_t len_of_salt, uint8_t* buf);

// Note: we will use this function to create salt and nonce
bool generate_random_bytes(uint8_t* buf, size_t size) {
    // size = 0 is unacceptable 
    if (!buf || size == 0) return false;
    randombytes_buf(buf, size);
}

// Note: the output buffer must have minimum size len(plain_text) + TAG_SIZE
size_t encrypt_data(const uint8_t* plain_text, size_t len_of_plaintext, const uint8_t* key, const uint8_t* nonce, uint8_t* output, size_t output_size);