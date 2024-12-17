#include <stdio.h>
#include <string.h>
#include <ncurses.h>
#include "cpu.h"
#include "hostname.h"
#include "kernel.h"
#include "memory.h"
#include "packages.h"

int main(){
    double mem_total, mem_free, mem_usage;
    long packages;
    char hostname[256], kernel_version[256], cpu_name[256];

    if (get_cpu_model(cpu_name, sizeof(cpu_name)) == -1) {
        strncpy(cpu_name, "Unknown", sizeof(cpu_name) / sizeof(cpu_name[0]) - 1);
        cpu_name[sizeof(cpu_name) / sizeof(cpu_name[0]) - 1] = '\0';
    };
    if (get_hostname(hostname, sizeof(hostname)) == -1) {
        strncpy(hostname, "Unknown", sizeof(hostname) / sizeof(hostname[0]) - 1);
        hostname[sizeof(hostname) / sizeof(hostname[0]) - 1] = '\0';
    };
    if (get_ram_info(&mem_total, &mem_free, &mem_usage) == -1) {
        mem_total = 0;
        mem_free = 0;
        mem_usage = 0;
    };
    if (get_kernel_version(kernel_version, sizeof(kernel_version)) == -1) {
        strncpy(kernel_version, "Unknown", sizeof(kernel_version) / sizeof(kernel_version[0]) - 1);
        kernel_version[sizeof(kernel_version) / sizeof(kernel_version[0]) - 1] = '\0';
    };
    if (get_packages(&packages) == -1) {
        packages = 0;
    };

    printf("\uF108  %s \n", hostname);
    printf("\uF17C  %s \n", kernel_version);
    printf("\uF4BC  %s \n", cpu_name);
    printf("\uEFC5  %.2f / %.2f (%.2f%%)\n", (mem_total - mem_free), mem_total, mem_usage);
    printf("\uED95  %ld\n", packages);

    //hostname
    //kernel
    //cpu
    //ram_usage
    //packages
}