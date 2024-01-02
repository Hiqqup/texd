
CC=gcc
#CC=musl-gcc
CFLAGS= -Wall -pedantic -Wextra -std=gnu99
SRC=src
BIN=bin
SOURCE= $(SRC)/main.c $(SRC)/term.c $(SRC)/io.c $(SRC)/key.c $(SRC)/list.c $(SRC)/command.c
EDIT_FILE=log
#tut/main.cpy 


texd: $(SOURCE) $(BIN)
	$(CC) $(SOURCE) $(CFLAGS) -g -o $(BIN)/texd

run: texd 
	./$(BIN)/texd $(EDIT_FILE)
	clear


gdb-attatch:
	sudo gdb -tui -p $$(ps aux | grep texd | awk 'NR==1 {print $$2}')

debug: $(SOURCE) $(BIN)
	$(CC) $(SOURCE) $(CFLAGS) -g -o $(BIN)/debug-bin
	gdb -tui --args $(BIN)/debug-bin $(EDIT_FILE)

$(BIN):
	mkdir bin

clean:
	rm -fr $(BIN)/*
