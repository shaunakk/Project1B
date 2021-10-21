# the compiler: gcc for C program, define as g++ for C++
	CXX = g++
# compiler flags:
#  -g    adds debugging information to the executable file
#  -Wall turns on most, but not all, compiler warnings
CXXFLAGS  = -g -Wall
BINARIES=project1b

all: ${BINARIES}
project1b: main.o hash24.o 
	${CXX} $^ -o $@
clean:
	/bin/rm -f ${BINARIES} *.o