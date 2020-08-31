CC=g++
CFLAGS=-Wall -Wextra -g -std=c++11
EXEC=./tp1

${EXEC}: src/main.cpp util.o graph.o BFS.o 
	${CC} ${CFLAGS} src/main.cpp util.o graph.o BFS.o -o ${EXEC}

util.o: src/util.cc
	$(CC) $(CFLAGS) -c src/util.cc -o util.o

graph.o: src/graph.cc
	$(CC) $(CFLAGS) -c src/graph.cc -o graph.o

BFS.o: src/BFS.cc
	$(CC) $(CFLAGS) -c src/BFS.cc -o BFS.o

clean:
	rm -rf util.o
	rm -rf graph.o
	rm -rf BFS.o