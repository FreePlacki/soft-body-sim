CC=g++
CFLAGS=-pedantic -Wall -Wextra -g

SRC=src
OBJ=obj
SRCS=$(wildcard $(SRC)/*.cpp)
OBJS=$(patsubst $(SRC)/%.cpp, $(OBJ)/%.o, $(SRCS))
BIN=bin/soft-body-sim

all: $(BIN)

release: CFLAGS=-O2 -Wall -DNDEBUG
release: clean
release: $(BIN)

$(BIN): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@ -lsfml-graphics -lsfml-window -lsfml-system
	$(BIN).exe

$(OBJ)/%.o: $(SRC)/%.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm $(OBJ)/*.o