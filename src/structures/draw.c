#include <stdarg.h>

#include "headers/draw.h"

void add_new_group(draw *draw)
{
    draw->length++;
    draw->draw_group = (group **) realloc(
        draw->draw_group,
        draw->length * sizeof(group *)
    );
    draw->draw_group[draw->length - 1]->length = 0;
}

void push_element_to_group(draw *draw, short int amount, ...)
{
    va_list valist;
    va_start(valist, amount);

    short int total = draw->draw_group[draw->length - 1]->length + amount;
    short int counter = draw->draw_group[draw->length - 1]->length;

    if (!draw->draw_group)
    {
        draw->length++;
        draw->draw_group = (group **) malloc(sizeof(group *));
        draw->draw_group[0] = (group *) malloc(sizeof(group));
        draw->draw_group[0]->length = amount;
        draw->draw_group[0]->moviments = (char *) malloc(amount * sizeof(char));
        draw->draw_group[0]->moviments[0] = va_arg(valist, char);

        return;
    }

    for (; counter < total; counter++)
    {
        draw->draw_group[draw->length - 1]->length += amount;
        draw->draw_group[draw->length - 1]->moviments = (char *) realloc(
            draw->draw_group[draw->length - 1]->moviments,
            draw->draw_group[draw->length - 1]->length * sizeof(char)
        );
        draw->draw_group[draw->length - 1]->moviments[counter] = va_arg(valist, char);
    }

    va_end(valist);
}
