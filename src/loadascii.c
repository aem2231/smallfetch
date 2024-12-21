#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int load_ascii_art(char*** ascii_art, int* longest_line, int* num_lines, char* buffer, size_t buffer_size) {
    memset(buffer, 0, buffer_size);
    char* home_dir = getenv("HOME");
    char config_path[512];

    snprintf(config_path, sizeof(config_path), "%s/.config/smallfetch/ascii.txt", home_dir);
    FILE *fp = fopen(config_path, "r");
    if (fp == NULL) {
        printf("Error opening ASCII art file.\n");
        return -1;
    }
    int capacity = 8;
    *ascii_art = (char **)malloc(capacity * sizeof(char *));
    if (*ascii_art == NULL) {
        fclose(fp);
        printf("Error allocating initial memory.\n");
        return -1;
    }

    *num_lines = 0;
    *longest_line = 0;

    // Read lines from the file
    while (fgets(buffer, buffer_size, fp) != NULL) {
        buffer[strcspn(buffer, "\n")] = '\0';

        if (*num_lines >= capacity) {
            capacity *= 2;
            char **temp = (char **)realloc(*ascii_art, capacity * sizeof(char *));
            if (temp == NULL) {
                for (int i = 0; i < *num_lines; i++) {
                    free((*ascii_art)[i]);
                }
                free(*ascii_art);
                fclose(fp);
                *ascii_art = NULL;
                printf("Error reallocating memory.\n");
                return -1;
            }
            *ascii_art = temp;
        }

        size_t line_length = strlen(buffer) + 1;
        (*ascii_art)[*num_lines] = (char *)malloc(line_length);
        if ((*ascii_art)[*num_lines] == NULL) {
            // Free previously allocated lines on malloc failure
            for (int i = 0; i < *num_lines; i++) {
                free((*ascii_art)[i]);
            }
            free(*ascii_art);
            fclose(fp);
            *ascii_art = NULL;
            printf("Error allocating memory for a line.\n");
            return -1;
        }

        strcpy((*ascii_art)[*num_lines], buffer);
        if (line_length - 1 > *longest_line) {
            *longest_line = line_length - 1;
        }
        (*num_lines)++;
    }

    fclose(fp);
    return *num_lines;
}
