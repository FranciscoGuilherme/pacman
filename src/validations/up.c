#include "../headers/pacman.h"
#include "../headers/helpers.h"
#include "../headers/validations/up.h"

int is_wall_up(char **map, coordenates *coordenates)
{
    return check_content(map[coordenates->row - 1][coordenates->column], WALL);
}

int is_food_up(char **map, coordenates *coordenates)
{
    return check_content(map[coordenates->row - 1][coordenates->column], FOOD);
}

int is_tunel_up(char **map, coordenates *coordenates)
{
    return check_content(map[coordenates->row - 1][coordenates->column], TUNEL);
}

int is_ghost_up(char **map, coordenates *coordenates)
{
    return check_content(map[coordenates->row - 1][coordenates->column], 'B')
        || check_content(map[coordenates->row - 1][coordenates->column], 'P')
        || check_content(map[coordenates->row - 1][coordenates->column], 'I')
        || check_content(map[coordenates->row - 1][coordenates->column], 'C');
}

int is_player_up(char **map, coordenates *coordenates)
{
    return check_content(map[coordenates->row - 1][coordenates->column], PACMAN);
}