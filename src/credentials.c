#include <stdio.h>
#include <stdlib.h>
#include "credentials.h"

// a helper function to allocate memory and copy the source string to the destination string
void str_cpy(char* src, char* dst) {
    if (src == NULL || dst == NULL) return;
    src = malloc(len(dst) + 1);
    if (src == NULL) return NULL;
    strncpy(src, dst, len(dst));
}
Entry* create_entry(unsigned id,char* name, char* username, char* password, char* url) {
    Entry entry = {
        .id = id
    };
    // copying all the given strings to our entry object using our helper function
    str_cpy(entry.name, name);
    str_cpy(entry.password, password);
    str_cpy(entry.url, url);
    str_cpy(entry.username, username);

}
// freeing all the strings owned by a particular entry
void free_strings(Entry* entry) {
    if (entry == NULL) return;
    free(entry->name);
    free(entry->password);
    free(entry->url);
    free(entry->username);
}

