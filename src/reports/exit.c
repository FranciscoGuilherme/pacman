#include <stdio.h>
#include <stdlib.h>

#include "../headers/helpers.h"
#include "../headers/reports/exit.h"

void update_output_file(data *data, char current_moviment)
{
    char *output_file = create_output_files_path(
        data->input.directory,
        FILE_NAME_OUTPUT
    );

    FILE *file = fopen(output_file, "a");

    if (file == NULL)
    {
        file = fopen(output_file, "w");
    }

    fprintf(file, "Estado do jogo apos o movimento '%c':\n", current_moviment);

    for (short int row = 0; row < data->input.rows; row++)
    {
        for (short int column = 0; column < data->input.columns; column++)
        {
            rules_to_write(file, row, column, data);
        }

        fprintf(file, "\n");
    }

    fprintf(file, "Pontuacao: %d\n\n",
        data->output.w_statistics.moviments_food_taken +
        data->output.a_statistics.moviments_food_taken +
        data->output.s_statistics.moviments_food_taken +
        data->output.d_statistics.moviments_food_taken
    );

    fclose(file);
    free(output_file);
}

void rules_to_write(FILE *file, short int row, short int column, data *data)
{
    for (short int amount = 0; amount < data->input.ghosts.amount; amount++)
    {
        if (data->input.ghosts.list[amount]->position.row == row &&
            data->input.ghosts.list[amount]->position.column == column
        ) {
            fprintf(file, "%c", data->input.ghosts.list[amount]->ghost);

            return;
        }
    }

    fprintf(file, "%c", data->input.original[row][column]);
}
