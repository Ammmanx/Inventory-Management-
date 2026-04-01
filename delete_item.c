#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "inventory.h"

// ── Safe input helper ──────────────────────────────────────────────
static void safe_input_d(char *buf, int size) {
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

void delete_item(char *col1, char *name) {
    char path1[100];
    char path2[100];

    sprintf(path1, "data_base/%s_inventory.csv", name);
    sprintf(path2, "data_base/temp_inventory.csv");

    // ── Open original (read) and temp (write) ─────────────────────
    FILE *fp      = fopen(path1, "r");
    FILE *temp_fp = fopen(path2, "w");

    if (fp == NULL || temp_fp == NULL) {
        printf("Error opening files.\n");
        if (fp)      fclose(fp);
        if (temp_fp) fclose(temp_fp);
        return;
    }

    // ── Confirm before deleting ────────────────────────────────────
    char confirm[5];
    printf("\nAre you sure you want to delete item ID '%s'? (yes/no): ", col1);
    safe_input_d(confirm, sizeof(confirm));

    if (strcmp(confirm, "yes") != 0) {
        printf("Delete cancelled.\n");
        fclose(fp);
        fclose(temp_fp);
        remove(path2);   // remove empty temp file
        return;
    }

    // ── Copy header ────────────────────────────────────────────────
    char header[100];
    if (fgets(header, sizeof(header), fp)) {
        fputs(header, temp_fp);
    }

    // ── Read each line: skip target, copy rest ─────────────────────
    char r_id[20], r_name[20];
    int  r_qty;
    int  deleted = 0;

    while (fscanf(fp, "%19[^,],%19[^,],%d\n", r_id, r_name, &r_qty) == 3) {
        if (strcmp(r_id, col1) == 0) {
            deleted = 1;       // skip this record — this is the delete
            continue;
        }
        fprintf(temp_fp, "%s,%s,%d\n", r_id, r_name, r_qty);
    }

    // ── Close both files ───────────────────────────────────────────
    fclose(fp);
    fclose(temp_fp);

    if (deleted) {
        // ── Remove original, rename temp → original ────────────────
        remove(path1);
        rename(path2, path1);
        printf("Item ID '%s' deleted successfully.\n", col1);
    } else {
        remove(path2);
        printf("Item ID '%s' not found. Nothing deleted.\n", col1);
    }
}