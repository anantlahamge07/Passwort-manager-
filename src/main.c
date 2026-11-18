#include <stdio.h>
#include <stdlib.h>
#include "../include/vault_session.h"
#include "../include/vault_manager.h"
#include "../include/storage.h"

// helper to read the input
static void read_line(char* buff, size_t size) {
    // printf("Prompt: %s", input);
    if (fgets(buff, (int) size, stdin) == NULL) {
        buff[0] = '\0';
        return;
    }
}
static void vault_menu(VaultSession* vault_session, Vault* vault) {
    char buff[8];
    read_line(&buff, sizeof(buff));
    printf("New here? type h to get some help\n");
    while (1) {
        switch (buff[0])
        {
        case '\n':
            break;
        case '1':
            printf("You have chose to add a new entry to the vault\n");
            break;
        case '2':
            printf("You have to chose to list all the entries present in thr vault\n");
        case '3':
            printf("You have chose to delete an entry from the vault\n");
            printf("The entry has been successfully deleted\n");
            break;
        case '4':
        printf("You have chose to lock the vault\n");
        printf("The vault has been successfully locked\n");
        case 'h':
            printf("Here are the list of entries, which you can give as an input\n");
            printf("1 - Add enty\n");
            printf("2 - List all entries\n");
            printf("3 - Delete an entry\n");
            printf("h - Lock the vault\n");
            break;
        
        default:
            printf("Enter h to get a set of the valid inputs\n");
            break;
        };
    }
}
// TODO: finish implementing me
static void main_menu(VaultSession* vault_session, Vault* vault) {
    char buff[8];
    read_line(buff, sizeof(buff));
    while (1) {
        switch (buff[0])
        {
        case '\n':
            break;
        case '1':
            printf("You have chose to create a new vault\n");
            char name_buff[252];
            char id_buff[32];
            printf("Please enter the name of the vault\n");
            while(name_buff == "") {
                read_line(name_buff, sizeof(name_buff));
                if (name_buff == "") printf("The name cannot be emtpy\n");
                else break;
            }
            printf("Please enter the unique id of the vault\n");
            read_line(id_buff, sizeof(id_buff));
            Vault* created_vault = create_vault(name_buff, atoi(id_buff), vault->path);
            printf("A new vault ha been created and saved\n");
            break;
        case '2':
            printf("You have chose to unlock an existing vault\n");
            VaultSession* loaded_vault_session = load_session(vault->path);
            break;
        case '3':
            printf("Password manager closed, goodbye :)\n");
            break;
        case 'h':
            printf("Here are the list of entries, which you can give as an input\n");
            printf("1 - Create a new Vault\n");
            printf("2 - Unlock an existing vault (Only for existing users)\n");
            printf("3 - Exit the program\n");
            printf("h - to get the set of commands\n");
            break;
        
        default:
            printf("Enter h to get a set of the valid inputs\n");
            break;
        };
    }
}



int main(void) {

    printf("      ********      \n");
    printf("   **          **   \n");
    printf("  *              *  \n");
    printf(" *   ***    ***   * \n");
    printf("*    ***    ***    *\n");
    printf("*                  *\n");
    printf("*   *          *   *\n");
    printf(" *   **      **   * \n");
    printf("  *    ******    *  \n");
    printf("   **          **   \n");
    printf("      ********      \n");
    printf("Welcome to password manager!\n");
    printf("======================================================================\n");
    printf("        PASSWORD MANAGER\n");
    printf("======================================================================\n");
    printf("Heyo! What would you like to do this time?\n");
    printf("New here? type h to get some help\n");
    // TODO: finish implementing me
    VaultSession* vault_session = NULL;
    Vault* vault = NULL;
    vault_menu(vault_session, vault);

    return 0;
}
