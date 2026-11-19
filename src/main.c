#include <stdio.h>
#include <stdlib.h>
#include "../include/vault_session.h"
#include "../include/vault_manager.h"
#include "../include/storage.h"
#include <string.h>
// helper to read the input
static void read_line(char* buff, size_t size) {
    // printf("Prompt: %s", input);
    if (fgets(buff, (int) size, stdin) == NULL) {
        buff[0] = '\0';
        return;
    }
    size_t i = strcspn(buff, "\n");
    buff[i] = '\0';
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

static bool build_path(const char* name, char* out, size_t size) {
    int written = snprintf(out, size, "vaults/%s.vault", name);
    if (written < 0 || written >= (int) size) return false;
    return true;
}

static int next_id(VaultSession* vault_session) {
    unsigned max_id = 0;
    for (size_t i = 0; i < vault_session->size; i++)
    {
        Entry* entry = vault_session->entries[i];
        if (entry->id > max_id) {
            max_id = entry->id;
        }
        
    }
    return (int) max_id + 1;
    
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
            // char id_buff[32];
            char name_buff[252];
            char username_buf[252];
            char password_buff[252];
            char url_buff[252];
            int next_id_ = next_id(vault_session);
            if (next_id_ == -1) {
                next_id_ = 1;
            }
            if (read_loop(name_buff, sizeof(name_buff), 3, "Please enter a name for the new Entry\n") == 0) {
                printf("Too many attempts :(\n");
                continue;;
            }
            if (read_loop(username_buf, sizeof(username_buf), 3, "Please enter an username\n") == 0) {
                printf("Too many attempts :(\n");
                continue;
            }
            if (read_loop(password_buff, sizeof(password_buff),3, "please enter your password\n") == 0) {
                printf("Too many attempts :(\n");
                continue;
            }
            if (read_loop(url_buff, sizeof(url_buff), 3, "Please enter an url for the Entry\n") == 0) {
                printf("Too many attempts :(\n");
                continue;
            }
            Entry* entry = create_entry((unsigned) next_id_, name_buff, username_buf, password_buff, url_buff);
            if (!entry) {
                printf("Entry could not be created :(");
                continue;
            }
            if (!add_entry(vault_session, entry)) {
                free_entry(entry);
                printf("Entry could not be added to the vault session\n");
                continue;
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
                if (!entry) continue;;
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
                continue;
            }
            if (!remove_entry(vault_session, (unsigned) atoi(id))) {
                printf("Entry could no be found :(\n");
                if (read_loop(id, sizeof(id), 3, "Please enter the id of the entry to be removed\n") == 0) {
                    printf("Number of attempts failed!\n");
                    continue;
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
        return;
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
    bool end = false;
    while (1) {
        char buff[32];
        read_line(buff, sizeof(buff));
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
            char path[512];
            bool r = build_path(name_buff, path, sizeof(name_buff));
            if (!r) {
                printf("Invalid vault name\n");
                continue;;
            }
            Vault* vault = create_vault(name_buff, (unsigned) atoi(id_buff), path);
            VaultSession* vault_session = create_vault_session(0, 4, true);
            if (!vault || !vault_session) {
                printf("There was a problem in the creating of the vault or vault session :(\n");
                break;
            }
            printf("A new vault has been created and saved\n");
            printf("Vault menu booting up\n");
            vault_menu(vault_session, vault);
            free_vault_session(vault_session);
            free_vault(vault);
            break;
        case '2':
            printf("You have chose to unlock an existing vault\n");
            char name[252];
            if (read_loop(name, sizeof(name), 3, "Please enter the name of the vault\n") == 0) {
                printf("Too many attempts :(\n");
                break;
            }
            char path_[512];
            bool r_ = build_path(name, path_, sizeof(name));
            if (!r_) {
                printf("Invalid vault name\n");
                continue;
            }
            VaultSession* loaded_vault_session = load_session(path_);
            if (!loaded_vault_session) {
                printf("Vault not found :(\n");
                break;
            }
            // TODO: fix the id placeholder
            Vault* created_vault = create_vault(name, 0, path_);
            vault_menu(loaded_vault_session, created_vault);
            free_vault(created_vault);
            free_vault_session(loaded_vault_session);
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
