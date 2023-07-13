#include "headers/output.h"

short int get_food_statistics(output *output, char letter)
{
    switch (letter)
    {
        case 'w': return output->w_statistics.moviments_food_taken;
        case 'a': return output->a_statistics.moviments_food_taken;
        case 's': return output->s_statistics.moviments_food_taken;
        case 'd': return output->d_statistics.moviments_food_taken;
    }
}

short int get_wall_statistics(output *output, char letter)
{
    switch (letter)
    {
        case 'w': return output->w_statistics.moviments_wall_colision;
        case 'a': return output->a_statistics.moviments_wall_colision;
        case 's': return output->s_statistics.moviments_wall_colision;
        case 'd': return output->d_statistics.moviments_wall_colision;
    }
}

short int get_moviments_statistics(output *output, char letter)
{
    switch (letter)
    {
        case 'w': return output->w_statistics.moviments;
        case 'a': return output->a_statistics.moviments;
        case 's': return output->s_statistics.moviments;
        case 'd': return output->d_statistics.moviments;
    }
}
