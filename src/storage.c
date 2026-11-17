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
    // the vault doesn't exist
    if (!fptr) {
        return NULL;
    }
    char buf[32];
    fgets(buf, sizeof(buf), fptr);
    int num_of_entries = atoi(buf);
    VaultSession* vault_session = create_vault_session(0, num_of_entries, true);
    if (vault_session == NULL) {
        fclose(fptr);
        return NULL;
    }
    while (num_of_entries > 0){
        char id_buf[32];
        char name_buf[MAX_NAME];
        char username_buf[MAX_USERNAME];
        char password_buf[MAX_PASSWORD];
        char url_buff[MAX_URL];
        fgets(id_buf, sizeof(id_buf), fptr);
        fgets(name_buf, MAX_NAME, fptr);
        fgets(username_buf, MAX_USERNAME, fptr);
        fgets(password_buf, MAX_PASSWORD, fptr);
        fgets(url_buff, MAX_URL, fptr);
        
        Entry* entry = create_entry((unsigned) atoi(id_buf), name_buf, username_buf, password_buf, url_buff);
        if(!entry) {
            fclose(fptr);
            return NULL;
        }
        if (!add_entry(vault_session, entry)) fclose(fptr); return NULL;
        num_of_entries--;
    }
    fclose(fptr);
    return vault_session;
    

}