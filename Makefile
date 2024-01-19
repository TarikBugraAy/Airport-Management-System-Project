# Define the compiler to use
CC=gcc

# Compiler flags, -I. tells the compiler to look in the current directory for headers
CFLAGS=-I.

# Dependencies, lists all the header files the project relies on
DEPS = employee.h flight.h passenger.h common.h

# Object files that the project will compile
OBJ = main.o employee.o flight.o passenger.o common.o

# Rule for generating object files.
# Takes each C file, compiles it into an object file.
# $@ is the target file, $< is the first dependency, and $(CFLAGS) are the flags for the compiler.
%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

# The final build target.
# Compiles the object files into the executable airport_mgmt.
# $@ is the target file, $^ is all dependencies, and $(CFLAGS) are the flags for the compiler.
airport_mgmt: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

# Clean rule.
# Deletes all object files and the executable to clean the directory.
# Useful for ensuring a clean build.
clean:
	rm -f *.o airport_mgmt
