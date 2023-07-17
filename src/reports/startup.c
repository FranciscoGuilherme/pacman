#include <stdio.h>
#include <stdlib.h>

#include "../headers/pacman.h"
#include "../headers/helpers.h"
#include "../headers/reports/write_map.h"

void create_startup_file(input *input)
{
    char *startup_file = create_output_files_path(
        input->directory,
        FILE_NAME_START
    );

    FILE *file = fopen(startup_file, "w");

    for (short int row = 0; row < input->rows; row++)
    {
        for (short int column = 0; column < input->columns; column++)
        {
            rules_to_write(file, row, column, input);
        }

        fprintf(file, "\n");
    }

    fprintf(file, "Pac-Man comecara o jogo na linha %hu e coluna %hu\n",
        input->pacman.row + 1,
        input->pacman.column + 1
    );

    fclose(file);
    free(startup_file);
}
