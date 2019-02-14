UNAME_S := $(shell uname -s)
CCFLAGS += -l SDL2 -l SDL2_image -l SDL2_ttf

all: test rsdl.o

test: Kingdom_Rush.o rsdl.o
	g++ rsdl.o Kingdom_Rush.o $(CCFLAGS) -o test.out

Kingdom_Rush.o: Kingdom_Rush.cpp rsdl.o
	g++ -c Kingdom_Rush.cpp -o Kingdom_Rush.o

rsdl.o: rsdl.hpp rsdl.cpp
	g++ -c rsdl.cpp -o rsdl.o

clean:
	rm -r *.o
