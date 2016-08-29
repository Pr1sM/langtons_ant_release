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
#include <getopt.h>
#include "parser.h"

// Defined from parser.h
int BORDER_MODE = 0;

const char* help_text = "Usage: langtons_ant [options]\n\n"
                        "-c, --cylinder    Run the ant in cylinder mode -- ant will wrap across the\n"
                        "                  x-axis.\n"
                        "-h, --help        Print this help message.\n"
                        "-r, --reflect     Run the ant in reflect mode -- ant will change direction\n"
                        "                  when it hits a border.  This will override both cylinder\n"
                        "                  and torus modes!\n"
                        "-t, --torus       Run the ant in torus mode -- ant will wrap across both\n"
                        "                  the x and y axes.  This will override cylinder mode!\n";

void parse_args(int argc, char** argv) {
    
    if(argc == 1) {
        return;
    }
    
    int flag;
    int help_flag = 0;
    
    opterr = 0;
    
    while(1) {
        static struct option long_options[] = {
            {"cylinder", no_argument, 0, 'c'},
            {"help", no_argument, 0, 'h'},
            {"reflect", no_argument, 0, 'r'},
            {"torus", no_argument, 0, 't'},
            {0, 0, 0, 0}
        };
        
        int option_index = 0;
        flag = getopt_long(argc, argv, "chrt", long_options, &option_index);
        
        if(flag == -1) {
            break;
        }
        
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
                
            case '?':
                opterr = 1;
                break;
                
            default:
                printf("%s", help_text);
                abort();
        }
    }
    
    if(help_flag || opterr) {
        printf("%s", help_text);
        exit(0);
    }
}
