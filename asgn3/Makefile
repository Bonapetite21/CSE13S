CC = clang
CFLAGS = -Wall -Wextra -Werror -Wpedantic -g

all: sorting

sorting: sorting.o support.o set.o bubble.o shell.o quick.o stack.o queue.o
	$(CC) -o sorting sorting.o support.o set.o bubble.o shell.o quick.o stack.o queue.o -lm

sorting.o: sorting.c
	$(CC) $(CFLAGS) -c sorting.c

support.o: support.c
	$(CC) $(CFLAGS) -c support.c

set.o: set.c
	$(CC) $(CFLAGS) -c set.c

bubble.o: bubble.c
	$(CC) $(CFLAGS) -c bubble.c

shell.o: shell.c
	$(CC) $(CFLAGS) -c shell.c

quick.o: quick.c
	$(CC) $(CFLAGS) -c quick.c

stack.o: stack.c
	$(CC) $(CFLAGS) -c stack.c

queue.o: queue.c
	$(CC) $(CFLAGS) -c queue.c

clean: 
	rm -rf *.o sorting 
