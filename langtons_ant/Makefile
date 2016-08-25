# the compiler: using gcc for C
CC = gcc

# compiler flags:
# -g      ~> add debugging information to the binary
# -Wall   ~> display all warnings
# -Werror ~> treat warnings as errors
CFLAGS = -g -Wall -Werror

# the build target:
TARGET = srinivas_dhanwada.assignment-0

# define default target
default: $(TARGET)

# define target build instructions
$(TARGET): $(TARGET).c
	$(CC) $(CFLAGS) -o $(TARGET) $(TARGET).c

# define clean build instructions
clean: 
	$(RM) $(TARGET) *.o *~
