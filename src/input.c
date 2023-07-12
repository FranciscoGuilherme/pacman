#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "headers/pacman.h"

void directory_is_defined(int condition)
{
    check_error(condition, "ERRO: O diretorio de arquivos de configuracao nao foi informado");
}

void prepare_map_file_path(char **directory, char **map_file)
{
    short int length = strlen(*directory) + strlen(MAP_FILE_NAME) + 2;

    *map_file = calloc(length, sizeof(char));
    strcpy(*map_file, *directory);
    strcat(*map_file, "/");
    strcat(*map_file, MAP_FILE_NAME);
}

void set_ghost(
    data *data,
    char ghost,
    char direction,
    short int row,
    short int column
) {
    if (!data->input.ghosts.amount)
    {
        data->input.ghosts.amount = 1;
        data->input.ghosts.list = (struct ghost **) malloc(sizeof(struct ghost *));
        data->input.ghosts.list[0] = (struct ghost *) malloc(sizeof(struct ghost));
        data->input.ghosts.list[0]->ghost = ghost;
        data->input.ghosts.list[0]->direction = direction;
        data->input.ghosts.list[0]->position.row = row;
        data->input.ghosts.list[0]->position.column = column;
    }

    if (data->input.ghosts.list)
    {
        data->input.ghosts.amount++;
        data->input.ghosts.list = (struct ghost **) realloc(
            data->input.ghosts.list,
            data->input.ghosts.amount * sizeof(struct ghost *)
        );
        data->input.ghosts.list[data->input.ghosts.amount - 1] = (struct ghost *) malloc(sizeof(struct ghost));
        data->input.ghosts.list[data->input.ghosts.amount - 1]->ghost = ghost;
        data->input.ghosts.list[data->input.ghosts.amount - 1]->direction = direction;
        data->input.ghosts.list[data->input.ghosts.amount - 1]->position.row = row;
        data->input.ghosts.list[data->input.ghosts.amount - 1]->position.column = column;
    }
}

void read_map(FILE *map_file, data *data)
{
    for (short int row = 0; row < data->input.rows; row++)
    {
        data->output.trail[row] = (char *) calloc(data->input.columns + 1, sizeof(char));
        data->input.original[row] = (char *) calloc(data->input.columns + 1, sizeof(char));

        for (short int column = 0; column < data->input.columns; column++)
        {
            check_read(fscanf(map_file, "%1[^\n]%*[\n]", &data->input.original[row][column]));

            data->output.trail[row][column] = '#';

            switch (data->input.original[row][column])
            {
                case 'B': set_ghost(data, 'B', 'L', row, column); break;
                case 'P': set_ghost(data, 'P', 'U', row, column); break;
                case 'I': set_ghost(data, 'I', 'D', row, column); break;
                case 'C': set_ghost(data, 'C', 'R', row, column); break;
                case '*': data->input.total_food++; break;
                case '>': {
                    data->input.pacman.row = row + 1;
                    data->input.pacman.column = column + 1;
                    data->output.trail[row][column] = '0';
                }
            }
        }
    }
}

void read_data(char **map_file, data *data)
{
    FILE *file = fopen(*map_file, "r");

    check_error(file, "Nao foi possivel ler o aquivo: %s", *map_file);
    check_read(fscanf(file, "%hu%*c", &data->input.rows));
    check_read(fscanf(file, "%hu%*c", &data->input.columns));
    check_read(fscanf(file, "%d%*[\n]", &data->input.moviments));

    data->output.food = 0;
    data->output.trail = (char **) malloc(data->input.rows * sizeof(char *));
    data->input.original = (char **) malloc(data->input.rows * sizeof(char *));

    read_map(file, data);
    fclose(file);
}
