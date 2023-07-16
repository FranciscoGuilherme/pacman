#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#include "headers/pacman.h"
#include "headers/helpers.h"
#include "headers/reports/ranking.h"
#include "headers/reports/summary.h"
#include "headers/reports/statistics.h"
#include "headers/validations/up.h"
#include "headers/validations/down.h"
#include "headers/validations/left.h"
#include "headers/validations/right.h"

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

void move_pacman(data *data, char moviment)
{
    //TODO: movimentar fantasmas
    data->output.moviments_without_food++;

    switch (moviment)
    {
        case PACMAN_UP: {
            data->output.w_statistics.moviments++;

            if (is_wall_up(data->input.original, &data->input.pacman))
            {
                data->output.w_statistics.moviments_wall_colision++;

                update_summary_file(&data->output, moviment, MESSAGE_WALL_COLISION);
            }

            if (is_food_up(data->input.original, &data->input.pacman))
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
    free(data->input.ghosts.list);
    free(data->output.summary_file);
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
