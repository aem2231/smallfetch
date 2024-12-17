#include <stdio.h>
#include <string.h>
#include <sys/utsname.h>
#include "kernel.h"

int get_kernel_version(char* kernel_version, size_t kernel_size){
    char version[256];
    struct utsname unameData;

    if (uname(&unameData) == -1 ){
        return -1;
    }

    strncpy(kernel_version, unameData.sysname, sizeof(unameData.sysname));
    kernel_version[kernel_size- 1] = '\0';

    strncpy(version, unameData.release, sizeof(version) - 1);
    version[sizeof(version) - 1] = '\0';

    strncat(kernel_version, " ", kernel_size - strlen(kernel_version) - 1);
    strncat(kernel_version, unameData.release, kernel_size - strlen(kernel_version) - 1);

    if (kernel_version != "") {
        return 0;
    }
    return -1;
}