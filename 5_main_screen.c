#include <stdio.h>
#include <stdlib.h>
#include "inventory.h"
void main_screen(char *name){
    int n;
    int try =0;
    printf("Wlecome to your Inventory record\n");
    
    printf("1. Add new item\n");
    printf("2. View all items\n");

    printf("3. search your entries\n");
    printf("4. For closing your inventory!\n");
    

    while (!try)
    {
    printf("What do you want to do?\n");
    scanf("%d", &n);
    switch (n)
    {
    case 1:
        add_item(name);
        try = 1;
        break;
    case 2:
        view_item(name);
        try = 1;
        break;
    case 3:
        search_item(name);
        try = 1;
        break;
    case 4:   
    printf("Closing Inventory...\n");
    exit(0);
    break;
    default:
        printf("Invalid Input\n");
        
    }
    }
    
}