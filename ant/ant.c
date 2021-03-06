//
//  ant.c
//  langtons_ant
//
//  Created by Srinivas Dhanwada on 8/26/16.
//  Copyright © 2016 dhanwada. All rights reserved.
//

#include <stdlib.h>
#include "ant.h"
#include "../parser/parser.h"

#define MAX_STEPS 30000

Ant* init_ant(int x_size, int y_size) {
    // allocate memory for the ant and set the
    // current_postition and direction to the
    // correct default values.
    Ant* newAnt = (Ant*) malloc(sizeof(Ant));
    newAnt->current_position.x = x_size / 2;
    newAnt->current_position.y = y_size / 2;
    newAnt->direction = 0;
    return newAnt;
}

void rotate_ant(Ant* ant, int num_times, int dir) {
    // NOTE: we are asserting that dir will be either 1 or -1 based on if the intended
    //       direction of rotation is clockwise or counterclockwise.
    int i;
    for(i = 0; i < num_times; i++) {
        // increment the direction, then correct if there is overflow.
        ant->direction += dir;
        ant->direction = ant->direction < 0 ? 3 : ant->direction > 3 ? 0 : ant->direction;
    }
}

void move_ant_forward(Ant* ant, int x_size, int y_size) {
    // The cardinal directions N, E, S, W are represented with values 0, 1, 2, 3, respectively.
    // That means a value of 0 or 2 affects the y direction, and 1 or 3 affects the x direction.
    // Check which axis we need to change first.
    if(ant->direction % 2) {
        // direction is either E or W (1 or 3).
        // E changes the x position relatively by +1.
        // W changes the x position relatively by -1.
        // 2 - dir will correctly map 1 ~> 1 and 3 ~> -1.
        ant->current_position.x += 2 - ant->direction;
        
        // Check if we are in cylinder/torus mode and apply a wrap
        // if the ant is out of bounds on the x axis.
        if(BORDER_MODE > 0 && BORDER_MODE <= 2) {
            ant->current_position.x += ant->current_position.x <  0      ?  x_size :
                                       ant->current_position.x >= x_size ? -x_size : 0;
        }
        
        // Check if we are in reflect mode and apply a redirection
        // if the ant is out of bounds on the x-axis.
        if(BORDER_MODE == 3) {
            if(ant->current_position.x < 0) {
                ant->current_position.x = 0;
                ant->direction = 1;
            } else if(ant->current_position.x >= x_size) {
                ant->current_position.x = x_size-1;
                ant->direction = 3;
            }
        }
    } else {
        // direction is either N or S (0 or 2).
        // N changes the y position relatively by -1.
        // S changes the y position relatively by +1.
        // dir - 1 will correctly map 0 ~> -1 and 2 ~> 1.
        ant->current_position.y += ant->direction - 1;
        
        // Check if we are in torus mode and apply a wrap
        // if the ant is out of bounds on the y-axis.
        if(BORDER_MODE == 2) {
            ant->current_position.y += ant->current_position.y <  0      ?  y_size :
                                       ant->current_position.y >= y_size ? -y_size : 0;
        }
        
        // Check if we are in reflect mode and apply a redirection
        // if the ant is out of bounds on the y-axis.
        if(BORDER_MODE == 3) {
            if(ant->current_position.y < 0) {
                ant->current_position.y = 0;
                ant->direction = 2;
            } else if(ant->current_position.y >= y_size) {
                ant->current_position.y = y_size-1;
                ant->direction = 0;
            }
        }
    }
}

char validate_ant_pos(Ant* ant, int x_size, int y_size, int sequence_number) {
    // Check if x coordinate is in bounds.
    int x_pass = ant->current_position.x >= 0 && ant->current_position.x < x_size;
    
    // Check if y coordinate is in bounds.
    int y_pass = ant->current_position.y >= 0 && ant->current_position.y < y_size;
    
    // Check if sequence has gone on too long.
    int max_steps = sequence_number <= MAX_STEPS;
    
    // Check for the proper conditions based on the border mode.
    return max_steps &&
          (BORDER_MODE == 0 ? x_pass : 1) &&
          (BORDER_MODE <= 1 ? y_pass : 1);
}
