# the compiler: using gcc for C
CC = gcc

# compiler flags:
# -g      ~> add debugging information to the binary
# -Wall   ~> display all warnings
# -Werror ~> treat warnings as errors
CFLAGS = -Wall -Werror

# debug flags:
# -g      ~> add debugging information to the binary
DFLAGS = -g

# the build target:
TARGET = dhanwada_srinivas.assignment-0

# define default target
default: $(TARGET)

# define target build instructions
$(TARGET): $(TARGET).c
	$(CC) $(CFLAGS) -o $(TARGET) $(TARGET).c

# define debug build instructions
debug: $(TARGET).c
	$(CC) $(CFLAGS) $(DFLAGS) -o $(TARGET) $(TARGET).c

# define clean build instructions
clean: 
	$(RM) -r $(TARGET) *.o *~ *.dSYM/
