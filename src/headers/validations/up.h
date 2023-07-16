#ifndef _UP_H
#define _UP_H

#include "../pacman.h"

int is_wall_up(char **map, coordenates *coordenates);
int is_food_up(char **map, coordenates *coordenates);
int is_tunel_up(char **map, coordenates *coordenates);
int is_ghost_up(char **map, coordenates *coordenates);
int is_player_up(char **map, coordenates *coordenates);

#endif
