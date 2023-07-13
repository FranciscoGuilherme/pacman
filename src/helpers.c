#include <stdlib.h>
#include <string.h>

#include "headers/helpers.h"

char *create_output_files_path(char *directory, char *file_base_name)
{
    short int length =
        strlen(directory) +
        strlen("/saida/") +
        strlen(file_base_name) + 1;
    char *file = (char *) calloc(length, sizeof(char));

    strcpy(file, directory);
    strcat(file, "/saida/");
    strcat(file, file_base_name);

    return file;
}
