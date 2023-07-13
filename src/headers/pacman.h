#ifndef _PACMAN_H
#define _PACMAN_H

#define MAP_FILE_NAME "mapa.txt"
#define PLAY_FILE_NAME "jogadas.txt"
#define START_FILE_NAME "inicializacao.txt"
#define SUMMARY_FILE_NAME "resumo.txt"
#define RANKING_FILE_NAME "ranking.txt"
#define STATISTICS_FILE_NAME "estatisticas.txt"

#define ERROR_READ_DATA "Erro ao ler os dados de entrada"
#define MESSAGE_FOOD_TAKEN "Movimento %d (%c) pegou comida\n"
#define MESSAGE_WALL_COLISION "Movimento %d (%c) colidiu com a parede\n"
#define MESSAGE_GHOST_COLISION "Movimento %d (%c) fim de jogo por encostar em um fantasma\n"

#define POSSIBLE_MOVIMENTS 4
#define moviments_limit_achieved(number) number == POSSIBLE_MOVIMENTS
#define finalize() printf(" - %s - Linha: %d\n", __FILE__, __LINE__); exit(EXIT_FAILURE);
#define check_error(condition, mesg, ...) \
    if (!condition) { printf(mesg, ##__VA_ARGS__); finalize(); }
#define check_read(reading) check_error(reading, ERROR_READ_DATA)

#include "structures/headers/output.h"

typedef struct ranking
{
    int number;
    char letter;
} ranking;

typedef struct coordenates
{
    unsigned short int row;
    unsigned short int column;
} coordenates;

typedef struct ghost
{
    char ghost;
    char direction;
    coordenates position;
} ghost;

typedef struct ghosts
{
    short int amount;
    ghost **list;
} ghosts;

typedef struct input_data
{
    ghosts ghosts;
    int moviments;
    char **original;
    char *directory;
    coordenates pacman;
    unsigned short int rows;
    unsigned short int columns;
    unsigned short int total_food;
} input;

typedef struct data
{
    input input;
    output output;
} data;

void show_map(data *data);
void create_starter_file(input *input);
void update_summary_file(output *output, char moviment, char *message);
void create_statistics_file(data *data);
void move_pacman(data *data, char moviment);
void destroy(data *data);
void destroy_multiple(short int amount, ...);

#endif
