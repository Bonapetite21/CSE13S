CC = clang
CFLAGS = -Wall -Wextra -Werror -Wpedantic -g

all: tsp

tsp: graph.o stack.o path.o tsp.o
	$(CC) -o tsp graph.o stack.o path.o tsp.o -lm

tsp.o: tsp.c
	$(CC) $(CFLAGS) -c tsp.c

graph.o: graph.c
	$(CC) $(CFLAGS) -c graph.c

stack.o: stack.c
	$(CC) $(CFLAGS) -c stack.c

path.o: path.c
	$(CC) $(CFLAGS) -c path.c 

clean: 
	rm -rf *.o tsp 
