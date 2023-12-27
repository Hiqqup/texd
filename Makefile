
CC=gcc
#CC=musl-gcc
CFLAGS= -Wall -pedantic -Wextra -std=gnu99
SRC=src
BIN=bin
SOURCE= $(SRC)/main.c $(SRC)/term.c $(SRC)/fileio.c


texd: $(SOURCE) $(BIN)
	$(CC) $(SOURCE) $(CFLAGS) -o $(BIN)/texd

run: texd 
	./$(BIN)/texd tut/main.cpy 

debug: $(SOURCE) $(BIN)
	$(CC) $(SOURCE) $(CFLAGS) -g -o $(BIN)/debug-bin
	gdb -tui --args $(BIN)/debug-bin tut/main.cpy

$(BIN):
	mkdir bin

clean:
	rm -fr $(BIN)/*
