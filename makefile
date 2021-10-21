all: main

main:main.o hash24.o 
	g++ -std=c++11 $^ -o $@

clean:
	rm -f *.out