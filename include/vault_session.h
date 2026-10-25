#ifndef VAULT_SESSION_H
#define VAULT_SESSION_H

#include "credentials.h"
#include "stdbool.h"


typedef struct {
    unsigned size;
    Entry* entries[2];
    unsigned capacity;
    bool state;
} VaultSession;


#endif