#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include "create_file.h"

int create_file(const char *path, const char *content) {

    // opens file with write access
    FILE *file = fopen(path, "w");
    if (file == NULL) {
        perror("Could not create file");
        return 1;
    }

    // writes content to file
    if (fprintf(file, "%s", content) < 0) {
        perror("Could not write to file\n");
        fclose(file);

        // returns 1 if it fails to write content to file
        return 1;
    }

    // Closes opened file
    if (fclose(file) != 0) {
        perror("Could not close file\n");
        return 1;
    }
    return 0;
}