#ifndef _PACMAN_H
#define _PACMAN_H

#define WALL '#'
#define FOOD '*'
#define TUNEL '@'
#define EMPTY ' '
#define PACMAN '>'
#define GHOST_UP 'U'
#define GHOST_DOWN 'D'
#define GHOST_LEFT 'L'
#define GHOST_RIGHT 'R'
#define PACMAN_UP 'w'
#define PACMAN_DOWN 's'
#define PACMAN_LEFT 'a'
#define PACMAN_RIGHT 'd'
#define IT_IS_TRUE 1;
#define IT_IS_FALSE 0;
#define POSSIBLE_MOVIMENTS 4

#define FILE_NAME_MAP "mapa.txt"
#define FILE_NAME_PLAYS "jogadas.txt"
#define FILE_NAME_START "inicializacao.txt"
#define FILE_NAME_OUTPUT "saida.txt"
#define FILE_NAME_SUMMARY "resumo.txt"
#define FILE_NAME_RANKING "ranking.txt"
#define FILE_NAME_STATISTICS "estatisticas.txt"

#define ERROR_READ_DATA "Erro ao ler os dados de entrada"
#define MESSAGE_FOOD_TAKEN "Movimento %d (%c) pegou comida\n"
#define MESSAGE_WALL_COLISION "Movimento %d (%c) colidiu com a parede\n"
#define MESSAGE_GHOST_COLISION "Movimento %d (%c) fim de jogo por encostar em um fantasma\n"

#define moviments_limit_achieved(number) number == POSSIBLE_MOVIMENTS
#define finalize() printf(" - %s - Linha: %d\n", __FILE__, __LINE__); exit(EXIT_FAILURE);
#define check_error(condition, mesg, ...) \
    if (!condition) { printf(mesg, ##__VA_ARGS__); finalize(); }
#define check_read(reading) check_error(reading, ERROR_READ_DATA)

#include "structures/output.h"

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
void move_pacman(data *data, char moviment, int moviment_number);
void rules_to_show_map(short int row, short int column, data *data);
void pacman_up_actions(data *data, char moviment, int moviment_number);
void pacman_down_actions(data *data, char moviment, int moviment_number);
void pacman_left_actions(data *data, char moviment, int moviment_number);
void pacman_right_actions(data *data, char moviment, int moviment_number);
void game_over(data *data);
void destroy(data *data);
void destroy_multiple(short int amount, ...);

#endif
