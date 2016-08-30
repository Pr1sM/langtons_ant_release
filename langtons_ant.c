//
//  langtons_ant.c
//  langtons_ant
//

#include <stdio.h>
#include <stdlib.h>
#include "ant/ant.h"
#include "encode/encode.h"
#include "parser/parser.h"

int main(int argc, char *argv[])
{
    int start_encode_pass = 0;
    int i, j;
    
    parse_args(argc, argv);
    char buffer[ARG_LENGTH][ARG_WIDTH];
    for(i = 0; i < ARG_LENGTH; i++) {
        for(j = 0; j < ARG_WIDTH; j++) {
            buffer[i][j] = 0;
        }
    }
    start_encode_pass = start_encode(ARG_WIDTH, ARG_LENGTH, ARG_SKIP);
    if(start_encode_pass != 0) {
        exit_with_help();
    }
    Ant* ant = init_ant(_x_size, _y_size);
    while(validate_ant_pos(ant, _x_size, _y_size, _sequence_number)) {
        char pos_val = buffer[ant->current_position.y][ant->current_position.x];
        rotate_ant(ant, 1, pos_val == 1 ? -1 : 1);
        buffer[ant->current_position.y][ant->current_position.x] = !pos_val;
        move_ant_forward(ant, _x_size, _y_size);
        next_frame((char*) buffer);
    }
    finish_encode();
    free(ant);
    return 0;
}
