#include <stdio.h>
#include <string.h>

int get_cpu_model(char* cpu_name, size_t cpu_name_size) {
    char buffer[256];

    FILE *fp = fopen("/proc/cpuinfo", "r");
    if (fp == NULL) {
        return -1;
    }

    while (fgets(buffer, sizeof(buffer), fp)) {
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