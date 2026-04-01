#include <stdio.h>
#include <conio.h>
#include "inventory.h"

void get_password(char *password) {
    int i = 0;
    char ch;

    // 13 is the ASCII code for Enter
    while ((ch = getch()) != 13) {
        if (ch == 8) { // 8 is Backspace
            if (i > 0) {
                i--;
                printf("\b \b"); // Erase the * from screen
            }
        } else if (i < 19) { // Max password length 19 + null
            password[i++] = ch;
            printf("*");
        }
    }
    password[i] = '\0'; // End the string
    printf("\n"); // Move to next line after Enter is pressed
}