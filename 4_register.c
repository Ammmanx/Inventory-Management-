#include <stdio.h>
#include <string.h>
#include "inventory.h"

void reg(){
     char ID[20];
    char f_id[20];
    
    printf("Create Login ID: ");
    scanf("%19s", ID);  // Prevent buffer overflow
    
    int try = 0;
    while(try == 0)
    {
        FILE *fp = fopen("id.csv", "r");
        
        // If file doesn't exist, it's the first user - no duplicates possible
        if (fp == NULL)
        {
            try = 1;  // Exit loop, ID is unique
            break;
        }
        
        int id_exists = 0;
        while (fscanf(fp, "%19[^,]%*[^\n]\n", f_id) != EOF)
        // the %* will read the rest of the line without collecting the data.
        // Read until comma, skip rest
        {
            if (strcmp(ID, f_id) == 0)
            {
                id_exists = 1;
                break;
            }
        }
        fclose(fp);  // Always close before potentially re-opening
        
        if (id_exists == 1) {
            printf("Error: ID already exists. Please try a different one.\n");
            printf("Create Login ID: ");
            scanf("%19s", ID);
            // try remains 0, loop continues
        } else {
            try = 1; // ID is unique
        }
    }
    
        char Pass[20];
        char CPass[20];
        while (1)
        {
            FILE *fp = fopen("id.csv", "a");
                if (fp == NULL)
             {
            printf("Error: Could not access database!\n");
                }

            printf("Create Password: ");
            get_password(Pass);

            printf("Confirm Password: ");
            get_password(CPass);

            if (strcmp(Pass, CPass) == 0)
            {
                fprintf(fp, "%s,%s\n", ID, Pass);
                fclose(fp);
                file_create(ID);
                printf("User registered successfully!\n");
                main_screen(ID);
                break;
            }
            else
            {
                printf("Error: Passwords do not match. Try again.\n");
            }
            fclose(fp);
        }
        
}