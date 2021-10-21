all: project1b.out

project1b.out:main.cpp hash24.cpp
	g++ -std=c++11 $^ -o $@

clean:
	rm -f *.out