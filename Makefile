all: main

main: dir main.o
	g++ bin\main.o -o main.exe

dir:
	mkdir -p bin

main.o: src\main.cpp
	g++ -ggdb -c src\main.cpp -o bin\main.o

clean:
	rm -rf bin main.exe tree.gv tree.png