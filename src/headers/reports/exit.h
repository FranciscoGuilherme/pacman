#ifndef _EXIT_H
#define _EXIT_H

#include "../pacman.h"

void update_output_file(data *data, char current_moviment);
void rules_to_write(FILE *file, short int row, short int column, data *data);

#endif
