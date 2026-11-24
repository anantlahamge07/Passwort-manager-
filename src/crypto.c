#include "../include/crypto.h"
#include <stdlib.h>
#include <sodium.h>

bool crypto_init() {
    if (sodium_init() < 0) {
        return false;
    }
    return true;
}

// Note: here salt must have size = SALT_SIZE
// Note: caller must provide buf of size KEY_SIZE
bool derive_key(const char* master_password, size_t len_of_password, size_t len_of_salt, const uint8_t* salt, uint8_t* buf) {
    if (len_of_salt != SALT_SIZE || !master_password || !salt || !buf) return false;
    int res = crypto_pwhash(buf, KEY_SIZE, master_password, len_of_password,
        salt, crypto_pwhash_OPSLIMIT_INTERACTIVE, crypto_pwhash_MEMLIMIT_INTERACTIVE, crypto_pwhash_ALG_ARGON2ID13);
    if (res == -1) return false;
    return true;
}

// Note: we will use this function to create salt and nonce
bool generate_random_bytes(uint8_t* buf, size_t size) {
    // size = 0 is unacceptable
    if (!buf || size == 0) return false;
    randombytes_buf(buf, size);
    return true;
}

// Note: the output buffer must have minimum size len(plain_text) + TAG_SIZE
// here we will use XChaCha20-Poly1305 encryption, which is provided by libsodium
size_t encrypt_data(const uint8_t* plain_text, size_t len_of_plaintext, const uint8_t* key, 
    const uint8_t* nonce, uint8_t* output, size_t output_size) {
    if (output_size != (len_of_plaintext + TAG_SIZE)) return 0;
    unsigned long long clen_p; 
    if (!output || !key || !nonce || !plain_text) return 0;
    int res = crypto_aead_xchacha20poly1305_ietf_encrypt(output, &clen_p, plain_text, len_of_plaintext,
        NULL, 0, NULL, nonce, key);
    if (res == -1) return 0;
    return clen_p;
}