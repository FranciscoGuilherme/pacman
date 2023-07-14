#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "headers/input.h"
#include "headers/pacman.h"
#include "headers/helpers.h"

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
        SUMMARY_FILE_NAME
    );
}

int main(int argc, char *argv[])
{
    data data;
    char *map_file;
    char current_moviment;

    directory_is_defined(argc > 1);
    initialize(&data, argv);
    destroy_initial_parameters(argc, argv);
    prepare_map_file_path(&data.input.directory, &map_file);
    read_data(&map_file, &data);
    create_starter_file(&data.input);
    free(map_file);

    for (int amount = 0; amount < data.input.moviments; amount++)
    {
        show_map(&data);
        check_read(fscanf(stdout, "%c%*c", &current_moviment));
        move_pacman(&data, current_moviment);
    }

    destroy(&data);

    return 0;
}
