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

void givehelp() {
    printf("Available commands:\n");
    printf("/h - Show help\n");
    printf("/v - View the file again\n");
    printf("/e - Edit the file\n");
    printf("/i - Enter Insert mode\n");
    printf("/ai - Enter Advanced Insert mode\n");
    printf("/q - Quit\n");
}

#include "header.h"

void give_edit(const char *filename) {
    FILE *file = fopen(filename, "r+");
    if (!file) {
        perror("Eroare la deschiderea fișierului pentru editare");
        return;
    }

    printf("\n---- Conținutul fișierului '%s' ----\n", filename);
    char line[MAX_LINE];
    int line_number = 0;

    while (fgets(line, MAX_LINE, file)) {
        printf("%d: %s", ++line_number, line);
    }
    rewind(file); 

    int choice;
    printf("\nOpțiuni de editare:\n");
    printf("1. Adaugă linie nouă\n");
    printf("2. Șterge o linie\n");
    printf("3. Modifică o linie existentă\n");
    printf("4. Salvează și închide\n");

    while (1) {
        printf("\nAlege o opțiune (1-4): ");
        scanf("%d", &choice);

        if (choice == 1) {
            printf("Scrie linia pe care vrei să o adaugi: ");
            getchar(); 
            char new_line[MAX_LINE];
            fgets(new_line, MAX_LINE, stdin);

            fseek(file, 0, SEEK_END);
            fprintf(file, "%s", new_line);
            printf("Linia a fost adăugată.\n");
        } else if (choice == 2) {
            printf("Numărul liniei de șters: ");
            int delete_line;
            scanf("%d", &delete_line);

            FILE *temp_file = fopen("temp.txt", "w");
            if (!temp_file) {
                perror("Eroare la crearea fișierului temporar");
                fclose(file);
                return;
            }

            rewind(file);
            int current_line = 0;
            while (fgets(line, MAX_LINE, file)) {
                current_line++;
                if (current_line != delete_line) {
                    fputs(line, temp_file);
                }
            }
            fclose(file);
            fclose(temp_file);

            remove(filename);
            rename("temp.txt", filename);
            file = fopen(filename, "r+");
            printf("Linia %d a fost ștearsă.\n", delete_line);
        } else if (choice == 3) {
            printf("Numărul liniei de modificat: ");
            int edit_line;
            scanf("%d", &edit_line);

            printf("Scrie noul conținut pentru linia %d: ", edit_line);
            getchar(); 
            char edited_line[MAX_LINE];
            fgets(edited_line, MAX_LINE, stdin);

            FILE *temp_file = fopen("temp.txt", "w");
            if (!temp_file) {
                perror("Eroare la crearea fișierului temporar");
                fclose(file);
                return;
            }

            rewind(file);
            int current_line = 0;
            while (fgets(line, MAX_LINE, file)) {
                current_line++;
                if (current_line == edit_line) {
                    fputs(edited_line, temp_file);
                } else {
                    fputs(line, temp_file);
                }
            }
            fclose(file);
            fclose(temp_file);

            remove(filename);
            rename("temp.txt", filename);
            file = fopen(filename, "r+");
            printf("Linia %d a fost modificată.\n", edit_line);
        } else if (choice == 4) {
            fclose(file);
            printf("Editarea a fost salvată. Ieșire.\n");
            break;
        } else {
            printf("Opțiune invalidă. Încearcă din nou.\n");
        }
    }
}

void give_insert(const char *filename) {
    FILE *file = fopen(filename, "a");  
    if (!file) {
        perror("Eroare la deschiderea fișierului pentru modul Insert");
        return;
    }

    printf("\n--- Mod Insert ---\n");
    printf("Introduceți textul pe care doriți să-l adăugați. Tastați ':q' pe o linie separată pentru a ieși.\n");

    char line[MAX_LINE];
    while (1) {
        printf("> ");
        fgets(line, MAX_LINE, stdin);

        if (strcmp(line, "q\n") == 0) {
            printf("--- Ieșire din mod Insert ---\n");
            break;
        }
        fputs(line, file);
    }

    fclose(file);
}

void give_advanced_insert(const char *filename) {
    FILE *file = fopen(filename, "r+"); 
    if (!file) {
        perror("Eroare la deschiderea fisierului pentru modul Insert");
        return;
    }

    char lines[100][MAX_LINE];
    int total_lines = 0;
    printf("\n---- Continutul fisierului '%s' ----\n", filename);
    while (fgets(lines[total_lines], MAX_LINE, file)) {
        printf("%d: %s", total_lines + 1, lines[total_lines]);
        total_lines++;
    }
    printf("\n--- Mod Insert ---\n");
    printf("Comenzi disponibile:\n");
    printf("a <text>   - Adauga o linie noua\n");
    printf("d <număr>  - Sterge linia specificata\n");
    printf("m <număr>  - Modifică linia specificata\n");
    printf("q          - Salveaza si iesi\n");

    char command[MAX_LINE];
    while (1) {
        printf("> ");
        fgets(command, MAX_LINE, stdin);

        if (strcmp(command, "q\n") == 0) {
            break;
        }

        if (strncmp(command, "a", 2) == 0) {
            char *new_line = command + 3; 
            strcpy(lines[total_lines], new_line);
            total_lines++;
            printf("Linia a fost adăugata.\n");
        }
        else if (strncmp(command, "d", 2) == 0) {
            int line_to_delete = atoi(command + 3);
            if (line_to_delete < 1 || line_to_delete > total_lines) {
                printf("Linie invalida!\n");
            } else {
                for (int i = line_to_delete - 1; i < total_lines - 1; i++) {
                    strcpy(lines[i], lines[i + 1]);
                }
                total_lines--;
                printf("Linia %d a fost stearsa.\n", line_to_delete);
            }
        }
        else if (strncmp(command, "m", 2) == 0) {
            int line_to_modify = atoi(command + 3);
            if (line_to_modify < 1 || line_to_modify > total_lines) {
                printf("Linie invalidă!\n");
            } else {
                printf("Scrie noul text pentru linia %d: ", line_to_modify);
                fgets(lines[line_to_modify - 1], MAX_LINE, stdin);
                printf("Linia %d a fost modificată.\n", line_to_modify);
            }
        }
        else {
            printf("Comandă necunoscută. Încearcă din nou.\n");
        }
    }
    freopen(filename, "w", file);
    for (int i = 0; i < total_lines; i++) {
        fputs(lines[i], file);
    }
    fclose(file);

    printf("--- Modificările au fost salvate. Ieșire din mod Insert ---\n");
}
