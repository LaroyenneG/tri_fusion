#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "tri_fusion.h"

char buffer[BUFFER_SIZE];

static int *tab = NULL;
static size_t tab_len = 0;

void usage() {
    printf("usage : tri_fusion <file>");
}

void addNumber(int number) {
    if (tab == NULL) {
        tab = malloc(sizeof(int));
    } else {
        tab = realloc(tab, sizeof(int) * (tab_len + 1));
    }

    if (tab == NULL) {
        perror("malloc()");
        exit(EXIT_FAILURE);
    }

    tab[tab_len] = number;
    tab_len++;
}

void print_tab() {
    printf("[");
    for (int i = 0; i < tab_len; i++) {
        printf("%d ", tab[i]);
    }
    printf("]\n");
}


int main(int argc, char *argv[]) {

    if (argc != 2) {
        usage();
        exit(EXIT_FAILURE);
    }

    FILE *file = fopen(argv[1], "r");
    if (file == NULL) {
        perror("fopen()");
        exit(EXIT_FAILURE);
    }

    size_t nbRead;
    while ((nbRead = fread(&buffer, sizeof(buffer) / BUFFER_SIZE, BUFFER_SIZE, file)) != 0) {

        int cursor = 0;
        while (cursor < nbRead) {

            size_t string_len = 1;
            char *string = malloc(sizeof(char) * string_len);
            if (string == NULL) {
                perror("malloc()");
                exit(EXIT_FAILURE);
            }

            bool cut = true;
            int i;
            for (i = 0; cursor < nbRead; cursor++, i++) {
                if (buffer[cursor] == ' ' || buffer[cursor] == '\n') {
                    cut = false;
                    break;
                }

                string[string_len - 1] = buffer[cursor];
                string_len++;

                string = realloc(string, sizeof(char) * string_len);
                if (string == NULL) {
                    perror("malloc()");
                    exit(EXIT_FAILURE);
                }
            }

            if (cut && (getc(file) != EOF)) {
                if (fseek(file, -i - 1, SEEK_CUR) < 0) {
                    perror("fseek()");
                    exit(EXIT_FAILURE);
                }
                free(string);
                break;
            }

            if (string_len > 1) {
                string[string_len - 1] = '\0';
                int number = atoi(string);
                addNumber(number);
            }

            free(string);
            cursor++;
        }
    }


    fclose(file);

    tri_fusion(tab, tab_len);

    print_tab();

    free(tab);

    return EXIT_SUCCESS;
}