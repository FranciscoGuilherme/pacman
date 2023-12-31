#ifndef _RANKING_H
#define _RANKING_H

#include "../pacman.h"
#include "../structures/draw.h"
#include "../structures/output.h"

void create_ranking_file(data *data);
void create_rank(draw *draw, output *output, char *ranking, char context);
void create_rank_by_context(draw *draw, output *output, char *ranking, char context, short int (*context_statistics)(struct output_data *, char));
draw validate_draw(output *output, char *ranking, short int (*context_statistics)(struct output_data *, char));
short int get_food_statistics(output *output, char letter);
void set_biggest_value(ranking *ranking, char letter, short int number);
void set_lowest_value(ranking *ranking, char letter, short int number);
ranking get_biggest_food_rank(data *data, char letter);
ranking get_lowest_wall_rank(data *data, char letter);

#endif
