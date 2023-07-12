#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#include "headers/pacman.h"

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
    short int nearby = 0;
    short int actual = 0;
    draw.length = 0;

    for (short int index = 0; index < POSSIBLE_MOVIMENTS;)
    {
        push_element_to_group(&draw, draw.length, 1, ranking[index]);

        actual = (*context_statistics)(output, ranking[index]);
        nearby = (*context_statistics)(output, ranking[index + 1]);

        for (short int counter = 1; actual == nearby; counter++)
        {
            push_element_to_group(&draw, draw.length, 1, ranking[index + counter]);

            nearby = (*context_statistics)(output, ranking[index + counter]);
            if (actual != (*context_statistics)(output, ranking[index + counter + 1]))
            {
                index = counter + 1;

                if (index != POSSIBLE_MOVIMENTS)
                {
                    //TODO: realocar memoria para o tamanho das listas
                }
            }
        }
    }

    return &draw;
}

void push_element_to_group(draw *draw, short int index, short int amount, ...)
{
    va_list valist;
    va_start(valist, amount);

    short int total = draw->draw_group[index]->length + amount;
    short int counter = draw->draw_group[index]->length;

    if (!draw->draw_group)
    {
        draw->length++;
        draw->draw_group = (group **) malloc(sizeof(group *));
        draw->draw_group[0] = (group *) malloc(sizeof(group));
        draw->draw_group[0]->length = amount;
        draw->draw_group[0]->moviments = (char *) malloc(amount * sizeof(char));
        draw->draw_group[draw->draw_group[0]->length - 1]
            ->moviments[0] = va_arg(valist, char);
    }

    for (; counter < total; counter++)
    {
        draw->draw_group[index]->length += amount;
        draw->draw_group[index]->moviments = (char *) realloc(
            draw->draw_group[index]->moviments,
            draw->draw_group[index]->length * sizeof(char)
        );
        draw->draw_group[index]->moviments[counter] = va_arg(valist, char);
    }

    va_end(valist);
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