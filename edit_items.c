#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "inventory.h"

void edit_item(char col1[], char col2[], int col3, char *name) {
    char path1[100];
    char path2[100];
    char n[20] = "temp";
    file_create(n);
    sprintf(path1, "data_base/%s_inventory.csv", name);
    sprintf(path2, "data_base/%s_inventory.csv", n);

    // Step 1: Show item and get user choice
    printf("This is your selected item:\n");
    printf("ID: %s, Name: %s, Quantity: %d\n", col1, col2, col3);
    printf("Press 1 to change the id of the item:\n");
    printf("Press 2 to change the name of the item:\n");
    printf("Press 3 to change the quantity of the item:\n");

    int choose;
    scanf("%d", &choose);

    char new_id[20];
    char new_name[20];
    int new_qty;

    // Step 2: Get new value based on choice
    switch (choose) {
        case 1:
            printf("Enter the new ID of the item: ");
            scanf("%s", new_id);
            break;
        case 2:
            printf("Enter the new name of the item: ");
            scanf("%s", new_name);
            break;
        case 3:
            printf("Enter the new quantity of the item: ");
            scanf("%d", &new_qty);
            break;
        default:
            printf("Please select from the above three!\n");
            fclose(fopen(path2, "w"));  // close temp cleanly
            return;
    }

    // Step 3: Open both files
    FILE *fp      = fopen(path1, "r");
    FILE *temp_fp = fopen(path2, "w");

    if (fp == NULL || temp_fp == NULL) {
        printf("Error opening files.\n");
        return;
    }

    // Step 4: Read each line, match target, write to temp
    char line[100];
    char r_id[20], r_name[20];
    int  r_qty;

    while (fgets(line, sizeof(line), fp)) {
        // Parse the CSV line
        if (sscanf(line, "%[^,],%[^,],%d", r_id, r_name, &r_qty) != 3) {
            // If line doesn't parse (e.g. header), write it as-is
            fputs(line, temp_fp);
            continue;
        }

        // Check if this is the target record
        if (strcmp(r_id, col1) == 0) {
            // Apply the selected modification
            switch (choose) {
                case 1: strcpy(r_id,   new_id);           break;
                case 2: strcpy(r_name, new_name);         break;
                case 3:        r_qty = new_qty;           break;
            }
        }

        // Write (possibly updated) record to temp
        fprintf(temp_fp, "%s,%s,%d\n", r_id, r_name, r_qty);
    }

    // Step 5: Close both files
    fclose(fp);
    fclose(temp_fp);

    // Step 6: Remove original, rename temp → original
    remove(path1);
    rename(path2, path1);

    printf("Item updated successfully!\n");
}