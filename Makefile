
CC=gcc
CFLAGS= -Wall -pedantic -Wextra -std=gnu99

texd: main.c
	$(CC) main.c $(CFLAGS)  

run: texd 
	./a.out main.cpy

debug:
	$(CC) main.c $(CFLAGS) -g -o debug-bin
	gdb -tui debug-bin
