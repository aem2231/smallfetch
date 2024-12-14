#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <math.h>

int get_ram_info(long* mem, long* mem_available, long* mem_usage){
    FILE* fp;
    char buffer[256];
    char umem[256];
    char umem_available[256];

    fp = fopen("/proc/meminfo", "r");
    if (fp == NULL){
        perror("Unable to get ram info: '/proc/meminfo' not found.");
        return -1;
    }

    for (int i = 0; i<3; i++){
        if(fgets(buffer, sizeof(buffer), fp) != NULL){
            switch (i) {
                case 0:
                    strncpy(umem, buffer, sizeof(buffer));
                    umem[sizeof(umem) - 1] = '\0';
                    break;
                case 2:
                    strncpy(umem_available, buffer, sizeof(buffer));
                    umem_available[sizeof(umem_available) - 1] = '\0';
                    break;
                default:
                    continue;
            }
        }
    }
    fclose(fp);

    char *p_umem = umem;
    while (*p_umem != '\0' && !isdigit(*p_umem)) {
        p_umem++;
    }

    if (*p_umem != '\0') {
        *mem = strtol(p_umem, &p_umem, 10);
    }

    char *p_umem_available = umem_available;
    while (*p_umem_available != '\0' && !isdigit(*p_umem_available)) {
        p_umem_available++;
    }

    if (*p_umem_available != '\0') {
        *mem_available = strtol(p_umem_available, &p_umem_available, 10);
    }

    *mem_usage = ((*mem - *mem_available) / *mem) * 100;

    return 0;
}
