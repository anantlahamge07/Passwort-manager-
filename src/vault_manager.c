#include "../include/vault_manager.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

Vault* create_vault(char* name, uint64_t id, char* path) {
    // empty name/path error handling
    if (strcmp(name, "") == 0 || strcmp(path, "") == 0) {
        fprintf(stdout, "The parameters cannot be empty!");
        return NULL;
    }
    // allocating memory for the vault
    Vault* vault = (Vault*) malloc(sizeof(Vault));
    vault->id = id;
    // initializing the name and path parameters of the vault
    vault->name = (char*) malloc(strlen(name) + 1);
    if (vault->name == NULL) return NULL;
    vault->path = (char*) malloc(strlen(path) + 1);
    if (vault->path == NULL) {
        free(vault->name);
        return NULL;
    }
    char dest[sizeof(name)];
    char dest1[sizeof(path)];
    strncpy(dest, name, sizeof(name));
    vault->name = dest;
    strncpy(dest1, path, sizeof(path));
    vault->path = dest1;
    return vault;
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

void free_vault(Vault* vault) {
    if (!vault) return;
    free(vault->name);
    free(vault->path);
    free(vault);
    vault = NULL;
}