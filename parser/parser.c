//
//  parser.c
//  langtons_ant
//
//  Created by Srinivas Dhanwada on 8/28/16.
//  Copyright © 2016 dhanwada. All rights reserved.
//

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include "parser.h"

// Default board length
#define BOARD_LENGTH_DEFAULT 128

// Defined from parser.h
int BORDER_MODE = 0;
int ARG_LENGTH = BOARD_LENGTH_DEFAULT;
int ARG_WIDTH = BOARD_LENGTH_DEFAULT;

const char* help_text = "Usage: langtons_ant [options]\n\n"
                        "-c, --cylinder    Run the ant in cylinder mode -- ant will wrap across the\n"
                        "                  x-axis.\n"
                        "-h, --help        Print this help message.\n"
                        "-r, --reflect     Run the ant in reflect mode -- ant will change direction\n"
                        "                  when it hits a border.  This will override both cylinder\n"
                        "                  and torus modes!\n"
                        "-t, --torus       Run the ant in torus mode -- ant will wrap across both\n"
                        "                  the x and y axes.  This will override cylinder mode!\n";

int is_number(char* str) {
    int val = atoi(str);
    return (val > 0 || (val == 0 && strlen(str) == 1)) ? val : -1;
}

void parse_args(int argc, char** argv) {
    
    if(argc == 1) {
        return;
    }
    
    int flag;
    int help_flag = 0;
    int number = -1;
    
    opterr = 0;
    
    while(1) {
        // Setup options
        static struct option long_options[] = {
            {"cylinder", no_argument, 0, 'c'},
            {"length", required_argument, 0, 'l'},
            {"help", no_argument, 0, 'h'},
            {"reflect", no_argument, 0, 'r'},
            {"torus", no_argument, 0, 't'},
            {"width", required_argument, 0, 'w'},
            {0, 0, 0, 0}
        };
        
        int option_index = 0;
        flag = getopt_long(argc, argv, "chrtl:w:", long_options, &option_index);
        
        // flags are finished, break out of while loop
        if(flag == -1) {
            break;
        }
        
        // parse which flag was found
        switch (flag) {
            case 0:
                if(long_options[option_index].flag != 0) {
                    break;
                }
                printf("option: %s", long_options[option_index].name);
                if(optarg) {
                    printf(" with args %s", optarg);
                }
                printf("\n");
                break;
                
            case 'c':
                if(BORDER_MODE == 0) {
                    BORDER_MODE = 1;
                }
                break;
                
            case 'l':
                number = is_number(optarg);
                if(number <= 0 || number >= 256) {
                    fprintf(stderr, "Error: length must be an integer in range [1, 255].\n");
                    exit_with_help();
                }
                ARG_LENGTH = number;
                break;
                
            case 'h':
                help_flag = 1;
                break;
                
            case 'r':
                BORDER_MODE = 3;
                break;
                
            case 't':
                if(BORDER_MODE < 2) {
                    BORDER_MODE = 2;
                }
                break;
                
            case 'w':
                number = is_number(optarg);
                if(number <= 0 || number >= 256) {
                    fprintf(stderr, "Error: width must be an integer in range [1, 255].\n");
                    exit_with_help();
                }
                ARG_WIDTH = number;
                break;
                
            case '?':
                opterr = 1;
                break;
                
            default:
                exit_with_help();
        }
    }
    
    if(opterr) {
        fprintf(stderr, "Error: invalid flag parsed.\n");
        exit_with_help();
    }
    
    if(help_flag) {
        exit_with_help();
    }
}

void exit_with_help() {
    printf("%s", help_text);
    exit(0);
}
