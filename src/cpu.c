#include <stdio.h>
#include <string.h>
#include "cpu.h"

int get_cpu_model(char* cpu_name, size_t cpu_name_size){
    FILE* fp;
    char line[256];
    char substring[256];
    char unstripped_cpu_name[256];

    fp = fopen("/proc/cpuinfo", "r");
    if (fp == NULL) {
        printf("Unable to get cpu model: '/proc/cpuinfo' not found.");
        strncpy(cpu_name, "Unknown", cpu_name_size - 1);
        cpu_name[cpu_name_size - 1 ] = '\0';
        return 0;
    }
    while (fgets(line, 256, fp)){
        strncpy(substring, line, 10);
        substring[10] = '\0';
        if (strcmp(substring, "model name") == 0){
            strcpy(unstripped_cpu_name, line);
            unstripped_cpu_name[sizeof(unstripped_cpu_name) - 1] = '\0';
            break;
        }
    }
    fclose(fp);

    char ch = ':';
    const char* pdelimiter = strchr(unstripped_cpu_name, ch);

    if (pdelimiter == NULL) {
        strncpy(cpu_name, unstripped_cpu_name, sizeof(unstripped_cpu_name) - 1);
        cpu_name[cpu_name_size - 1] = '\0';
        return 0;
    }

    pdelimiter++;
    while (*pdelimiter == ' ') {
        pdelimiter++;
    }

    int remaining_length = strlen(pdelimiter);
    if (remaining_length >= cpu_name_size){
        remaining_length = cpu_name_size - 1;
    }

    strncpy(cpu_name, pdelimiter, remaining_length);
    cpu_name[remaining_length] = '\0';
    return 0;
}