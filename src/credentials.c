#include <stdio.h>
#include <stdlib.h>
#include "../include/credentials.h"
#include <string.h>

// a helper function to allocate memory and copy the source string to the destination string
//  TODO: fix me (something related to create_entry)
char* str_cpy(char* src) {
    if (src == NULL) return NULL;
    char* dst = malloc(strlen(src) + 1);
    if (dst == NULL) return NULL;
    strncpy(dst, src, strlen(src) + 1);
    return dst;
}


Entry* create_entry(unsigned id, char* name, char* username, char* password, char* url) {
    Entry* entry = malloc(sizeof(Entry));
    // assigning the id
    entry->id = id;
    // copying all the given strings to our entry object using our helper function
    entry->name = str_cpy(name);
    entry->username = str_cpy(username);
    entry->password = str_cpy(password);
    entry->url = str_cpy(url);
    return entry;
}
// freeing all the strings owned by a particular entry
void free_strings(Entry* entry) {
    if (entry == NULL) return;
    free(entry->name);
    free(entry->password);
    free(entry->url);
    free(entry->username);
}

void free_entry(Entry* entry) {
    free_strings(entry);
    free(entry);
    entry = NULL;
}
