#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

int get_memory(char* mem_info, char* buffer, size_t buffer_size){
    memset(buffer, 0, buffer_size);
    double mem_total;
    double mem_free;

    FILE *fp = fopen("/proc/meminfo", "r");
    if (fp == NULL){
        printf("Error opening /proc/meminfo.\n");
        return -1;
    }

    while (fgets(buffer, buffer_size, fp) != NULL){
        if (sscanf(buffer, "MemTotal: %lf kB", &mem_total) == 1) {
            mem_total = mem_total / (1024 * 1024);
            continue;
        }
        if (sscanf(buffer, "MemAvailable: %lf kB", &mem_free) == 1) {
            mem_free = mem_free / (1024 * 1024);
            break;
        }
    }
    fclose(fp);

    double mem_used = mem_total - mem_free;
    double mem_usage = (mem_used / mem_total) * 100;

    if (mem_usage > 0 && mem_free > 0 && mem_total > 0) {
        snprintf(mem_info, 512, "%.2lf GB / %.2lf GB (%.2lf%%)", mem_used, mem_total, mem_usage);
        return 0;
    }
    return -1;
}
