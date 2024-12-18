#include <stdio.h>
#include <unistd.h>
#include "hostname.h"

#define MAX_HOST_LENGTH 256

int get_hostname(char* host_name, const size_t hostname_size){
    if (gethostname(host_name, hostname_size) == - 1) {
        return -1;
    }
    return 0;
}