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
TARGET = langtons_ant

# define default target
all: $(TARGET)

# define target build instructions
$(TARGET): $(TARGET).o libLangton.a
	$(CC) $(CFLAGS) $(DFLAGS) $^ -o $@

# define target.o build instructions
$(TARGET).o: $(TARGET).c
	$(CC) $(CFLAGS) $(DFLAGS) -c -o $@ $<

# define lib build instructions
libLangton.a: ant.o encode.o parser.o
	ar rcs $@ $^

# define ant build instructions
ant.o: ant/ant.c ant/ant.h
	$(CC) $(CFLAGS) $(DFLAGS) -c -o $@ $<

# define encode build instructions
encode.o: encode/encode.c encode/encode.h
	$(CC) $(CFLAGS) $(DFLAGS) -c -o $@ $<

# define parser build instructions
parser.o: parser/parser.c parser/parser.h
	$(CC) $(CFLAGS) $(DFLAGS) -c -o $@ $<

# define clean build instructions
clean: 
	$(RM) -r $(TARGET) *.o *.a *~ *.dSYM/
