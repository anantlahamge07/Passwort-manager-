#include <stdio.h>
#include <stdlib.h>

int main(void) {

    printf("Welcome to the password manager!\n");
    printf("===================================\n");
    printf("        PASSWORD MANAGER\n");
    printf("===================================\n");
    char buff[3];
    printf("Heyo! What would you like this time?\n");
    fgets(buff, sizeof(buff), stdin);

    return 0;
}