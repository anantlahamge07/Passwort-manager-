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

Vaults* get_all_vaults() {
    return NULL;
}

Vault* get_vault(Vaults* vaults, uint64_t id) {
    if (vaults == NULL) return NULL;
    for (size_t i = 0; i < vaults->size; i++)
    {
        if (vaults->vaults[i]->id == id) {
            return vaults->vaults[i];
        }
    }
    fprintf(stdout, "There is no vault with the given id!");
    return NULL;
    

}