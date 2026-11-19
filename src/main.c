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

static int read_loop(char* buff, size_t size, int repeat, char* str) {
    while (repeat > 0) {
        printf("%s", str);
        read_line(buff, size);
        if (buff[0] != '\0') return 1;
        repeat--;
    }
    return 0;
}
static void vault_menu(VaultSession* vault_session, Vault* vault) {
    // no arguments validation check, becaus they are guaranteed to be valid
    printf("New here? type h to get some help\n");
    while (1) {
        char buff[8];
        read_line(buff, sizeof(buff));
        switch (buff[0])
        {
        case '\n':
            break;
        case '1':
            printf("You have chosen to add a new entry\n");
            char id_buff[32];
            char name_buff[252];
            char username_buf[252];
            char password_buff[252];
            char url_buff[252];
            if (read_loop(id_buff, sizeof(id_buff), 3, "Please enter an id\n") == 0) {
                printf("Too many attempts :(\n");
                break;
            }
            if (read_loop(name_buff, sizeof(name_buff), 3, "Please enter a name for the new Entry\n") == 0) {
                printf("Too many attempts :(\n");
                break;
            }
            if (read_loop(username_buf, sizeof(username_buf), 3, "Please enter an username\n") == 0) {
                printf("Too many attempts :(\n");
                break;
            }
            if (read_loop(password_buff, sizeof(password_buff),3, "please enter your password\n") == 0) {
                printf("Too many attempts :(\n");
                break;
            }
            if (read_loop(url_buff, sizeof(url_buff), 3, "Please enter an url for the Entry\n") == 0) {
                printf("Too many attempts :(\n");
                break;
            }
            Entry* entry = create_entry((unsigned) atoi(id_buff), name_buff, username_buf, password_buff, url_buff);
            if (!entry) {
                printf("Entry could not be created :(");
                break;
            }
            if (!add_entry(vault_session, entry)) {
                free_entry(entry);
                printf("Entry could not be added to the vault session\n");
                break;
            }
            printf("The entry has been successfully added :)\n");
            break;
        case '2':
            printf("You have to chose to list all the entries present in thr vault\n");
            if (vault_session->size == 0) printf("The session is empty, there is nothing ot be listed :)\n");
            for (size_t i = 0; i < vault_session->size; i++)
            {
                Entry* entry = vault_session->entries[i];
                // skipping the null entries for the time being
                if (!entry) continue;
                printf("id: %u\n", entry->id);
                printf("name: %s\n", entry->name);
                printf("username: %s\n", entry->username);
                printf("password: %s\n", "****");
                printf("url: %s\n", entry->url);
            }
            break;
        case '3':
            printf("You have chose to delete an entry from the vault\n");
            char id[32];
            if (read_loop(id, sizeof(id), 3, "Please enter the id of the entry to be removed\n") == 0) {
                printf("Number of attempts failed!\n");
                break;
            }
            if (!remove_entry(vault_session, (unsigned) atoi(id))) {
                printf("Entry could no be found :(\n");
                if (read_loop(id, sizeof(id), 3, "Please enter the id of the entry to be removed\n") == 0) {
                    printf("Number of attempts failed!\n");
                    break;
                }
                break;
            }
            printf("The entry has been successfully deleted\n");
            break;
        case '4':
        printf("You have chose to lock the vault\n");
        if (!save_session(vault_session, vault->path)) {
            printf("The session could not be saved :(\n");
            break;
        }
        printf("The vault has been successfully locked\n");
        break;
        case 'h':
            printf("Here are the list of entries, which you can give as an input\n");
            printf("1 - Add enty\n");
            printf("2 - List all entries\n");
            printf("3 - Delete an entry\n");
            printf("h - Lock the vault\n");
            break;
        
        default:
            printf("Enter h to get a set of valid inputs\n");
            break;
        };
    }
}
// TODO: finish implementing me
static void main_menu() {
    while (1) {
        char buff[32];
        read_line(buff, sizeof(buff));
        bool end = false;
        if (end) {
            break;
        }
        switch (buff[0])
        {
        case '\n':
            break;
        case '1':
            printf("You have chose to create a new vault\n");
            char name_buff[252];
            char id_buff[32];
            if (read_loop(name_buff, sizeof(name_buff), 3, "Please enter the name of the vault\n") == 0) {
                printf("Too many attempts\n");
                break;
            }
            if (read_loop(id_buff, sizeof(id_buff), 3, "Please enter the id of the vault\n") == 0) {
                printf("Too many attempts\n");
                break;
            }
            Vault* vault = create_vault(name_buff, (unsigned) atoi(id_buff), vault->path);
            VaultSession* vault_session = create_vault_session(0, 4, true);
            if (!vault || !vault_session) {
                printf("There was a problem in the creating of the vault or vault session :(\n");
                break;
            }
            vault_menu(vault_session, vault);
            free_vault_session(vault_session);
            free_vault(vault);
            printf("A new vault has been created and saved\n");
            break;
        case '2':
            printf("You have chose to unlock an existing vault\n");
            VaultSession* loaded_vault_session = load_session(vault->path);
            break;
        case '3':
            end = true;
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
    main_menu();

    return 0;
}
