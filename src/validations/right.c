#include "../headers/pacman.h"
#include "../headers/helpers.h"
#include "../headers/validations/right.h"

int is_wall_right(char **map, coordenates *coordenates)
{
    return check_content(map[coordenates->row][coordenates->column + 1], WALL);
}

int is_food_right(char **map, coordenates *coordenates)
{
    return check_content(map[coordenates->row][coordenates->column + 1], FOOD);
}

int is_tunel_right(char **map, coordenates *coordenates)
{
    return check_content(map[coordenates->row][coordenates->column + 1], TUNEL);
}

int is_player_right(char **map, coordenates *coordenates)
{
    return check_content(map[coordenates->row][coordenates->column + 1], PLAYER);
}
