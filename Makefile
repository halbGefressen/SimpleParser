CFLAGS=-O2 -g
.PHONY: all clean

all: main

main: linkedlist.h linkedlist.c parser.h parser.c main.c

clean:
	rm -f main
