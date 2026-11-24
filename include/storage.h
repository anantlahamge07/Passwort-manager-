#ifndef STORAGE_H
#define STORAGE_H

#include "vault_session.h"

#define MAX_NAME 252
#define MAX_USERNAME 252
#define MAX_URL 252
#define MAX_PASSWORD 252

bool save_session(VaultSession* vault_session, const char* path);    
VaultSession* load_session(const char* path);

#endif
