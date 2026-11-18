#include <stdio.h>
#include <stdlib.h>
#include "../include/vault_session.h"

// helper to read the input
static void read_line(char* buff, size_t size) {
    // printf("Prompt: %s", input);
    if (fgets(buff, (int) size, stdin) == NULL) {
        buff[0] = '\0';
        return;
    }
}

// TODO: finish implementing me
static void vault_menu(VaultSession* vault_session) {
    char buff[8];
    read_line(&buff, sizeof(buff));
    printf("Heyo! What would you like to do this time?\n");
    printf("New here? type h to get some help\n");
    while (1) {
        switch (buff[0])
        {
        case '\n':
            break;
        case '1':
            printf("You have chose to create a new vault\n");
            break;
        case '2':
            printf("You have chose to unlock an existing vault\n");
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
    // TODO: finish implementing me
    VaultSession* vault_session = NULL;
    vault_menu(vault_session);

    return 0;
}
