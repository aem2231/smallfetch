#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int load_ascii_art(char*** ascii_art, int* longest_line, int* num_lines) {
    char buffer[256];
    char* home_dir = getenv("HOME");
    char config_path[512];

    snprintf(config_path, sizeof(config_path), "%s/.config/smallfetch/ascii.txt", home_dir);
    FILE *fp = fopen(config_path, "r");
    if (fp == NULL) {
        printf("Error opening ASCII art file.\n");
        return -1;
    }

    *ascii_art = NULL;
    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        buffer[strcspn(buffer, "\n")] = '\0';

        *ascii_art = (char **)realloc(*ascii_art, (*num_lines + 1) * sizeof(char *));
        if (*ascii_art == NULL) {
            fclose(fp);
            for (int i = 0; i < *num_lines; i++) {
                free((*ascii_art)[i]);
            }
            free(*ascii_art);
            *ascii_art = NULL;
            printf("Error reallocating memory.\n");
            return -1;
        }

        (*ascii_art)[*num_lines] = (char *)malloc(strlen(buffer) + 1);
        if ((*ascii_art)[*num_lines] == NULL) {
            fclose(fp);
            for (int i = 0; i < *num_lines; i++) {
                free((*ascii_art)[i]);
            }
            free(*ascii_art);
            *ascii_art = NULL;
            printf("Error allocating memory.\n");
            return -1;
        }

        if (strlen(buffer) > *longest_line) {
            *longest_line = strlen(buffer);
        }

        strcpy((*ascii_art)[*num_lines], buffer);
        (*num_lines)++;
    }
    fclose(fp);
    return *num_lines;
}