#ifndef VAULT_SESSION_H
#define VAULT_SESSION_H

#include "credentials.h"
#include "stdbool.h"


typedef struct {
    unsigned size;
    Entry** entries;
    unsigned capacity;
    bool state;
} VaultSession;

VaultSession* create_vault_session(unsigned size, unsigned capacity, bool state);
bool add_entry (VaultSession* vault_session, Entry* entry);
bool remove_entry(VaultSession* vault_session, unsigned id);
void free_resources(VaultSession* vault_session);

#endif