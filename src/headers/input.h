#ifndef _INPUT_H
#define _INPUT_H

#include "pacman.h"

void directory_is_defined(int condition);
void prepare_map_file_path(char **directory, char **map_file);
void read_data(char **map_file, data *data);
void set_ghost(
    data *data,
    char ghost,
    char direction,
    short int row,
    short int column
);

#endif
