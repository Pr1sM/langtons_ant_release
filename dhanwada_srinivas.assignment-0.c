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
    // allocate memory for the ant and set the
    // current_postition and direction to the
    // correct default values.
    Ant* newAnt = (Ant*) malloc(sizeof(Ant));
    newAnt->current_position.x = _x_size / 2;
    newAnt->current_position.y = _y_size / 2;
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

void move_ant_forward(Ant* ant) {
    // The cardinal directions N, E, S, W are represented with values 0, 1, 2, 3, respectively.
    // That means a value of 0 or 2 affects the y direction, and 1 or 3 affects the x direction.
    // Check which axis we need to change first.
    if(ant->direction % 2) {
        // direction is either E or W (1 or 3).
        // E changes the x position relatively by +1.
        // W changes the x position relatively by -1.
        // 2 - dir will correctly map 1 ~> 1 and 3 ~> -1.
        ant->current_position.x += 2 - ant->direction;
    } else {
        // direction is either N or S (0 or 2).
        // N changes the y position relatively by -1.
        // S changes the y position relatively by +1.
        // dir - 1 will correctly map 0 ~> -1 and 2 -> 1.
        ant->current_position.y += ant->direction - 1;
    }
}

char validate_ant_pos(Ant* ant) {
    return ant->current_position.x >= 0 && ant->current_position.x < _x_size && ant->current_position.y >= 0 && ant->current_position.y < _y_size;
}

int main(int argc, char *argv[])
{
    start_encode(BOARD_LENGTH, BOARD_LENGTH, 5);
    Ant* ant = init_ant();
    while(validate_ant_pos(ant)) {
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