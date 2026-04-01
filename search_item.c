#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "inventory.h"

// ── Safe input helper ──────────────────────────────────────────────
static void safe_input(char *buf, int size) {
    if (fgets(buf, size, stdin)) {
        buf[strcspn(buf, "\n")] = '\0';
        if (strlen(buf) == (size_t)(size - 1)) {
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
        }
    } else {
        buf[0] = '\0';
    }
}

void search_item(char *name) {
    char path[100];
    sprintf(path, "data_base/%s_inventory.csv", name);

    // Check file exists before entering loop
    FILE *test = fopen(path, "r");
    if (test == NULL) {
        printf("Inventory file not found.\n");
        return;
    }
    fclose(test);

    int  searching  = 1;
    char input_buf[20];

    while (searching) {
        char item[20];
        char col1[20];
        char col2[20];
        int  col3;
        int  item_exists = 0;

        // ── Prompt for ID ──────────────────────────────────────────
        printf("\nEnter the ID of the item (or 0 to go to main screen): ");
        safe_input(item, sizeof(item));

        if (strcmp(item, "0") == 0) {
            main_screen(name);
            return;
        }

        // ── Open → skip header → search → close ───────────────────
        FILE *fp = fopen(path, "r");
        if (fp == NULL) {
            printf("Inventory file not found.\n");
            return;
        }

        char header[100];
        fgets(header, sizeof(header), fp);   // skip header row

        while (fscanf(fp, "%19[^,],%19[^,],%d\n", col1, col2, &col3) == 3) {
            if (strcmp(item, col1) == 0) {
                item_exists = 1;
                break;
            }
        }
        fclose(fp);

        // ── Not found ─────────────────────────────────────────────
        if (!item_exists) {
            printf("Item with ID '%s' not found. Please try again.\n", item);
            continue;
        }

        // ── Found: show details ────────────────────────────────────
        printf("\nItem found:\n");
        printf("  ID       : %s\n", col1);
        printf("  Name     : %s\n", col2);
        printf("  Quantity : %d\n", col3);

        // ── Action menu ────────────────────────────────────────────
        int menu_active = 1;
        while (menu_active) {
            printf("\n[1] Search another item\n");
            printf("[2] Edit this item\n");
            printf("[3] Delete this item\n");
            printf("[4] Back to main screen\n");
            printf("Your choice: ");

            safe_input(input_buf, sizeof(input_buf));
            int choose = atoi(input_buf);

            switch (choose) {

                case 1:
                    // Exit menu, outer loop re-prompts for new ID
                    menu_active = 0;
                    break;

                case 2:
                    edit_item(col1, col2, col3, name);
                    printf("\n[1] Search another item\n");
                    printf("[2] Back to main screen\n");
                    printf("Your choice: ");
                    safe_input(input_buf, sizeof(input_buf));
                    if (atoi(input_buf) == 1) {
                        menu_active = 0;
                    } else {
                        menu_active = 0;
                        searching   = 0;
                        main_screen(name);
                    }
                    break;

                case 3:
                    delete_item(col1, name);
                    // After delete, item no longer exists — go back to search
                    printf("\n[1] Search another item\n");
                    printf("[2] Back to main screen\n");
                    printf("Your choice: ");
                    safe_input(input_buf, sizeof(input_buf));
                    if (atoi(input_buf) == 1) {
                        menu_active = 0;       // outer loop re-prompts
                    } else {
                        menu_active = 0;
                        searching   = 0;
                        main_screen(name);
                    }
                    break;

                case 4:
                    menu_active = 0;
                    searching   = 0;
                    main_screen(name);
                    break;

                default:
                    printf("Invalid choice. Please enter 1, 2, 3, or 4.\n");
                    break;
            }
        }
    }
}
