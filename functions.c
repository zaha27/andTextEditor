#include "header.h"

void open_and_view_file(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Eroare la deschiderea fișierului");
        return;
    }

    char line[MAX_LINE];
    printf("---- Conținutul fișierului '%s' ----\n", filename);
    while (fgets(line, MAX_LINE, file)) {
        printf("%s", line);
    }
    fclose(file);

    printf("\n---- Vizualizare terminată ----\n");
}