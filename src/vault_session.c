#include "../include/vault_session.h"
#include <stdlib.h>
#include <stdio.h>


VaultSession* create_vault_session(unsigned size, unsigned capacity, bool state) {
    VaultSession vault_session = {
        .size = size, 
        .entries = malloc(capacity * sizeof(Entry)),
        .capacity = capacity,
    };

    return &vault_session;
}


bool add_entry (VaultSession* vault_session, Entry* entry) {
    if (vault_session == NULL || entry == NULL) return false;
    if (vault_session->size == vault_session->capacity) {
        if (vault_session->capacity == 0) {
            Entry** temp = realloc(vault_session->entries, 2 * sizeof(Entry*));
            if (temp == NULL) {
                return false;
            }
            vault_session->capacity = 2;
            vault_session->entries = temp;
            temp = NULL;

        } else {

            Entry** temp = realloc(vault_session->entries, vault_session->capacity * 2 * sizeof(Entry*));
            if (temp == NULL) {
                return false;
            }
            vault_session->capacity = vault_session->capacity * 2;
            vault_session->entries = temp;
            temp = NULL;
        }
        vault_session->entries[vault_session->size] = entry;
        vault_session->size++;
        return true;
    }
    vault_session->entries[vault_session->size] = entry;
    vault_session->size++;
    return true;
}


bool remove_entry(VaultSession* vault_session, unsigned id) {
    if (vault_session == NULL) return false;
    if (vault_session->size == 0) return false;
    for (size_t i = 0; i < vault_session->size; i++)
    {
        if (vault_session->entries[i]->id == id) {
            // setting the required pointer to NULL
            free(vault_session->entries[i]);
            vault_session->entries[i] = NULL;
            vault_session->size--;
            return true;
        }
    }
    return false;
    
}

void free_resources(VaultSession* vault_session) {
    if (vault_session == NULL) return;
    for (size_t i = 0; i < vault_session->size; i++)
    {
        // freeing each and every entry in the VaultSession
        free(vault_session->entries[i]);
        vault_session->entries[i] = NULL;
    }
    free(vault_session);
    vault_session = NULL;

    
}