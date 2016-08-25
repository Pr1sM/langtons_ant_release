#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>

const char *params = "PATTERN I\nOUTPUT langton.mpg\nBASE_FILE_FORMAT PPM\n"
"INPUT_CONVERT *\nGOP_SIZE 650\nSLICES_PER_FRAME 1\n"
"INPUT_DIR .\nINPUT\n"
".langton_data/*.pbm [0000000000-%d+%d]\n"
"END_INPUT\nPIXEL HALF\nRANGE 10\n"
"PSEARCH_ALG LOGARITHMIC\nBSEARCH_ALG CROSS2\nIQSCALE 8\n"
"PQSCALE 10\nBQSCALE 25\nREFERENCE_FRAME ORIGINAL\n";

#define NAME_TEMPLATE ".langton_data/%010u.pbm"
#define BOARD_LENGTH 128
static int _x_size, _y_size, _skip, _sequence_number;

int start_encode(int x_size, int y_size, int skip)
{
    if ((x_size * y_size) % 8) {
        fprintf(stderr, "Error: x_size * y_size must be divisible by 8.\n");
        return 1;
    }
    
    if (x_size * y_size > 65536) {
        fprintf(stderr, "Error: Let's not be ridiculous.\n");
        return 1;
    }
    
    if (skip < 1) {
        fprintf(stderr, "Error: skip must be positive.\n");
    }
    
    system("rm -f ppmtompeg_params");
    system("rm -rf .langton_data");
    
    if (mkdir(".langton_data", 0700)) {
        perror(".langton_data");
        return 1;
    }
    
    _x_size = x_size;
    _y_size = y_size;
    _skip = skip;
    _sequence_number = 0;
    
    return 0;
}

int next_frame(char *data)
{
    char name[80];
    FILE *file;
    unsigned char byte;
    unsigned i;
    
    if (_sequence_number % _skip) {
        _sequence_number++;
        
        return 0;
    }
    
    sprintf(name, NAME_TEMPLATE, _sequence_number++);
    file = fopen(name, "w");
    
    fprintf(file, "P4\n%d %d\n", _x_size, _y_size);
    
    for (i = 0, byte = 0; i < _x_size * _y_size; i++) {
        if (i && !(i % 8)) {
            fwrite(&byte, 1, 1, file);
            byte = 0;
        }
        if (data[i]) {
            byte |= (1 << (7 - (i % 8)));
        }
    }
    fwrite(&byte, 1, 1, file);
    
    fclose(file);
    
    return 0;
}

int finish_encode(void)
{
    char name[80];
    char encoder_params[400];
    FILE *f;
    
    strcpy(name, "ppmtompeg_params");
    sprintf(encoder_params, params, _sequence_number - 1, _skip);
    
    f = fopen(name, "w");
    fwrite(encoder_params, strlen(encoder_params), 1, f);
    fclose(f);
    
    system("ppmtompeg ppmtompeg_params");
    system("rm -f ppmtompeg_params");
    system("rm -rf .langton_data");
    
    return 0;
}

char buffer[BOARD_LENGTH][BOARD_LENGTH];

typedef struct {
    int x;
    int y;
} Point;

typedef struct {
    Point current_position;
    int direction;
} Ant;

Ant* init_ant() {
    Ant* newAnt = (Ant*) malloc(sizeof(Ant));
    newAnt->current_position.x = _x_size / 2;
    newAnt->current_position.y = _y_size / 2;
    newAnt->direction = 2;
    return newAnt;
}

void _rotate_ant(Ant* ant, int num_times, int dir) {
    int i;
    for(i = 0; i < num_times; i++) {
        ant->direction += dir;
        ant->direction = ant->direction < 0 ? 3 : ant->direction > 3 ? 0 : ant->direction;
    }
}

void rotate_ant_cw(Ant* ant, int num_times) {
    _rotate_ant(ant, num_times, 1);
}

void rotate_ant_ccw(Ant* ant, int num_times) {
    _rotate_ant(ant, num_times, -1);
}

void move_ant_forward(Ant* ant) {
    if(ant->direction % 2) {
        ant->current_position.x -= ant->direction - 2;
    } else {
        ant->current_position.y -= ant->direction - 1;
    }
}

char validate_ant_pos(Ant* ant) {
    return ant->current_position.x >= 0 && ant->current_position.x < _x_size && ant->current_position.y >= 0 && ant->current_position.y < _y_size;
}

int main(int argc, char *argv[])
{
    start_encode(BOARD_LENGTH, BOARD_LENGTH, 50);
    Ant* ant = init_ant();
    while(validate_ant_pos(ant)) {
        char pos_val = buffer[ant->current_position.y][ant->current_position.x];
        if(!pos_val) {
            rotate_ant_cw(ant, 1);
        } else {
            rotate_ant_ccw(ant, 1);
        }
        buffer[ant->current_position.y][ant->current_position.x] = !pos_val;
        move_ant_forward(ant);
        next_frame((char*) buffer);
    }
    finish_encode();
    
    return 0;
}