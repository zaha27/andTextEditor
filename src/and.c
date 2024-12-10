#include "header.h"

//de imp :
//search
//type
// ***undo
//copy
//delete entire rows
//copy all text with a simple command

int main() {
    char filename[100];
    char command[10];

    printf("File name: ");
    scanf("%99s", filename);

    open_and_view_file(filename);

    printf("\nType /q' to exit\n");
    while (1) {
        scanf("%9s", command);
        if (strcmp(command, "/q") == 0) {   //de f funct 
            printf("Exiting. . .\n");
            break;
        } else {
            printf("Command not found. Type '/q' to exit.\n");
        }
    }

    return 0;
}
