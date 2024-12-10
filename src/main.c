#include "header.h"

int main() {
    char filename[100];
    char command[10];
    printf("File name: ");
    scanf("%99s", filename);

    open_and_view_file(filename);
    while (1) {
        printf("\nType a command \n");
        scanf("%9s", command);
        if (strcmp(command, "/h") == 0) {
            givehelp();
        } else if (strcmp(command, "/i") == 0) {
            give_insert(filename);
        } else if (strcmp(command, "/v") == 0) { 
            open_and_view_file(filename); 
        } else if(strcmp(command, "/e") == 0){
            give_edit(filename);
        } else if (strcmp(command, "/q") == 0) { 
            printf("Exiting. . .\n");
            break;  
        } else {
            printf("Command not found. Type '/q' to exit.\n");
        }
    }

    return 0;
}
