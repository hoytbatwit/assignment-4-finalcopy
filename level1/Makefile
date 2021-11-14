# Location of unity directory
UNITY:=../unity

# Compilers use flags to control what options are used to compile the C source code. Commonly called CFLAGS
#  - The compiler is pretty smart and can warn you of various things. Use "-Wall -Wextra" to enable them
#  - We'll be using the 2011 version of C with GCC specific extensions (needed later in the course). Use "-std=gnu11"
CFLAGS:= -Wall -Wextra -Wvla -Wpedantic -std=gnu18 -ggdb -I$(UNITY) -fsanitize=address 

# Linkers also use flags to control the options used. Commonly called LDFLAGS
LDFLAGS:= -fsanitize=address 

# The list of programs this Makefile will build
PROGS:= test_files

# This line tells what to do when we type "make":
all: $(PROGS)

# This line tells what to do when we type "make clean": removes all .o files and the list of programs in PROGS
clean:
	$(RM) $(UNITY)/unity.o *.o $(PROGS)

# This is the line that will compile and build the main program for for Level 3
test_files: test_files.o files.o $(UNITY)/unity.o 
	$(CC) ${LDFLAGS} $^ -o $@

