#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include "create_directory.h"

int create_directory(const char *path) {
    struct stat stats;

    if (stat(path, &stats) != 0) {
        mkdir(path, 0700);
        return 0;
    }

    // Return 1 if the folder for the given project name is already present
    return 1;
}