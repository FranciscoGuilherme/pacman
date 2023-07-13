#ifndef _OUTPUT_H
#define _OUTPUT_H

typedef struct statistics
{
    unsigned long long int moviments: 32;
    unsigned long long int moviments_food_taken: 12;
    unsigned long long int moviments_wall_colision: 8;
} statistics;

typedef struct output_data
{
    char **trail;
    char *summary_file;
    statistics w_statistics;
    statistics a_statistics;
    statistics s_statistics;
    statistics d_statistics;
    int moviments_without_food;
    unsigned short int food;
} output;

short int get_food_statistics(output *output, char letter);
short int get_wall_statistics(output *output, char letter);
short int get_moviments_statistics(output *output, char letter);

#endif
