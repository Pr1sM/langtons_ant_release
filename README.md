# langtons_ant
First assignment for Com S 327 at [ISU](https://www.iastate.edu)

This program creates a Langton's ant Simulation and renders the frames into an
mpeg video.

## Run this program

This project includes a Makefile, so to build the project:
```bash
$ make
```
For more information on `make`, click [here](https://www.gnu.org/software/make/)

This will create an binary called `langtons_ant`. This can be 
run with the default settings using:
```bash
$ ./langtons_ant
```

To view the different modes available for the ant, show the
help menu:
```bash
$ ./langtons_ant -h
```

#### Run Modes

This project includes several different modes that affect the ant's collision 
with the borders.

- **Normal**   - The ant will stop when it reaches any border.
- **Cylinder** - The ant will wrap around on the x-axis borders, but will stop on the y-axis borders.
- **Torus**    - The ant will wrap around on both axes' borders. 
- **Reflect**  - The ant will reflect off of all borders when it reaches them

To change the run mode, pass in a flag at runtime.

| Run Mode | Flag                                            |
|:--------:|:----------------------------------------------- |
| Normal   | This is the default mode - _No flag necessary_. |
| Cylinder | use `-c` or `--cylinder`.                       |
| Torus    | use `-t` or `--torus`.                          |
| Reflect  | use `-r` or `--reflect`.                        |


There are several modes that determine the ant 

After the program completes, a file called `langton.mpg` should be 
available for you to view!

> This program does use [NetPBM](http://netpbm.sourceforge.net) to translate 
> the ppm frames to an mpeg video.  This must be installed for the mpeg video 
> to be created.
