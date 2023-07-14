#include <stdio.h>

#include "../headers/pacman.h"
#include "../headers/reports/statistics.h"

void create_statistics_file(data *data)
{
    char *statistics_file = create_output_files_path(
        data->input.directory,
        STATISTICS_FILE_NAME
    );
    int moviments_done =
        data->output.w_statistics.moviments +
        data->output.a_statistics.moviments +
        data->output.s_statistics.moviments +
        data->output.d_statistics.moviments;
    short int moviments_wall_colision =
        data->output.w_statistics.moviments_wall_colision +
        data->output.a_statistics.moviments_wall_colision +
        data->output.s_statistics.moviments_wall_colision +
        data->output.d_statistics.moviments_wall_colision;

    FILE *file = fopen(statistics_file, "w");
    fprinf(file, "Numero de movimentos: %d\n", moviments_done);
    fprinf(file, "Numero de movimentos sem pontuar: %d\n", data->output.moviments_without_food);
    fprinf(file, "Numero de colisoes com parede: %d\n", moviments_wall_colision);
    fprinf(file, "Numero de movimentos para baixo: %d\n", data->output.s_statistics.moviments);
    fprinf(file, "Numero de movimentos para cima: %d\n", data->output.w_statistics.moviments);
    fprinf(file, "Numero de movimentos para esquerda: %d\n", data->output.a_statistics.moviments);
    fprinf(file, "Numero de movimentos para direita: %d\n", data->output.d_statistics.moviments);
    fclose(file);
}
