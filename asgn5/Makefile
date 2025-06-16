CC = clang
CFLAGS = -Wall -Wextra -Werror -Wpedantic -g

all: encode decode error entropy

encode: encode.o hamming.o bm.o bv.o
	$(CC) -o encode encode.o hamming.o bm.o bv.o

decode: decode.o hamming.o bm.o bv.o
	$(CC) -o decode decode.o hamming.o bm.o bv.o

bm.0: bm.c
	$(CC) $(CFLAGS) -c bm.c

bv.o: bv.c
	$(CC) $(CFLAGS) -c bv.c

entropy: entropy.o
	$(CC) -o entropy entropy.o -lm

error: error.o
	$(CC) -o error error.o -lm

encode.o: encode.c
	$(CC) $(CFLAGS) -c encode.c

decode.o: decode.c
	$(CC) $(CFLAGS) -c decode.c

entropy.o: entropy.c
	$(CC) $(CFLAGS) -c entropy.c

error.o: error.c
	$(CC) $(CFLAGS) -c error.c 

hamming.0: hamming.clang
	$(CC) $(CFLAGS) -c hamming.c

clean:
	rm -rf encode decode entropy error *.o tsp 

format:
	clang-format -i -style=file *.c *.h

infer:
	make clean; infer-capture -- make; infer-analyze -- make
