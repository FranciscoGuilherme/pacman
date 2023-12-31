#include <stdlib.h>
#include <string.h>

#include "headers/pacman.h"
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

void ascending_order(char *chars_list)
{
    char temp;
    int length = strlen(chars_list);

    for (int i = 0; i < length - 1; i++)
    {
        for (int j = i + 1; j < length; j++)
        {
            if (chars_list[i] > chars_list[j])
            {
                temp = chars_list[i];
                chars_list[i] = chars_list[j];
                chars_list[j] = temp;
            }
        }
    }
}

int check_content(char content, char expect_content)
{
    if (content == expect_content)
    {
        return IT_IS_TRUE;
    }

    return IT_IS_FALSE;
}
