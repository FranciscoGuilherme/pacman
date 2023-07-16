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

void create_starter_file(input *input)
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
        input->pacman.row,
        input->pacman.column
    );

    fclose(file);
    free(start_file);
}

void move_ghosts(data *data)
{
    for (short int amount = 0; amount < data->input.ghosts.amount; amount++)
    {
        switch (data->input.ghosts.list[amount]->direction)
        {
            case GHOST_UP: ghost_up_actions(data, data->input.ghosts.list[amount]); return;
            case GHOST_DOWN: ghost_down_actions(data, data->input.ghosts.list[amount]); return;
            case GHOST_LEFT: ghost_left_actions(data, data->input.ghosts.list[amount]); return;
            case GHOST_RIGHT: ghost_right_actions(data, data->input.ghosts.list[amount]); return;
            default: return;
        }
    }
}

void ghost_up_actions(data *data, ghost *ghost)
{
    //TODO: implementar um jeito de marcar colisao com fantasma.
    if (is_wall_up(&data->input.original, &ghost->position)) ghost->direction = GHOST_DOWN;
    if (is_tunel_up(&data->input.original, &ghost->position)) //TODO: implementar teleporte para ghost
    if (is_player_up(&data->input.original, &ghost->position)) {
        ghost->position.row -= 1;
        game_over(data);
    }
}

void ghost_down_actions(data *data, ghost *ghost)
{
    //TODO: implementar um jeito de marcar colisao com fantasma.
    if (is_wall_down(&data->input.original, &ghost->position)) ghost->direction = GHOST_DOWN;
    if (is_tunel_down(&data->input.original, &ghost->position)) //TODO: implementar teleporte para ghost
    if (is_player_down(&data->input.original, &ghost->position)) {
        ghost->position.row += 1;
        game_over(data);
    }
}

void ghost_left_actions(data *data, ghost *ghost)
{
    //TODO: implementar um jeito de marcar colisao com fantasma.
    if (is_wall_left(&data->input.original, &ghost->position)) ghost->direction = GHOST_DOWN;
    if (is_tunel_left(&data->input.original, &ghost->position)) //TODO: implementar teleporte para ghost
    if (is_player_left(&data->input.original, &ghost->position)) {
        ghost->position.column -= 1;
        game_over(data);
    }
}

void ghost_right_actions(data *data, ghost *ghost)
{
    //TODO: implementar um jeito de marcar colisao com fantasma.
    if (is_wall_right(&data->input.original, &ghost->position)) ghost->direction = GHOST_DOWN;
    if (is_tunel_right(&data->input.original, &ghost->position)) //TODO: implementar teleporte para ghost
    if (is_player_right(&data->input.original, &ghost->position)) {
        ghost->position.column += 1;
        game_over(data);
    }
}

void move_pacman(data *data, char moviment)
{
    //TODO: movimentar fantasmas
    data->output.moviments_without_food++;

    switch (moviment)
    {
        case 'w': {
            data->output.w_statistics.moviments++;

            if (is_wall_up(&data->input.original, &data->input.pacman))
            {
                data->output.w_statistics.moviments_wall_colision++;

                update_summary_file(&data->output, moviment, MESSAGE_WALL_COLISION);
            }

            if (is_food_up(&data->input.original, &data->input.pacman))
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
