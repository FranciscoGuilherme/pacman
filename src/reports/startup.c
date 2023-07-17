#include <stdio.h>
#include <stdlib.h>

#include "../headers/pacman.h"
#include "../headers/helpers.h"

void create_startup_file(input *input)
{
    char *start_file = create_output_files_path(
        input->directory,
        FILE_NAME_START
    );

    FILE *file = fopen(start_file, "w");

    for (short int row = 0; row < input->rows; row++)
    {
        fprintf(file, "%s\n", input->original[row]);
    }

    fprintf(file, "Pac-Man comecara o jogo na linha %hu e coluna %hu\n",
        input->pacman.row + 1,
        input->pacman.column + 1
    );

    fclose(file);
    free(start_file);
}
