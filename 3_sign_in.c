#include <stdio.h>
#include <string.h>
#include "inventory.h"

void sign_in(){
     char lid[20], pass[20];
        int loggedIn = 0;

        // Read the file line by line searching for a match
        // %[^,] reads everything until it hits a comma

        while (!loggedIn)
        {
            FILE *fp = fopen("id.csv", "r"); // 'r' for reading
        if (fp == NULL)
        {
            printf("No users found. Please signup first.\n");
        }
            printf("Enter Login ID: ");
            scanf("%s", lid);
            // %s is a format specifier that read the string until there is some white space or termination.
            char f_id[20], f_pass[20];

            printf("Enter Password: ");
            get_password(pass);

            int found = 0;
            

            while (fscanf(fp, "%[^,],%s\n", f_id, f_pass) != EOF)
            // %[^,] in this % denotes the start scanning, ^ this denotes the carat till whihc it will scan, and on which charachter it will stop scanning that is , here.
            //we can also add the limit till what to scan like %19 means it will scan till 19 char.
            {
                if (strcmp(lid, f_id) == 0 && strcmp(pass, f_pass) == 0)
                //strcmp is used for the comarision of the to strings.
                {
                    
                    found = 1;
                    
                    break;
                }
                
            }
            // 3. ALWAYS close the file after the search loop
    fclose(fp);

    // 4. Check the result AFTER the file loop is done
    if (found == 1) {
        printf("Logged in Successfully!\n");
        loggedIn = 1; // This will break the outer "while (!loggedIn)" loop
    } else {
        printf("Error: Invalid credentials. Please try again.\n");
        // Loop continues because loggedIn is still 0
    }
    
            
        }
        main_screen(lid);
    
}