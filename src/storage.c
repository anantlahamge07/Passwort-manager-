#include "../include/storage.h"
#include "stdio.h"


// typedef struct {
    // unsigned id;
    // // char* name;
    // char* username;
    // char* password;
    // char* url;
// } Entry;
// TODO: implement me
bool save_session(VaultSession* vault_session, const char* path) {
    // invalid inputs
    if (vault_session == NULL || path == NULL) return false;
    FILE* fptr;
    // opening the file in write mode
    if ((fptr = fopen(path, "w")) == NULL) return false;
    fprintf(fptr, vault_session->size);
    for (size_t i = 0; i < vault_session->size; i++)
    {
        fprintf(fptr, "%u\n", vault_session->entries[i]->id);
        fprintf(fptr, "%s\n", vault_session->entries[i]->name);
        fprintf(fptr, "%s\n", vault_session->entries[i]->username);
        fprintf(fptr, "%s\n", vault_session->entries[i]->password);
        fprintf(fptr, "%s\n", vault_session->entries[i]->url);
    }
    
    // close the file
    fclose(fptr);
    return true;

}
// TODO: implement me
VaultSession* load_session(const char* path) {
    // invalid input
    if (!path) return NULL;
    // open the file in read mode
    FILE* fptr = fopen(path, "r");
    if (!fptr) {
        return NULL;
    }
    return NULL;
    

}