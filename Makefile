CC = gcc
CFLAGS = -Wall -Iinclude
LDFLAGS = -L/usr/local/lib -lcunit -lm

SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin

all: $(BIN_DIR)/main $(BIN_DIR)/test

main: $(BIN_DIR)/main

test: $(BIN_DIR)/test
	$(BIN_DIR)/test

$(BIN_DIR)/main: $(OBJ_DIR)/main.o $(OBJ_DIR)/clock.o
	$(CC) -o $(BIN_DIR)/main $(OBJ_DIR)/main.o $(OBJ_DIR)/clock.o

$(BIN_DIR)/test: $(OBJ_DIR)/clock.o $(OBJ_DIR)/test.o
	$(CC) -o $(BIN_DIR)/test $(OBJ_DIR)/clock.o $(OBJ_DIR)/test.o $(LDFLAGS)

$(OBJ_DIR)/main.o: $(SRC_DIR)/main.c
	$(CC) $(CFLAGS) -c $(SRC_DIR)/main.c -o $(OBJ_DIR)/main.o

$(OBJ_DIR)/clock.o: $(SRC_DIR)/clock.c
	$(CC) $(CFLAGS) -c $(SRC_DIR)/clock.c -o $(OBJ_DIR)/clock.o

$(OBJ_DIR)/test.o: $(SRC_DIR)/test.c
	$(CC) $(CFLAGS) -c $(SRC_DIR)/test.c -o $(OBJ_DIR)/test.o

clean:
	rm -f $(OBJ_DIR)/*.o $(BIN_DIR)/main $(BIN_DIR)/test