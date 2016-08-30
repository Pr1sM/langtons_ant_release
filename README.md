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

> You can pass in multiple run modes, however only one will be selected.
> Torus will override Cylinder, and Reflect will override both Cylinder and Torus.

#### Variable Canvas Size

The length or width of the canvas used can be changed based on flags passed in:

| Dimension | Flag                                            |
|:---------:|:----------------------------------------------- |
| Length    | use `-l<int>` or `--length <int>`.              |
| Width     | use `-w<int>` or `--width <int>`.               |

> Both the length and width have a default value of 128 if no flag is passed in.
> The range of these argument is [1,255]. Additionally, for encoding to work 
> properly, the area of the canvas (length * width) must be divisible by 8.

```bash
$ ./langtons_ant -w64 --length 120
```

#### Variable Frame Skip Rate

The number of frames to skip can be varied using a flag.  This will speed up or slow down
the final .mpg video based on if the number is high or low.  To vary the skip rate, pass in 
the following flag:

```
$ ./langtons_ant -s45
$ ./langtons_ant --skip 42
```

After the program completes, a file called `langton.mpg` should be 
available for you to view!

> This program does use [NetPBM](http://netpbm.sourceforge.net) to translate 
> the ppm frames to an mpeg video.  This must be installed for the mpeg video 
> to be created.
