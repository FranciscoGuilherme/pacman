#include <stdio.h>
#include <stdlib.h>

#include "../headers/pacman.h"
#include "../headers/helpers.h"
#include "../headers/reports/ranking.h"
#include "../headers/structures/draw.h"
#include "../headers/structures/output.h"

void create_ranking_file(data *data)
{
    FILE *file;
    draw draw;
    ranking partial_ranking;
    char *ranking = calloc(POSSIBLE_MOVIMENTS + 1, sizeof(char));
    char letters[POSSIBLE_MOVIMENTS] = {'w', 'a', 's', 'd'};
    char *ranking_file = create_output_files_path(
        data->input.directory,
        FILE_NAME_RANKING
    );

    for (short int index = 0; index < POSSIBLE_MOVIMENTS; index++)
    {
        partial_ranking = get_biggest_food_rank(data, letters[index]);
        ranking[index] = partial_ranking.letter;
    }

    file = fopen(ranking_file, "w");
    draw = validate_draw(&data->output, ranking, get_food_statistics);
    create_rank(&draw, &data->output, ranking, 'f');

    for (int index = 0; index < POSSIBLE_MOVIMENTS; index++)
    {
        fprintf(file, "%c,%hu,%hu,%d\n",
            ranking[index],
            get_food_statistics(&data->output, ranking[index]),
            get_wall_statistics(&data->output, ranking[index]),
            get_moviments_statistics(&data->output, ranking[index])
        );
    }

    fclose(file);
    free(ranking_file);
}

void create_rank(draw *draw, output *output, char *ranking, char context)
{
    switch (context)
    {
        case 'f': create_rank_by_context(draw, output, ranking, 'w', get_wall_statistics); break;
        case 'w': create_rank_by_context(draw, output, ranking, 'm', get_moviments_statistics); break;
        case 'm':
        {
            ascending_order(ranking);
            destroy_draw(draw);
        }
        default: return;
    }
}

void create_rank_by_context(draw *draw, output *output, char *ranking, char context, short int (*context_statistics)(struct output_data *, char))
{
    struct draw aux;

    for (int index = 0; index < draw->length; index++)
    {
        aux = validate_draw(output, ranking, context_statistics);

        if (aux.has_draw) create_rank(&aux, output, ranking, context);
        if (!aux.has_draw)
        {
            for (int index = 0; index < aux.length; index++)
            {
                ranking[index] = aux.draw_group[index]->moviments[0];
            }
        }

        destroy_draw(draw);
    }
}

draw validate_draw(output *output, char *ranking, short int (*context_statistics)(struct output_data *, char))
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

    return draw;
}

ranking get_biggest_food_rank(data *data, char letter)
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

    return partial_ranking;
}

ranking get_lowest_wall_rank(data *data, char letter)
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

    return partial_ranking;
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
