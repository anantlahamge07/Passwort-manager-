#include "../include/vault_manager.h"
#include "../include/credentials.h"
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
    if (!vault) return NULL;
    vault->id = id;
    
    char* dest = str_cpy(name);
    if (!dest) {
        free(vault);
        return NULL;
    }
    vault->name = dest;
    char* dest1 = str_cpy(path);
    if (!dest1) {
        free(vault);
        return NULL;
    }
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