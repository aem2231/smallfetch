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
    int num_lines = load_ascii_art(&ascii_art, &longest_line);
    if (num_lines == -1) {
        printf("Error loading ASCII art.\n");
        return 1;
    }

    // Display the output
    printf("%s\n", ascii_art[0]);
    printf("%s HOSTNAME: %s\n",ascii_art[1], hostname);
    printf("%s KERNEL: %s\n", ascii_art[2], kernel_version);
    printf("%s CPU: %s\n", ascii_art[3], cpu_name);
    printf("%s MEMORY: %.2fGB (%.2f%% used)\n", ascii_art[4], mem_total, mem_usage);
    printf("%s PACKAGES: %ld\n", ascii_art[5], packages);
    printf("\n");

    // Free memory allocated by load_ascii_art
    for (int i = 0; i < num_lines; i++) {
        free(ascii_art[i]);
    }
    exit(0);
}
