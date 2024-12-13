#include <stdio.h>
#include "cpu.h"
#include "hostname.h"

int main(){
    int ram, ram_usage, packages;
    char hostname[256], kernel_version[256], cpu_name[256];

    get_cpu_model(cpu_name, sizeof(cpu_name));
    get_hostname(hostname, sizeof(hostname));
    printf("%s", cpu_name);
    printf("%s", hostname);
}


