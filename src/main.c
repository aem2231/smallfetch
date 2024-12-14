#include <stdio.h>
#include <math.h>
#include "cpu.h"
#include "hostname.h"
#include "kernel.h"
#include "memory.h"

int main(){
    long mem, mem_available, mem_usage, packages;
    char hostname[256], kernel_version[256], cpu_name[256];

    get_cpu_model(cpu_name, sizeof(cpu_name));
    get_hostname(hostname, sizeof(hostname));
    get_kernel_version(kernel_version, sizeof(kernel_version));
    get_ram_info(&mem, &mem_available, &mem_usage);
    int mem_gb = mem / 1024^2;
    int mem_available_gb = mem_available / 1024^2;


    printf("%s \n", cpu_name);
    printf("%s \n", hostname);
    printf("%s \n", kernel_version);
    printf("%d Gb\n", mem_gb);
    printf("%d Gb\n", mem_available_gb);
    printf("%ld %%", mem_usage);


    //hostname
    //kernel
    //cpu
    //ram_usage
    //packages
}