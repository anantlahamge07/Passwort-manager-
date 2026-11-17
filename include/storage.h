#ifndef STORAGE_H
#define STORAGE_H

#include "vault_session.h"


bool save_session(VaultSession* vault_session, const char* path);    
VaultSession* load_session(const char* path);

#endif
