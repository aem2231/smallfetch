#include <stdio.h>
#include <string.h>
#include "cpu.h"

int get_cpu_model(char* cpu_name){
    FILE* fp;
    char line[256];
    char substring[256];
    char unstripped_cpu_name[256];

    fp = fopen("/proc/cpuinfo", "r");
    if (fp == NULL) {
        printf("Unable to get cpu model: '/proc/cpuinfo' not found.");
        cpu_name = "Unknown";
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
    // TODO: Add code to strip cpu name from line
    strcpy(cpu_name, unstripped_cpu_name);
    return 0;
}