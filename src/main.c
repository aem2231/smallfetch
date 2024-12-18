#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <threads.h>
#include "cpu.h"
#include "hostname.h"
#include "kernel.h"
#include "memory.h"
#include "packages.h"
#include "loadascii.h"

int main() {
    double mem_total, mem_free, mem_usage;
    long packages;
    char hostname[256], kernel_version[256], cpu_name[256];
    char **ascii_art = NULL;
    int longest_line = 0;
    int num_lines = 0;

    if (get_cpu_model(cpu_name) == -1) {
        strncpy(cpu_name, "Unknown", sizeof(cpu_name) / sizeof(cpu_name[0]) - 1);
        cpu_name[sizeof(cpu_name) / sizeof(cpu_name[0]) - 1] = '\0';
    }
    if (get_hostname(hostname, sizeof(hostname)) == -1) {
        strncpy(hostname, "Unknown", sizeof(hostname) / sizeof(hostname[0]) - 1);
        hostname[sizeof(hostname) / sizeof(hostname[0]) - 1] = '\0';
    }
    if (get_memory(&mem_total, &mem_free, &mem_usage) == -1) {
        mem_total = 0;
        mem_free = 0;
        mem_usage = 0;
    }
    if (get_kernel_version(kernel_version, sizeof(kernel_version)) == -1) {
        strncpy(kernel_version, "Unknown", sizeof(kernel_version) / sizeof(kernel_version[0]) - 1);
        kernel_version[sizeof(kernel_version) / sizeof(kernel_version[0]) - 1] = '\0';
    }
    if (get_packages(&packages) == -1) {
        packages = 0;
    }
    if (load_ascii_art(&ascii_art, &longest_line, &num_lines) == -1) {
        ascii_art = NULL;
        printf("Error loading ASCII art.\n"
               "Please make sure the ASCII art file exists at ~/.config/smallfetch/ascii.txt.\n");
        return -1;
    }

    // Custom colors
    const char *ascii_art_color = "\033[38;2;243;139;168m"; // Red (for ASCII art)
    const char *label_color = "\033[38;2;250;179;135m";     // Peach (for labels)
    const char *info_color = "\033[38;2;255;255;255m";      // White (for system info)
    const char *reset_color = "\033[0m";                    // Reset to default color

    printf("%s%s\n", ascii_art_color, ascii_art[0]); // ASCII art line 1
    printf("%s%s %sHOSTNAME: %s%s%s\n", ascii_art_color, ascii_art[1], label_color, info_color, hostname, reset_color);
    printf("%s%s %sKERNEL: %s%s%s\n", ascii_art_color, ascii_art[2], label_color, info_color, kernel_version, reset_color);
    printf("%s%s %sCPU: %s%s%s\n", ascii_art_color, ascii_art[3], label_color, info_color, cpu_name, reset_color);
    printf("%s%s %sMEMORY: %s%.2f / %s%.2f (%.2f%% used)%s\n",
       ascii_art_color,
       ascii_art[4],
       label_color,
       info_color,
       (mem_total - mem_free), // Used memory
       info_color,
       mem_total, // Total memory
       ((mem_total - mem_free) / mem_total) * 100, // Percentage of used memory
       reset_color); // This was confusing as shit

    printf("%s%s %sPACKAGES: %s%ld%s\n", ascii_art_color, ascii_art[5], label_color, info_color, packages, reset_color);
    printf("\n");

    // Free memory allocated by load_ascii_art
    for (int i = 0; i < num_lines; i++) {
        free(ascii_art[i]);
    }
    exit(0);
}
