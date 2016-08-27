//
//  langtons_ant.c
//  langtons_ant
//

#include <stdio.h>
#include <stdlib.h>
#include "ant/ant.h"
#include "encode/encode.h"

#define BOARD_LENGTH 128

char buffer[BOARD_LENGTH][BOARD_LENGTH];

int main(int argc, char *argv[])
{
    start_encode(BOARD_LENGTH, BOARD_LENGTH, 50);
    Ant* ant = init_ant(_x_size, _y_size);
    while(validate_ant_pos(ant, _x_size, _y_size)) {
        char pos_val = buffer[ant->current_position.y][ant->current_position.x];
        rotate_ant(ant, 1, pos_val == 1 ? -1 : 1);
        buffer[ant->current_position.y][ant->current_position.x] = !pos_val;
        move_ant_forward(ant);
        next_frame((char*) buffer);
    }
    finish_encode();
    free(ant);
    return 0;
}
