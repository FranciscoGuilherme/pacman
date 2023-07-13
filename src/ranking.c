#include <stdio.h>
#include <stdlib.h>

#include "headers/pacman.h"
#include "structures/headers/draw.h"

//TODO: finalizar a logica de ranqueamento
void create_ranking_file(data *data)
{
    draw *draw_food;
    draw *draw_wall;
    ranking *partial_ranking;
    char *ranking = calloc(POSSIBLE_MOVIMENTS + 1, sizeof(char));
    char letters[POSSIBLE_MOVIMENTS] = {'w', 'a', 's', 'd'};
    char *ranking_file = create_output_files_path(
        data->input.directory,
        RANKING_FILE_NAME
    );

    for (short int index; index < POSSIBLE_MOVIMENTS; index++)
    {
        partial_ranking = get_biggest_food_rank(data, letters[index]);
        ranking[index] = partial_ranking->letter;
    }

    draw_food = validate_draw(&data->output, &ranking, get_food_statistics);
    create_rank(draw_food, &data->output, ranking, 'f');

    //draw_wall->length = 0;
    //TODO: modularizacao FODA de contextos

    if (!draw_food->length)
    {
        //criar arquivo de ranking
    }

    //TODO: verificar igualdade e separar em grupos

    FILE *file = fopen(ranking_file, "w");
    fprintf(file, "%d\n", 1);
    fclose(file);
}

void create_rank(draw *draw, output *output, char *ranking, char context)
{
    struct draw *aux = NULL;

    switch (context)
    {
        case 'f':
        {
            for (short int index = 0; index < draw->length; index++)
            {
                aux = validate_draw(output, draw->draw_group[index]->moviments, get_wall_statistics);

                //TODO: olhar desempate para movimentos
                //TODO: continuar varrendo as listas
            }

            break;
        }
        case 'w':
        {
            for (short int index = 0; index < draw->length; index++)
            {
                aux = validate_draw(output, draw->draw_group[index]->moviments, get_wall_statistics);

                //TODO: olhar desempate para movimentos
                //TODO: continuar varrendo as listas
            }

            break;
        }
        case 'm':
        {
            for (short int index = 0; index < draw->length; index++)
            {
                aux = validate_draw(output, draw->draw_group[index]->moviments, get_wall_statistics);

                //TODO: olhar desempate para movimentos
                //TODO: continuar varrendo as listas
            }

            break;
        }
        default: return;
    }
}

draw *validate_draw(output *output, char *ranking, short int (*context_statistics)(void *, char))
{
    draw draw;
    short int index = 0;
    short int nearby = 0;
    short int actual = 0;
    short int counter = 1;
    draw.length = 0;

    for (; !moviments_limit_achieved(index + counter); index += counter, counter = 0, counter++)
    {
        if (actual != nearby) add_new_group(&draw);
        push_element_to_group(&draw, 1, ranking[index]);
        actual = (*context_statistics)(output, ranking[index]);
        nearby = (*context_statistics)(output, ranking[index + counter]);

        for (; actual == nearby && !moviments_limit_achieved(index + counter);)
        {
            push_element_to_group(&draw, 1, ranking[index + counter]);

            if (!moviments_limit_achieved(index + (counter++)))
            {
                nearby = (*context_statistics)(output, ranking[index + counter]);
            }
        }
    }

    return &draw;
}

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

void set_biggest_value(ranking *ranking, char letter, short int number)
{
    if (ranking->number < number)
    {
        ranking->number = number;
        ranking->letter = letter;
    }
}

void set_lowest_value(ranking *ranking, char letter, short int number)
{
    if (ranking->number < number)
    {
        ranking->number = number;
        ranking->letter = letter;
    }
}

ranking *get_biggest_food_rank(data *data, char letter)
{
    ranking partial_ranking;

    switch (letter)
    {
        case 'w': partial_ranking.number = data->output.w_statistics.moviments_food_taken; break;
        case 'a': partial_ranking.number = data->output.a_statistics.moviments_food_taken; break;
        case 's': partial_ranking.number = data->output.s_statistics.moviments_food_taken; break;
        case 'd': partial_ranking.number = data->output.d_statistics.moviments_food_taken; break;
    }

    set_biggest_value(&partial_ranking, letter, data->output.w_statistics.moviments_food_taken);
    set_biggest_value(&partial_ranking, letter, data->output.a_statistics.moviments_food_taken);
    set_biggest_value(&partial_ranking, letter, data->output.s_statistics.moviments_food_taken);
    set_biggest_value(&partial_ranking, letter, data->output.d_statistics.moviments_food_taken);

    return &partial_ranking;
}

ranking *get_lowest_wall_rank(data *data, char letter)
{
    ranking partial_ranking;

    switch (letter)
    {
        case 'w': partial_ranking.number = data->output.w_statistics.moviments_wall_colision; break;
        case 'a': partial_ranking.number = data->output.a_statistics.moviments_wall_colision; break;
        case 's': partial_ranking.number = data->output.s_statistics.moviments_wall_colision; break;
        case 'd': partial_ranking.number = data->output.d_statistics.moviments_wall_colision; break;
    }

    set_biggest_value(&partial_ranking, letter, data->output.w_statistics.moviments_wall_colision);
    set_biggest_value(&partial_ranking, letter, data->output.a_statistics.moviments_wall_colision);
    set_biggest_value(&partial_ranking, letter, data->output.s_statistics.moviments_wall_colision);
    set_biggest_value(&partial_ranking, letter, data->output.d_statistics.moviments_wall_colision);

    return &partial_ranking;
}
