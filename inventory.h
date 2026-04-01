#ifndef INVENTORY_H
// ifndef(this means if not defined flag checks.)
#define INVENTORY_H
//define (after checking it will define the flag if it dosent exist.)

// Function declaration
void login();
void reg();
void sign_in();
void main_screen(char *name);
void get_password(char *password);
void file_create(char *name);
void add_item(char *name);
void view_item(char *name);
void search_item(char *name);
void edit_item(char col1[],char col2[],int col3, char *name);
void delete_item(char *col1, char *name);


#endif
// endif (ifndef ends here to avoid multiple inclusions of the same header file)