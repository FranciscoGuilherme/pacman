#include "headers/ghost.h"
#include "headers/pacman.h"
#include "headers/helpers.h"
#include "headers/reports/summary.h"
#include "headers/validations/up.h"
#include "headers/validations/down.h"
#include "headers/validations/left.h"
#include "headers/validations/right.h"

void move_ghosts(data *data, char moviment)
{
    for (short int amount = 0; amount < data->input.ghosts.amount; amount++)
    {
        switch (data->input.ghosts.list[amount]->direction)
        {
            case GHOST_UP: ghost_up_actions(data, data->input.ghosts.list[amount], moviment); return;
            case GHOST_DOWN: ghost_down_actions(data, data->input.ghosts.list[amount], moviment); return;
            case GHOST_LEFT: ghost_left_actions(data, data->input.ghosts.list[amount], moviment); return;
            case GHOST_RIGHT: ghost_right_actions(data, data->input.ghosts.list[amount], moviment); return;
            default: return;
        }
    }
}

void ghost_up_actions(data *data, ghost *ghost, char moviment)
{
    if (is_wall_up(data->input.original, &ghost->position))
    {
        ghost->direction = GHOST_DOWN;

        return;
    }

    if (is_tunel_up(data->input.original, &ghost->position)) //TODO: implementar teleporte para ghost
    if (is_player_up(data->input.original, &ghost->position))
    {
        ghost->position.row -= 1;

        update_summary_file(&data->output, moviment, MESSAGE_GHOST_COLISION);
        game_over(data);
    }

    ghost->position.row -= 1;
}

void ghost_down_actions(data *data, ghost *ghost, char moviment)
{
    if (is_wall_down(data->input.original, &ghost->position))
    {
        ghost->direction = GHOST_DOWN;

        return;
    }

    if (is_tunel_down(data->input.original, &ghost->position)) //TODO: implementar teleporte para ghost
    if (is_player_down(data->input.original, &ghost->position))
    {
        ghost->position.row += 1;

        update_summary_file(&data->output, moviment, MESSAGE_GHOST_COLISION);
        game_over(data);
    }

    ghost->position.row += 1;
}

void ghost_left_actions(data *data, ghost *ghost, char moviment)
{
    if (is_wall_left(data->input.original, &ghost->position))
    {
        ghost->direction = GHOST_DOWN;

        return;
    }

    if (is_tunel_left(data->input.original, &ghost->position)) //TODO: implementar teleporte para ghost
    if (is_player_left(data->input.original, &ghost->position))
    {
        ghost->position.column -= 1;

        update_summary_file(&data->output, moviment, MESSAGE_GHOST_COLISION);
        game_over(data);
    }

    ghost->position.column -= 1;
}

void ghost_right_actions(data *data, ghost *ghost, char moviment)
{
    if (is_wall_right(data->input.original, &ghost->position))
    {
        ghost->direction = GHOST_DOWN;

        return;
    }

    if (is_tunel_right(data->input.original, &ghost->position)) //TODO: implementar teleporte para ghost
    if (is_player_right(data->input.original, &ghost->position))
    {
        ghost->position.column += 1;

        update_summary_file(&data->output, moviment, MESSAGE_GHOST_COLISION);
        game_over(data);
    }

    ghost->position.column += 1;
}
