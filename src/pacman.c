#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#include "headers/pacman.h"
#include "headers/helpers.h"

void show_map(data *data)
{
    for (short int row = 0; row < data->input.rows; row++)
    {
        puts(data->input.original[row]);
    }
}

//TODO: definir no arquivo .h, MAS E UMA FUNCAO TEMPORARIA
void debug_maps(data *data)
{
    for (short int row = 0; row < data->input.rows; row++)
    {
        printf("%s", data->input.original[row]);
    }

    puts("");

    for (short int row = 0; row < data->input.rows; row++)
    {
        printf("%s", data->output.trail[row]);
    }
}

void create_starter_file(input *input)
{
    char *start_file = create_output_files_path(
        input->directory,
        START_FILE_NAME
    );

    FILE *file = fopen(start_file, "w");

    for (short int row = 0; row < input->rows; row++)
    {
        fprintf(file, "%s\n", input->original[row]);
    }

    fprintf(file, "Pac-Man comecara o jogo na linha %hu e coluna %hu\n",
        input->pacman.row,
        input->pacman.column
    );

    fclose(file);
}

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

//TODO: definir no arquivo .h
void move_pacman(data *data, char moviment)
{
    data->output.moviments_without_food++;

    switch (moviment)
    {
        case 'w': {
            data->output.w_statistics.moviments++;

            if (is_wall_w(&data->input))
            {
                data->output.w_statistics.moviments_wall_colision++;

                update_summary_file(&data->output, moviment, MESSAGE_WALL_COLISION);
            }

            if (is_food_w(&data->input))
            {
                data->output.moviments_without_food--;
                data->output.w_statistics.moviments_food_taken++;

                update_summary_file(&data->output, moviment, MESSAGE_FOOD_TAKEN);

                if (data->output.food == data->input.total_food)
                {}
            }
        }
    }
}

//TODO: definir no arquivo .h
int is_wall_w(input *input)
{
    if (input->pacman.row - 1 == 0 ||
        input->original[input->pacman.row - 1][input->pacman.column] == '#'
    ) {
        return 1;
    }
}

//TODO: definir no arquivo .h
int is_food_w(input *input)
{
    if (input->original[input->pacman.row - 1][input->pacman.column] == '*')
    {
        return 1;
    }
}

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

//TODO: definir no arquivo .h e finalizar logica de fim de jogo
void game_over(data *data)
{
    create_ranking_file(data);
    create_statistics_file(data);
}

//TODO: definir no arquivo .h e desenhar e implementar logica de validacao
int keep_reading(
    int moviments_amount,
    int moviments_limit
)
{}

void destroy(data *data)
{
    for (short int index = 0; index < data->input.ghosts.amount; index++)
    {
        free(data->input.ghosts.list[index]);
    }

    for (short int row = 0; row < data->input.rows; row++)
    {
        free(data->output.trail[row]);
        free(data->input.original[row]);
    }

    free(data->output.trail);
    free(data->input.original);
    free(data->input.directory);
    free(data->input.ghosts.list);
}

void destroy_multiple(short int amount, ...)
{
    va_list valist;
    va_start(valist, amount);

    for (short int counter = 0; counter < amount; counter++) {
        free(va_arg(valist, void *));
    }

    va_end(valist);
}
