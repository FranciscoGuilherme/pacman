#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "headers/input.h"
#include "headers/ghost.h"
#include "headers/pacman.h"
#include "headers/helpers.h"
#include "headers/reports/startup.h"

void initialize(data *data, char **argv)
{
    data->output.food = 0;
    data->input.total_food = 0;
    data->input.ghosts.amount = 0;
    data->input.directory = argv[1];
    data->output.moviments_without_food = 0;
    data->output.w_statistics.moviments = 0;
    data->output.w_statistics.moviments_food_taken = 0;
    data->output.w_statistics.moviments_wall_colision = 0;
    data->output.a_statistics.moviments = 0;
    data->output.a_statistics.moviments_food_taken = 0;
    data->output.a_statistics.moviments_wall_colision = 0;
    data->output.s_statistics.moviments = 0;
    data->output.s_statistics.moviments_food_taken = 0;
    data->output.s_statistics.moviments_wall_colision = 0;
    data->output.d_statistics.moviments = 0;
    data->output.d_statistics.moviments_food_taken = 0;
    data->output.d_statistics.moviments_wall_colision = 0;
    data->output.summary_file = create_output_files_path(
        data->input.directory,
        FILE_NAME_SUMMARY
    );
}

int main(int argc, char *argv[])
{
    data data;
    char *map_file;
    char current_moviment;

    directory_is_defined(argc > 1);
    initialize(&data, argv);

    (void) argc;
    (void) argv;

    prepare_map_file_path(&data.input.directory, &map_file);
    read_data(&map_file, &data);
    create_startup_file(&data.input);
    free(map_file);

    for (int amount = 0; amount < data.input.moviments; amount++)
    {
        show_map(&data);
        check_read(fscanf(stdout, "%c%*c", &current_moviment));
        move_pacman(&data, current_moviment);
        move_ghosts(&data, current_moviment);
    }

    destroy(&data);

    return 0;
}
