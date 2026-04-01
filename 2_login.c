#include <stdio.h>
#include "inventory.h"
// this is the login function implementation file
#include <stdlib.h>
#include <conio.h>
#include <string.h>

void login()
{
    printf("Welcome Sir!\n");
    printf("Login(Existing User): Press 1\nSignup(New User): Press 2\n");
    int choice;
    scanf("%d", &choice);
    switch (choice)
    {
    case 1:
        sign_in();
        break;
    case 2:
        reg();
        break;
    
    default:
        printf("please Enter a valid input!\n");
        break;
    }

}