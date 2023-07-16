#include "../headers/pacman.h"
#include "../headers/helpers.h"
#include "../headers/validations/left.h"

int is_wall_left(char **map, coordenates *coordenates)
{
    return check_content(map[coordenates->row][coordenates->column - 1], WALL);
}

int is_food_left(char **map, coordenates *coordenates)
{
    return check_content(map[coordenates->row][coordenates->column - 1], FOOD);
}

int is_tunel_left(char **map, coordenates *coordenates)
{
    return check_content(map[coordenates->row][coordenates->column - 1], TUNEL);
}

int is_player_left(char **map, coordenates *coordenates)
{
    return check_content(map[coordenates->row][coordenates->column - 1], PLAYER);
}
