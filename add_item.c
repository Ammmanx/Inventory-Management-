#include <stdio.h>
#include "inventory.h"

void add_item(char *name){
    char path[100];
    sprintf(path, "data_base/%s_inventory.csv", name);
    FILE *fp= fopen(path, "a");
    if (fp == NULL)
    {
        printf("Error: Can't access item_list");
    }
    //name, id, qty
    char namee[20];
    char id[20];
    int qty;

    printf("Enter name of the item:\n");
    scanf("%s", &namee);
    printf("Enter id of the item:\n");
    scanf("%s", &id);
    printf("Enter quantity of the item:\n");
    scanf("%d", &qty);

    fprintf(fp, "%s,%s,%d\n",id,namee,qty);
    fclose(fp);
    int op, try = 0;

    printf("Enter the details of the next item! (press 1)\n");
    
    printf("Move to main screen. (press 2)\n");
    
    scanf("%d", &op);
    while(!try)
    {
     if (op == 1){
        add_item(name);
        try = 1;
        break;

    }
    else if(op == 2){
        main_screen(name);
        try = 1;
        break;

    }
    else{
        printf("Invalid input!\n");
    }   
    }
    

}