//
//  parser.h
//  langtons_ant
//
//  Created by Srinivas Dhanwada on 8/28/16.
//  Copyright © 2016 dhanwada. All rights reserved.
//

#ifndef parser_h
#define parser_h

#include <stdio.h>

// Tells the program how the ant should interact around the borders.
// Modes:
//     0 = normal    -> stop when ant hits any border.
//     1 = cylinder  -> stop when ant hits y-axis borders, wrap on x-axis.
//     2 = torus     -> wrap on both x and y axes.  Hard limit is ~30000 steps.
//     3 = reflect   -> reflect direction when ant meets a border.
extern int BORDER_MODE;

// The Length and Width of the board size.  The default is 128 for both.
extern int ARG_LENGTH;
extern int ARG_WIDTH;

// The skip length of the frames.  The default is 50 frames.
extern int ARG_SKIP;

void parse_args(int argc, char** argv);
void exit_with_help();

#endif /* parser_h */
