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

// Thread argument struct for ASCII art
typedef struct {
    char ***ascii_art;
    int *longest_line;
    int *num_lines;
} ThreadArgs;

// Thread functions
void* cpu_start_routine(void* arg) {
    char* cpu_name = arg;
    if (get_cpu_model(cpu_name) == -1) {
        strncpy(cpu_name, "Unknown", 255);
        cpu_name[255] = '\0';
    }
    return NULL;
}

void* hostname_start_routine(void* arg) {
    char* hostname = arg;
    if (get_hostname(hostname, 256) == -1) {
        strncpy(hostname, "Unknown", 255);
        hostname[255] = '\0';
    }
    return NULL;
}

void* memory_start_routine(void* arg) {
    char* mem_info = arg;
    if (get_memory(mem_info) == -1) {
        strncpy(mem_info, "Unknown", 511);
        mem_info[511] = '\0';
    }
    return NULL;
}

void* kernel_start_routine(void* arg) {
    char* kernel_version = arg;
    if (get_kernel_version(kernel_version, 256) == -1) {
        strncpy(kernel_version, "Unknown", 255);
        kernel_version[255] = '\0';
    }
    return NULL;
}

void* packages_start_routine(void* arg) {
    long* packages = arg;
    if (get_packages(packages) == -1) {
        *packages = 0;
    }
    return NULL;
}

void* ascii_art_start_routine(void* args) {
    ThreadArgs* thread_args = args;

    if (load_ascii_art(thread_args->ascii_art, thread_args->longest_line, thread_args->num_lines) == -1) {
        *(thread_args->ascii_art) = NULL;
    }

    return NULL;
}

int main() {
    // Buffers for data
    long packages;
    char hostname[256] = {0}, kernel_version[256] = {0}, cpu_name[256] = {0}, mem_info[512] = {0};
    char **ascii_art = NULL;
    int longest_line = 0;
    int num_lines = 0;

    // Thread argument for ASCII art
    ThreadArgs ascii_art_args = {&ascii_art, &longest_line, &num_lines};

    // Create threads
    pthread_t threads[6];
    pthread_create(&threads[0], NULL, cpu_start_routine, cpu_name);
    pthread_create(&threads[1], NULL, hostname_start_routine, hostname);
    pthread_create(&threads[2], NULL, memory_start_routine, mem_info);
    pthread_create(&threads[3], NULL, kernel_start_routine, kernel_version);
    pthread_create(&threads[4], NULL, packages_start_routine, &packages);
    pthread_create(&threads[5], NULL, ascii_art_start_routine, &ascii_art_args);

    // Wait for threads to complete
    for (int i = 0; i < 6; i++) {
        pthread_join(threads[i], NULL);
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
