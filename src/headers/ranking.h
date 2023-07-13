#ifndef _RANKING_H
#define _RANKING_H

#include "headers/pacman.h"
#include "structures/headers/draw.h"

void create_statistics_file(data *data);
draw *validate_draw(output *output, char *ranking, short int (*context_statistics)(void *, char));
short int get_food_statistics(output *output, char letter);
void set_biggest_value(ranking *ranking, char letter, short int number);
void set_lowest_value(ranking *ranking, char letter, short int number);
ranking get_biggest_food_rank(data *data, char letter);
ranking get_lowest_wall_rank(data *data, char letter);

#endif
