#include <stdio.h>
#include <string.h>
#include "cpu.h"

/* TODO:
     Ensure code is memory safe
     Null terminate all strings */

int get_cpu_model(char* cpu_name){
    FILE* fp;
    char line[256];
    char substring[256];
    char unstripped_cpu_name[256];

    fp = fopen("/proc/cpuinfo", "r");
    if (fp == NULL) {
        printf("Unable to get cpu model: '/proc/cpuinfo' not found.");
        strcpy(cpu_name, "Unknown");
        return 0;
    }
    while (fgets(line, 256, fp)){
        strncpy(substring, line, 10);
        substring[10] = '\0';
        if (strcmp(substring, "model name") == 0){
            strcpy(unstripped_cpu_name, line);
            break;
        }
    }
    fclose(fp);

    char ch = ':';
    const char* pdelimiter = strchr(unstripped_cpu_name, ch);

    if (pdelimiter == NULL) {
        strcpy(cpu_name, unstripped_cpu_name);
        return 0;
    }

    pdelimiter++;
    while (*pdelimiter == ' ') {
        pdelimiter++;
    }

    int remaining_length = strlen(pdelimiter);
    strncpy(cpu_name, pdelimiter, remaining_length);
    cpu_name[remaining_length] = '\0';
    return 0;
}