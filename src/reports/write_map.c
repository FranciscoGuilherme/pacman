#include <stdio.h>

#include "../headers/reports/write_map.h"

void rules_to_write(FILE *file, short int row, short int column, input *input)
{
    for (short int amount = 0; amount < input->ghosts.amount; amount++)
    {
        if (input->ghosts.list[amount]->position.row == row &&
            input->ghosts.list[amount]->position.column == column
        ) {
            fprintf(file, "%c", input->ghosts.list[amount]->ghost);

            return;
        }
    }

    fprintf(file, "%c", input->original[row][column]);
}
