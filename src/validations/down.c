#include "../headers/pacman.h"
#include "../headers/helpers.h"
#include "../headers/validations/down.h"

int is_wall_down(char **map, coordenates *coordenates)
{
    return check_content(map[coordenates->row + 1][coordenates->column], WALL);
}

int is_food_down(char **map, coordenates *coordenates)
{
    return check_content(map[coordenates->row + 1][coordenates->column], FOOD);
}

int is_tunel_down(char **map, coordenates *coordenates)
{
    return check_content(map[coordenates->row + 1][coordenates->column], TUNEL);
}

int is_player_down(char **map, coordenates *coordenates)
{
    return check_content(map[coordenates->row + 1][coordenates->column], PLAYER);
}
