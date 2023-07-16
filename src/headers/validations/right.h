#ifndef _RIGHT_H
#define _RIGHT_H

#include "../pacman.h"

int is_wall_right(char **map, coordenates *coordenates);
int is_food_right(char **map, coordenates *coordenates);
int is_tunel_right(char **map, coordenates *coordenates);
int is_player_right(char **map, coordenates *coordenates);

#endif
