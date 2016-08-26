# the compiler: using gcc for C
CC = gcc

# compiler flags:
# -Wall   ~> display all warnings
# -Werror ~> treat warnings as errors
CFLAGS = -Wall -Werror

# debug flags:
# -ggdb   ~> add gdb debugging information to the binary
DFLAGS = -ggdb

# the build target:
TARGET = dhanwada_srinivas.assignment-0

# define default target
all: clean debug

# define target build instructions
$(TARGET): $(TARGET).c
	$(CC) $(CFLAGS) -o $(TARGET) $(TARGET).c

# define debug build instructions
debug: $(TARGET).c
	$(CC) $(CFLAGS) $(DFLAGS) -o $(TARGET) $(TARGET).c

# define ant build instructions
ant: ant/ant.h ant/ant.c
	$(CC) $(CFLAGS) $(DFLAGS) -c -o ant.o ant/ant.c -I.

# define clean build instructions
clean: 
	$(RM) -r $(TARGET) *.o *~ *.dSYM/
