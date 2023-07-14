#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#include "headers/pacman.h"
#include "headers/helpers.h"
#include "headers/reports/summary.h"
#include "headers/reports/statistics.h"

void show_map(data *data)
{
    for (short int row = 0; row < data->input.rows; row++)
    {
        puts(data->input.original[row]);
    }
}

//TODO: definir no arquivo .h, MAS E UMA FUNCAO TEMPORARIA
void debug_maps(data *data)
{
    for (short int row = 0; row < data->input.rows; row++)
    {
        printf("%s", data->input.original[row]);
    }

    puts("");

    for (short int row = 0; row < data->input.rows; row++)
    {
        printf("%s", data->output.trail[row]);
    }
}

void create_starter_file(input *input)
{
    char *start_file = create_output_files_path(
        input->directory,
        START_FILE_NAME
    );

    FILE *file = fopen(start_file, "w");

    for (short int row = 0; row < input->rows; row++)
    {
        fprintf(file, "%s\n", input->original[row]);
    }

    fprintf(file, "Pac-Man comecara o jogo na linha %hu e coluna %hu\n",
        input->pacman.row,
        input->pacman.column
    );

    fclose(file);
}

void move_pacman(data *data, char moviment)
{
    //TODO: movimentar fantasmas
    data->output.moviments_without_food++;

    switch (moviment)
    {
        case 'w': {
            data->output.w_statistics.moviments++;

            if (is_wall_w(&data->input))
            {
                data->output.w_statistics.moviments_wall_colision++;

                update_summary_file(&data->output, moviment, MESSAGE_WALL_COLISION);
            }

            if (is_food_w(&data->input))
            {
                data->output.moviments_without_food--;
                data->output.w_statistics.moviments_food_taken++;

                update_summary_file(&data->output, moviment, MESSAGE_FOOD_TAKEN);

                if (data->output.food == data->input.total_food)
                {
                    game_over(data);
                }
            }

            //TODO: validar se for fantasma atualizar no resumo.txt
            //TODO: validar se for tunel
        }
    }
}

int is_wall_w(input *input)
{
    if (input->pacman.row - 1 == 0 ||
        input->original[input->pacman.row - 1][input->pacman.column] == '#'
    ) {
        return 1;
    }
}

int is_food_w(input *input)
{
    if (input->original[input->pacman.row - 1][input->pacman.column] == '*')
    {
        return 1;
    }
}

void game_over(data *data)
{
    create_ranking_file(data);
    create_statistics_file(data);
}

void destroy(data *data)
{
    for (short int index = 0; index < data->input.ghosts.amount; index++)
    {
        free(data->input.ghosts.list[index]);
    }

    for (short int row = 0; row < data->input.rows; row++)
    {
        free(data->output.trail[row]);
        free(data->input.original[row]);
    }

    free(data->output.trail);
    free(data->input.original);
    free(data->input.directory);
    free(data->input.ghosts.list);
}

void destroy_multiple(short int amount, ...)
{
    va_list valist;
    va_start(valist, amount);

    for (short int counter = 0; counter < amount; counter++) {
        free(va_arg(valist, void *));
    }

    va_end(valist);
}
