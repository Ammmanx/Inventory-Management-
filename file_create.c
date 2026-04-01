#include <stdio.h>
#include "inventory.h"
#include <stdlib.h>

void file_create(char *name){
    char path[100];
    sprintf(path, "data_base/%s_inventory.csv", name);
    FILE *user_file = fopen(path, "w");
    if (user_file != NULL) {
        // Add headers so the CSV is easy to read in Excel
        fprintf(user_file, "Item_ID,Item_Name,Item_Quantity\n");
        fclose(user_file);
        printf("Personal inventory file '%s' created!\n", path);
    }
    


}