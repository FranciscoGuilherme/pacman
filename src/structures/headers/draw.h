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
    group **draw_group;
} draw;

#endif
