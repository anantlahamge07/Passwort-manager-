#include "../include/crypto.h"
#include <string.h>
#include <stdio.h>
int main(void)
{
    const char* master_password = "password";
    const char* wrong_password = "p";
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
    uint8_t key_1[KEY_SIZE];
    bool derivation_success = derive_key(master_password, strlen(master_password), SALT_SIZE, salt, key);
    if (!derivation_success) {
        printf("The key couldn't be derived :(\n");
        return 0;
    }
    bool derivation_success_1 = derive_key(wrong_password, strlen(wrong_password), SALT_SIZE, salt, key_1);
    if (!derivation_success_1) {
        printf("The key_1 couldn't be derived :(\n");
        return 0;
    }
    uint8_t ciphertext[TAG_SIZE + strlen(m)];
    size_t encryption = encrypt_data((const uint8_t*)m, strlen(m), key, nonce, ciphertext, sizeof(ciphertext));
    if (encryption == 0) {
        printf("Decryption failed :(\n");
        return 0;
    }
    uint8_t plain_text[TAG_SIZE + strlen(m)];
    uint8_t plain_text_1[TAG_SIZE + strlen(m)];
    size_t decryption = decrypt_data(ciphertext, encryption, key, nonce, plain_text, sizeof(plain_text));
    if (decryption == 0) {
        printf("Decryption failed :(\n");
        return 0;
    }
    size_t decryption_1 = decrypt_data(ciphertext, encryption, key_1, nonce, plain_text_1, sizeof(plain_text_1));
    if (decryption_1 == 0) {
        printf("Decryption failed :(\n");
        return 0;
    }
    printf("encryption length: %zu\n", encryption);
    printf("decryption length: %zu\n", decryption);
    printf("decryption length: %zu\n", decryption_1);
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


