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
        for (short int column = 0; column < data->input.columns; column++)
        {
            rules_to_show_map(row, column, data);
        }

        printf("\n");
    }
}

void rules_to_show_map(short int row, short int column, data *data)
{
    for (short int amount = 0; amount < data->input.ghosts.amount; amount++)
    {
        if (data->input.ghosts.list[amount]->position.row == row &&
            data->input.ghosts.list[amount]->position.column == column
        ) {
            printf("%c", data->input.ghosts.list[amount]->ghost);

            return;
        }
    }

    printf("%c", data->input.original[row][column]);
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

void move_pacman(data *data, char moviment, int moviment_number)
{
    data->output.moviments_without_food++;

    switch (moviment)
    {
        case PACMAN_UP: pacman_up_actions(data, moviment, moviment_number); return;
        case PACMAN_DOWN: pacman_down_actions(data, moviment, moviment_number); return;
        case PACMAN_LEFT: pacman_left_actions(data, moviment, moviment_number); return;
        case PACMAN_RIGHT: pacman_right_actions(data, moviment, moviment_number); return;
        default: return;
    }
}

void pacman_up_actions(data *data, char moviment, int moviment_number)
{
    data->output.w_statistics.moviments++;

    if (is_wall_up(data->input.original, &data->input.pacman))
    {
        data->output.w_statistics.moviments_wall_colision++;

        update_summary_file(&data->output, moviment, MESSAGE_WALL_COLISION);

        return;
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

    if (is_tunel_up(data->input.original, &data->input.pacman))
    {
        //TODO: implementar teletransporte
    }

    if (is_ghost_up(data->input.original, &data->input.pacman))
    {
        data->output.trail[data->input.pacman.row][data->input.pacman.column] = moviment_number;
        data->input.original[data->input.pacman.row][data->input.pacman.column] = EMPTY;
        data->input.pacman.row -= 1;

        update_summary_file(&data->output, moviment, MESSAGE_GHOST_COLISION);
        game_over(data);

        return;
    }

    data->output.trail[data->input.pacman.row][data->input.pacman.column] = moviment_number;
    data->input.original[data->input.pacman.row][data->input.pacman.column] = EMPTY;
    data->input.original[data->input.pacman.row - 1][data->input.pacman.column] = PACMAN;
    data->input.pacman.row -= 1;
}

void pacman_down_actions(data *data, char moviment, int moviment_number)
{
    data->output.s_statistics.moviments++;

    if (is_wall_down(data->input.original, &data->input.pacman))
    {
        data->output.s_statistics.moviments_wall_colision++;

        update_summary_file(&data->output, moviment, MESSAGE_WALL_COLISION);

        return;
    }

    if (is_food_down(data->input.original, &data->input.pacman))
    {
        data->output.moviments_without_food--;
        data->output.s_statistics.moviments_food_taken++;

        update_summary_file(&data->output, moviment, MESSAGE_FOOD_TAKEN);

        if (data->output.food == data->input.total_food)
        {
            game_over(data);
        }
    }

    if (is_tunel_down(data->input.original, &data->input.pacman))
    {
        //TODO: implementar teletransporte
    }

    if (is_ghost_down(data->input.original, &data->input.pacman))
    {
        data->output.trail[data->input.pacman.row][data->input.pacman.column] = moviment_number;
        data->input.original[data->input.pacman.row][data->input.pacman.column] = EMPTY;
        data->input.pacman.row += 1;

        update_summary_file(&data->output, moviment, MESSAGE_GHOST_COLISION);
        game_over(data);

        return;
    }

    data->output.trail[data->input.pacman.row][data->input.pacman.column] = moviment_number;
    data->input.original[data->input.pacman.row][data->input.pacman.column] = EMPTY;
    data->input.original[data->input.pacman.row + 1][data->input.pacman.column] = PACMAN;
    data->input.pacman.row += 1;
}

void pacman_left_actions(data *data, char moviment, int moviment_number)
{
    data->output.a_statistics.moviments++;

    if (is_wall_left(data->input.original, &data->input.pacman))
    {
        data->output.a_statistics.moviments_wall_colision++;

        update_summary_file(&data->output, moviment, MESSAGE_WALL_COLISION);

        return;
    }

    if (is_food_left(data->input.original, &data->input.pacman))
    {
        data->output.moviments_without_food--;
        data->output.a_statistics.moviments_food_taken++;

        update_summary_file(&data->output, moviment, MESSAGE_FOOD_TAKEN);

        if (data->output.food == data->input.total_food)
        {
            game_over(data);
        }
    }

    if (is_tunel_left(data->input.original, &data->input.pacman))
    {
        //TODO: implementar teletransporte
    }

    if (is_ghost_left(data->input.original, &data->input.pacman))
    {
        data->output.trail[data->input.pacman.row][data->input.pacman.column] = moviment_number;
        data->input.original[data->input.pacman.row][data->input.pacman.column] = EMPTY;
        data->input.pacman.column -= 1;

        update_summary_file(&data->output, moviment, MESSAGE_GHOST_COLISION);
        game_over(data);

        return;
    }

    data->output.trail[data->input.pacman.row][data->input.pacman.column] = moviment_number;
    data->input.original[data->input.pacman.row][data->input.pacman.column] = EMPTY;
    data->input.original[data->input.pacman.row][data->input.pacman.column - 1] = PACMAN;
    data->input.pacman.column -= 1;
}

void pacman_right_actions(data *data, char moviment, int moviment_number)
{
    data->output.d_statistics.moviments++;

    if (is_wall_right(data->input.original, &data->input.pacman))
    {
        data->output.d_statistics.moviments_wall_colision++;

        update_summary_file(&data->output, moviment, MESSAGE_WALL_COLISION);

        return;
    }

    if (is_food_right(data->input.original, &data->input.pacman))
    {
        data->output.moviments_without_food--;
        data->output.d_statistics.moviments_food_taken++;

        update_summary_file(&data->output, moviment, MESSAGE_FOOD_TAKEN);

        if (data->output.food == data->input.total_food)
        {
            game_over(data);
        }
    }

    if (is_tunel_right(data->input.original, &data->input.pacman))
    {
        //TODO: implementar teletransporte
    }

    if (is_ghost_right(data->input.original, &data->input.pacman))
    {
        data->output.trail[data->input.pacman.row][data->input.pacman.column] = moviment_number;
        data->input.original[data->input.pacman.row][data->input.pacman.column] = EMPTY;
        data->input.pacman.column += 1;

        update_summary_file(&data->output, moviment, MESSAGE_GHOST_COLISION);
        game_over(data);
    }

    data->output.trail[data->input.pacman.row][data->input.pacman.column] = moviment_number;
    data->input.original[data->input.pacman.row][data->input.pacman.column] = EMPTY;
    data->input.original[data->input.pacman.row][data->input.pacman.column + 1] = PACMAN;
    data->input.pacman.column += 1;
}

void game_over(data *data)
{
    //create_ranking_file(data);
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
