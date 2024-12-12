#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

void remove_non_int(char *line) {
    int j = 0;

    for (int i = 0; line[i] != '\0'; i++){
        if (isdigit(line[i])){
            line[j++] = line[i];
        }
    }
    line[j] = '\0';
}


int get_meminfo(int *memtotal_kb, int *memavailable_kb) {
    FILE *pmeminfo = fopen("/proc/meminfo", "r");

    if (pmeminfo == NULL) {
        perror("Error opening file.");
        return 1;
    }

    char line[256];

    while (fgets(line, sizeof(line), pmeminfo) != NULL) {
        if (strncmp(line, "MemTotal", 8) == 0){
            remove_non_int(line);
            *memtotal_kb = atoi(line);
        }
        if (strncmp(line, "MemAvailable", 12) == 0){
            remove_non_int(line);
            *memavailable_kb = atoi(line);
            break;
        }
    }
    fclose(pmeminfo);
    return 0;
}

int get_cpu_name(char *cpu_name) {
    FILE* pcpuinfo = fopen("/proc/cpuinfo", "r");

    if (pcpuinfo == NULL) {
        perror("Error opening file");
        return 1;
    }

    char line[256];
    while (fgets(line, sizeof(line), pcpuinfo) != NULL) {
        if (strncmp(line, "model name", 10) == 0) {
            int length = strlen(line) - 13;
            strncpy(cpu_name, line + 13, length);
            cpu_name[length] = '\0';
            break;
        }
    }
    fclose(pcpuinfo);
    return 0; // Successful completion
}

int main(void) {
    int memtotal_kb;
    int memavailable_kb;
    char cpu_name[50];

    get_meminfo(&memtotal_kb, &memavailable_kb);
    get_cpu_name(cpu_name);
    int mem_in_use = ((memtotal_kb - memavailable_kb) * 100) / memtotal_kb;
    printf("%d %% of memory currently in use.\n", mem_in_use);
    printf("%s", cpu_name);
}