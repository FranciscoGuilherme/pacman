#include <stdio.h>

#include "../headers/structures/output.h"

void update_summary_file(output *output, char moviment, char *message)
{
    FILE *file = fopen(output->summary_file, "a");
    int moviments_done =
        output->w_statistics.moviments +
        output->a_statistics.moviments +
        output->s_statistics.moviments +
        output->d_statistics.moviments;

    if (file == NULL)
    {
        file = fopen(output->summary_file, "w");
    }

    fprintf(file, message, moviments_done, moviment);
    fclose(file);
}
