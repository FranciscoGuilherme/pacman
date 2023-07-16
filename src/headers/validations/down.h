#ifndef _DOWN_H
#define _DOWN_H

#include "../pacman.h"

int is_wall_down(char **map, coordenates *coordenates);
int is_food_down(char **map, coordenates *coordenates);
int is_tunel_down(char **map, coordenates *coordenates);
int is_player_down(char **map, coordenates *coordenates);

#endif
