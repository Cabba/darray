CC=gcc
CFLAGS=-std=c89 -ansi -Wall -pedantic

default: test

test: darray.c test.c 
	$(CC) $(CFLAGS) test.c darray.c -o test

clean:
	rm -f *.o test
