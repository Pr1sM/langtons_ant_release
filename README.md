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
run using:
```bash
$ ./langtons_ant
```

After the program completes, a file called `langton.mpg` should be 
available for you to view!

> This program does use [NetPBM](http://netpbm.sourceforge.net) to translate 
> the ppm frames to an mpeg video.  This must be installed for the mpeg video 
> to be created.
