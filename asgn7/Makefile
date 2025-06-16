CC = clang
CFLAGS = -Wall -Werror -Wextra -Wpedantic

all: banhammer

banhammer: banhammer.o node.o ll.o ht.o speck.o bv.o bf.o parser.o
	$(CC) -o banhammer banhammer.o node.o ll.o ht.o speck.o bv.o bf.o parser.o

banhammer.o: banhammer.c
	$(CC) $(CFLAGS) -c banhammer.c

node.o: node.c
	$(CC) $(CFLAGS) -c node.c

ll.o: ll.c
	$(CC) $(CFLAGS) -c ll.c

ht.o: ht.c
	$(CC) $(CFLAGS) -c ht.c

speck.o: speck.c
	$(CC) $(CFLAGS) -c speck.c

bv.o: bv.c
	$(CC) $(CFLAGS) -c bv.c

bf.o: bf.c
	$(CC) $(CFLAGS) -c bf.c

parser.o: parser.c
	$(CC) $(CFLAGS) -c parser.c

clean:
	rm -rf banhammer *.o infer-out

format:
	clang-format -i -style=file *.c *.h

infer:
	make clean; infer-capture -- make; infer-analyze -- make
