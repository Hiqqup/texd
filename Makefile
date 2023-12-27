
CC=gcc
#CC=musl-gcc
CFLAGS= -Wall -pedantic -Wextra -std=gnu99
SRC=src
BIN=bin
SOURCE= $(SRC)/main.c $(SRC)/term.c $(SRC)/io.c
EDIT_FILE=tut/main.cpy 


texd: $(SOURCE) $(BIN)
	$(CC) $(SOURCE) $(CFLAGS) -o $(BIN)/texd

run: texd 
	./$(BIN)/texd $(EDIT_FILE)
	clear

debug: $(SOURCE) $(BIN)
	$(CC) $(SOURCE) $(CFLAGS) -g -o $(BIN)/debug-bin
	gdb -tui --args $(BIN)/debug-bin $(EDIT_FILE)

$(BIN):
	mkdir bin

clean:
	rm -fr $(BIN)/*
