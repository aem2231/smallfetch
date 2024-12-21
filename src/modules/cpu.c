#include <stdio.h>
#include <string.h>

int get_cpu_model(char *cpu_name, char *buffer, size_t buffer_size) {
    memset(buffer, 0, buffer_size);
    FILE *fp = fopen("/proc/cpuinfo", "r");
    if (fp == NULL) {
        return -1;
    }

    while (fgets(buffer, buffer_size, fp)) {
        if (strncmp(buffer, "model name", 10) == 0) {
            if (sscanf(buffer, "model name : %255[^\n]", cpu_name) == 1) {
                fclose(fp);
                return 0;
            }
        }
    }
    fclose(fp);
    return -1;
}