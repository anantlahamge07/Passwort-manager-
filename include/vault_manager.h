#ifndef VAULT_MANAGER_H
#define VAULT_MANAGER_H

#include <stdint.h>

// struct representing a vault 
typedef struct {
    uint64_t id;
    char* name;
    char* path;
} Vault;


// struct representing multiple vaults
typedef struct {
    unsigned capacity;
    unsigned size;
    Vault** vaults;
} Vaults;

Vault* create_vault(char* name, uint64_t id, char* path);

Vaults* get_all_vaults();

Vault* get_vault(Vaults* vaults, uint64_t id);


#endif