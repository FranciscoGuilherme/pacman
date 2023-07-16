#ifndef _LEFT_H
#define _LEFT_H

#include "../pacman.h"

int is_wall_left(char **map, coordenates *coordenates);
int is_food_left(char **map, coordenates *coordenates);
int is_tunel_left(char **map, coordenates *coordenates);
int is_player_left(char **map, coordenates *coordenates);

#endif
