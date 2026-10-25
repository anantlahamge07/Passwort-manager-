#include <stdio.h>
#include <stdlib.h>

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
    char buff;
    printf("Heyo! What would you like to do this time?\n");
    printf("New here? press h to get some help\n");
    while (1) {

        if (scanf("%c", &buff) != 1) {
            break;
        }
        switch (buff)
        {
        case '\n':
            break;
        case '1':
            printf("You have chose to create a new vault\n");
            return 0;
        case '2':
            printf("You have chose to unlock an existing vault\n");
            return 0;
        case '3':
            printf("Password manager closing, goodbye :)\n");
            return 0;
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