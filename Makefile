CC=g++
CFLAGS=-pedantic -Wall -Wextra -g

SRC=src
OBJ=obj
SRCS=$(wildcard $(SRC)/*.cpp)
OBJS=$(patsubst $(SRC)/%.cpp, $(OBJ)/%.o, $(SRCS))
BIN=bin/soft-body-sim

LDLIBS := -lsfml-graphics -lsfml-window -lsfml-system

all: $(BIN)

release: CFLAGS=-O2 -Wall -DNDEBUG
release: clean
release: $(BIN)

$(BIN): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@ $(LDLIBS)
	$(BIN).exe

$(OBJ)/%.o: $(SRC)/%.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm $(OBJ)/*.o


# tests -------------------
T_SRC=tests
T_OBJ=tests
T_SRCS=$(wildcard $(T_SRC)/*.cpp)
T_OBJS=$(patsubst $(T_SRC)/%.cpp, $(T_OBJ)/%.o, $(T_SRCS))
T_BIN=tests/tests

F_OBJS=$(filter-out obj/main.o, $(OBJS))

tests: $(T_BIN)

$(T_BIN): $(T_OBJS) $(F_OBJS)
	$(CC) $(T_OBJS) $(F_OBJS) -o $@ $(LDLIBS)
	$(T_BIN).exe

$(T_OBJ)/%.o: $(T_SRC)/%.cpp
	$(CC) -c $< -o $@ -lrt -lm

tests-clean:
	rm $(T_OBJ)/*.o