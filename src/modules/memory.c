#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int get_memory(double* mem_total, double* mem_free, double* mem_usage){
    char buffer[256];

    FILE *fp = fopen("/proc/meminfo", "r");
    if (fp == NULL){
        return -1;
    }

    while (fgets(buffer, sizeof(buffer), fp) != NULL){
        if (sscanf(buffer, "MemTotal: %lf kB", mem_total) == 1) {
            *mem_total = *mem_total / (1024 * 1024);
            continue;
        }
        if (sscanf(buffer, "MemAvailable: %lf kB", mem_free) == 1) {
            *mem_free = *mem_free / (1024 * 1024);
            break;
        }
    }
    fclose(fp);

    *mem_usage = ((double)(*mem_total - *mem_free) / *mem_total) * 100;

    if (*mem_usage > 0 && *mem_free > 0 && *mem_total > 0) {
        return 0;
    }
    return -1;
}