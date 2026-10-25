#ifndef CREDENTIALS_H
#define CREDENTIALS_H

// the password entry 
// Note: the password entry is responsible itself for allocating/deallocating the memory for it's attribute
typedef struct {
    unsigned id;
    char* name;
    char* username;
    char* password;
    char* url;
} Entry;

void str_cpy(char* src, char* dst);
Entry* create_entry(unsigned id,char* name, char* username, char* password, char* url);
void free_strings(Entry* entry);

#endif