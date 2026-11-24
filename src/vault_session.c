#include "../include/vault_session.h"
#include <stdlib.h>
#include <stdio.h>

VaultSession* create_vault_session(unsigned capacity, bool state) {
    VaultSession* vault_session = malloc(sizeof(VaultSession));
    if (!vault_session) return NULL;
    vault_session->entries = calloc(capacity, sizeof(Entry));
    if (!vault_session->entries) {
        free(vault_session);
        return NULL;
    }
    vault_session->capacity = capacity;
    vault_session->size = 0;
    vault_session->state = state;
    return vault_session;
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

// helper to move lall the elemnts of the entries to the right, so that there are no null entires in the entries list
void move_left(size_t k, size_t size, VaultSession* vault_session) {
    for (size_t i = k; i < size - 1; i++)
    {
        vault_session->entries[i] = vault_session->entries[i + 1];
    }
    
}

bool remove_entry(VaultSession* vault_session, unsigned id) {
    if (vault_session == NULL) return false;
    if (vault_session->size == 0) return false;
    for (size_t i = 0; i < vault_session->size; i++)
    {
        if (vault_session->entries[i]->id == id) {
            // setting the required pointer to NULL
            free_entry(vault_session->entries[i]);
            vault_session->entries[i] = NULL;
            move_left(i, vault_session->size, vault_session);
            vault_session->size--;
            return true;
        }
    }
    return false;
    
}


void free_vault_session(VaultSession* vault_session) {
    if (vault_session == NULL) return;
    for (size_t i = 0; i < vault_session->size; i++)
    {
        // freeing each and every entry in the VaultSession
        free_entry(vault_session->entries[i]);
        vault_session->entries[i] = NULL;
    }
    free(vault_session);
    vault_session = NULL;

    
}