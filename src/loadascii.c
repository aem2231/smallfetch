#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int load_ascii_art(char*** ascii_art, int* longest_line) {
    char buffer[256];
    int line_count = 0;
    char* home_dir = getenv("HOME");
    char config_path[512];

    snprintf(config_path, sizeof(config_path), "%s/.config/smallfetch/ascii.txt", home_dir);
    FILE *fp = fopen(config_path, "r");
    if (fp == NULL) {
        return -1;
    }

    *ascii_art = NULL;
    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        buffer[strcspn(buffer, "\n")] = '\0';

        *ascii_art = (char **)realloc(*ascii_art, (line_count + 1) * sizeof(char *));
        if (*ascii_art == NULL) {
            fclose(fp);
            return -1;
        }

        (*ascii_art)[line_count] = (char *)malloc(strlen(buffer) + 1);
        if ((*ascii_art)[line_count] == NULL) {
            fclose(fp);
            return -1;
        }

        if (strlen(buffer) > *longest_line) {
            *longest_line = strlen(buffer);
        }

        strcpy((*ascii_art)[line_count], buffer);
        line_count++;
    }
    fclose(fp);
    return line_count;
}