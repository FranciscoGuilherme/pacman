#ifndef _DRAW_H
#define _DRAW_H

typedef struct group
{
    int length;
    char *moviments;
} group;

typedef struct draw
{
    int length;
    short int has_draw;
    group **draw_group;
} draw;

void add_new_group(draw *draw);
void push_element_to_group(draw *draw, short int amount, ...);
void destroy_draw(draw *draw);

#endif
