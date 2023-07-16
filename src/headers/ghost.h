#ifndef _GHOST_H
#define _GHOST_H

#include "pacman.h"

void move_ghosts(data *data, char moviment);
void ghost_up_actions(data *data, ghost *ghost, char moviment);
void ghost_down_actions(data *data, ghost *ghost, char moviment);
void ghost_left_actions(data *data, ghost *ghost, char moviment);
void ghost_right_actions(data *data, ghost *ghost, char moviment);

#endif
