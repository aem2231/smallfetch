#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include "cpu.h"
#include "hostname.h"
#include "kernel.h"
#include "memory.h"
#include "packages.h"
#include "loadascii.h"

int main() {
    // Buffers for data
    long packages;
    char hostname[256] = {0}, kernel_version[256] = {0}, cpu_name[256] = {0}, mem_info[512] = {0};
    char **ascii_art = NULL;
    int longest_line = 0;
    int num_lines = 0;
    char buffer[256] = {0};


    if (get_cpu_model(cpu_name, buffer, sizeof(buffer)) == -1) {
        strncpy(cpu_name, "Unknown", 256);
        cpu_name[255] = '\0';
    }
    if (get_hostname(hostname, 256) == 1 ) {
        strncpy(hostname, "Unknown", 255);
        hostname[255] = '\0';
    }
    if (get_kernel_version(kernel_version, buffer, sizeof(buffer)) == -1) {
        strncpy(kernel_version, "Unknown", 255);
        kernel_version[255] = '\0';
    }
    if (get_memory(mem_info, buffer, sizeof(buffer)) == -1) {
        strncpy(mem_info, "Unknown", 256);
        mem_info[255] = '\0';
    }
    if (get_packages(&packages) == -1) {
        packages = 0;
    }
    if (load_ascii_art(&ascii_art, &longest_line, &num_lines, buffer, sizeof(buffer)) == -1) {
        printf("Error loading ascii art. Check ~/.config/smallfetch/ascii.txt.");
        return -1;
    }

    // Custom colors
    const char *ascii_art_color = "\033[38;2;243;139;168m"; // Red (for ASCII art)
    const char *label_color = "\033[38;2;250;179;135m";     // Peach (for labels)
    const char *info_color = "\033[38;2;255;255;255m";      // White (for system info)
    const char *reset_color = "\033[0m";                    // Reset to default color

    // Print results
    printf("%s%s\n", ascii_art_color, ascii_art[0]); // ASCII art line 1
    printf("%s%s %sHOSTNAME: %s%s%s\n", ascii_art_color, ascii_art[1], label_color, info_color, hostname, reset_color);
    printf("%s%s %sKERNEL: %s%s%s\n", ascii_art_color, ascii_art[2], label_color, info_color, kernel_version, reset_color);
    printf("%s%s %sCPU: %s%s%s\n", ascii_art_color, ascii_art[3], label_color, info_color, cpu_name, reset_color);
    printf("%s%s %sMEMORY: %s%s%s\n", ascii_art_color, ascii_art[4], label_color, info_color, mem_info, reset_color);
    printf("%s%s %sPACKAGES: %s%ld%s\n", ascii_art_color, ascii_art[5], label_color, info_color, packages, reset_color);
    printf("\n");


    for (int i = 0; i < num_lines; i++) {
        free(ascii_art[i]);
    }
    free(ascii_art);

    return 0;
}
