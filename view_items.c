#include <stdio.h>
#include "inventory.h"

void view_item(char *name){
    char path[100];
    sprintf(path, "data_base/%s_inventory.csv", name);
    FILE *fp= fopen(path, "r");
    if (fp == NULL)
    {
        printf("Error: Your database is empty.\n");
    }
    
    char col1[20];
    char col2[20];
    char header[100];
    int col3;
    int choose;
    int t = 0;
    fgets(header, sizeof(header), fp);
    printf("\n%-10s %-20s %-10s\n", "ID", "ITEM NAME", "QTY");
   while (fscanf(fp, "%[^,],%[^,],%d\n", col1, col2, &col3) != EOF) {
        printf("%-10s %-20s %-10d\n", col1, col2, col3);
    }
    fclose(fp);
    while(!t){
            printf("Move to  main scree: press 1\n");
            printf("For searching any itme from the given list: press 2\n");
            scanf("%d", &choose);
            switch (choose)
            {
            case 1:
                main_screen(name);
                t = 1;
                break;
            case 2:
                search_item(name);
                t = 1;
                break;
           
                
            default:
             printf("Choose from these 3: ");
             
                
            }
        }
}