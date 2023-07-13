#include <stdio.h>
#include <stdlib.h>

#include "headers/pacman.h"
#include "structures/headers/draw.h"
#include "structures/headers/output.h"

//TODO: finalizar a logica de ranqueamento
void create_ranking_file(data *data)
{
    draw *draw;
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

    draw = validate_draw(&data->output, &ranking, get_food_statistics);
    create_rank(draw, &data->output, ranking, 'f');

    //draw_wall->length = 0;
    //TODO: modularizacao FODA de contextos

    if (!draw->length)
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
    switch (context)
    {
        case 'f': create_rank_by_context(draw, output, ranking, get_wall_statistics, 'w'); break;
        case 'w': create_rank_by_context(draw, output, ranking, get_moviments_statistics, 'm'); break;
        case 'm':
        {
            ascending_order(ranking);
            destroy_draw(draw);
        }
        default: return;
    }
}

void create_rank_by_context(draw *draw, output *output, char *ranking, char context, short int (*context_statistics)(void *, char))
{
    struct draw *aux = NULL;

    for (int index = 0; index < draw->length; index++)
    {
        aux = validate_draw(output, ranking, context_statistics);

        if (aux->has_draw) create_rank(aux, output, ranking, context);
        if (!aux->has_draw)
        {
            for (int index = 0; index < aux->length; index++)
            {
                ranking[index] = aux->draw_group[index]->moviments[0];
            }
        }

        destroy_draw(draw);
        destroy_draw(aux);
    }
}

draw *validate_draw(output *output, char *ranking, short int (*context_statistics)(void *, char))
{
    draw draw;
    draw.length = 0;
    draw.has_draw = 0;
    short int index = 0;
    short int nearby = 0;
    short int actual = 0;
    short int counter = 1;

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
