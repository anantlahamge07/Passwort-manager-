#include "../include/vault_manager.h"
#include <string.h>
#include <stdio.h>

Vault* create_vault(char* name, uint64_t id, char* path) {
    // empty name/path error handling
    if (strcmp(name, "") == 0 || strcmp(path, "") == 0) {
        fprintf(stdout, "The parameters cannot be empty!");
        return NULL;
    }
    // initializing th vault
    Vault vault = {
        .id = id
    };
    // initializing the name and path parameters of the vault
    strncpy(vault.name, name, sizeof(name));
    strncpy(vault.path, path, sizeof(path));
    return &vault;
}

Vaults* get_all_vaults() {}

Vault* get_vault(uint64_t id) {}