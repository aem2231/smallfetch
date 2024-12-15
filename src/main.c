#include <stdio.h>
#include <math.h>
#include "cpu.h"
#include "hostname.h"
#include "kernel.h"
#include "memory.h"
#include "packages.h"

int main(){
    double mem, mem_available, mem_usage;
    long packages;
    char hostname[256], kernel_version[256], cpu_name[256];

    get_cpu_model(cpu_name, sizeof(cpu_name));
    get_hostname(hostname, sizeof(hostname));
    get_kernel_version(kernel_version, sizeof(kernel_version));
    get_ram_info(&mem, &mem_available, &mem_usage);
    get_packages(&packages);
    double mem_gb = mem / (1024 * 1024);
    double mem_available_gb = mem_available / (1024 * 1024);

    printf("\uF108  %s \n", hostname);
    printf("\uF17C  %s \n", kernel_version);
    printf("\uF4BC  %s \n", cpu_name);
    printf("\uEFC5  %.2f / %.2f (%.2f%%)\n", mem_gb, mem_available_gb, mem_usage);
    printf("\uED95  %ld\n", packages);


    //hostname
    //kernel
    //cpu
    //ram_usage
    //packages
}