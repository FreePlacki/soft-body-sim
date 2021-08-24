CC = g++
CFLAGS = -pedantic -Wall -Wextra -g

bin\soft-body-sim: main.o particle.o vector2.o window.o engine.o shape.o fileManager.o body.o
	$(CC) $^ -o $@ $(CFLAGS) -lsfml-graphics -lsfml-window -lsfml-system
	bin\soft-body-sim.exe

main.o: src/main.cpp
	$(CC) -c $^ $(CFLAGS)

particle.o: src/shapes/particle.cpp
	$(CC) -c $^ $(CFLAGS)

vector2.o: src/math/vector2.cpp
	$(CC) -c $^ $(CFLAGS)

window.o: src/engine/window.cpp
	$(CC) -c $^ $(CFLAGS)

engine.o: src/engine/engine.cpp
	$(CC) -c $^ $(CFLAGS)

shape.o: src/shapes/shape.cpp
	$(CC) -c $^ $(CFLAGS)

fileManager.o: src/engine/fileManager.cpp
	$(CC) -c $^ $(CFLAGS)

body.o: src/shapes/body.cpp
	$(CC) -c $^ $(CFLAGS)

clean:
	rm *.o