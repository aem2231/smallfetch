#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "hostname.h"

#define MAX_HOST_LENGTH 256

int get_hostname(char* host_name, size_t hostname_size){
    if (gethostname(host_name, hostname_size) == - 1) {
        printf("Unable to get hostname.");
        strncpy(host_name, "Unknown", hostname_size - 1);
        host_name[hostname_size - 1] = '\0';
        return -1;
    }
    return 0;
}