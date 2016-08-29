//
//  ant.h
//  langtons_ant
//
//  Created by Srinivas Dhanwada on 8/26/16.
//  Copyright © 2016 dhanwada. All rights reserved.
//

#ifndef ant_h
#define ant_h

typedef struct {
    int x;
    int y;
} Point;

typedef struct {
    Point current_position;
    int direction;
} Ant;

Ant* init_ant(int x_size, int y_size);
void rotate_ant(Ant* ant, int num_times, int dir);
void move_ant_forward(Ant* ant, int x_size, int y_size);
char validate_ant_pos(Ant* ant, int x_size, int y_size);

#endif /* ant_h */
