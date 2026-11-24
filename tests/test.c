#include "../include/crypto.h"
#include <string.h>
#include <stdio.h>
int main(void)
{
    const char* master_password = "password";
    const char* m = "plaintext";
    crypto_init();
    uint8_t salt[SALT_SIZE];
    uint8_t nonce[NONCE_SIZE];
    bool salt_success = generate_random_bytes(salt, SALT_SIZE);
    bool nonce_success = generate_random_bytes(nonce, NONCE_SIZE);
    if (!salt_success || !nonce_success) {
        printf("salt creation or nonce creating didn't succeed :(\n");
        return 0;
    }
    uint8_t key[KEY_SIZE];
    bool derivation_success = derive_key(master_password, strlen(master_password), SALT_SIZE, salt, key);
    if (!derivation_success) {
        printf("The key couldn't be derived :(\n");
        return 0;
    }
    printf("The key has been generated: %u\n", key);
    uint8_t ciphertext[TAG_SIZE + strlen(m)];
    size_t encryption = encrypt_data((const uint8_t*)m, strlen(m), key, nonce, ciphertext, sizeof(ciphertext));
    if (encryption == 0) {
        printf("Decryption failed :(\n");
        return 0;
    }
    uint8_t plain_text[TAG_SIZE + strlen(m)];
    size_t decryption = decrypt_data(ciphertext, encryption, key, nonce, plain_text, sizeof(plain_text));
    if (decryption == 0) {
        printf("Decryption failed :(\n");
        return 0;
    }
    printf("encryption length: %zu\n", encryption);
    printf("decryption length: %zu\n", decryption);
    plain_text[decryption] = '\0';
    for (size_t i = 0; i < encryption; i++) {
        printf("%x", ciphertext[i]);
    }
    printf("\n");
    printf("Decrypted: %s\n", plain_text);
    bool is_equal = sodium_memcmp(m, plain_text, strlen(m)) == 0;
    printf("is_equal: %d", is_equal);
    printf("\n");
    return 0;
}

