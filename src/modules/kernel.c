#include <stdio.h>
#include <string.h>
#include <sys/utsname.h>
#include "kernel.h"

int get_kernel_version(char* kernel_version, char* buffer, size_t buffer_size){
    memset(buffer, 0, buffer_size);
    struct utsname unameData;

    if (uname(&unameData) == -1 ){
        return -1;
    }

    strncpy(kernel_version, unameData.sysname, sizeof(unameData.sysname));
    kernel_version[buffer_size - 1] = '\0';

    strncpy(buffer, unameData.release, buffer_size - 1);
    buffer[buffer_size - 1] = '\0';

    strncat(kernel_version, " ", buffer_size - strlen(kernel_version) - 1);
    strncat(kernel_version, unameData.release, buffer_size - strlen(kernel_version) - 1);

    if (kernel_version != "") {
        return 0;
    }
    return -1;
}