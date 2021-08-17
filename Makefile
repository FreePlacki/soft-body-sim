output: main.o particle.o vector2.o window.o engine.o shape.o fileManager.o
	g++ main.o particle.o vector2.o window.o engine.o shape.o fileManager.o -o bin/soft-body-sim.exe -B bin -g -Wall -lsfml-graphics -lsfml-window -lsfml-system
	bin\soft-body-sim.exe

main.o: src/main.cpp
	g++ -c src/main.cpp

particle.o: src/shapes/particle.cpp src/shapes/particle.h
	g++ -c src/shapes/particle.cpp

vector2.o: src/math/vector2.cpp src/math/vector2.h
	g++ -c src/math/vector2.cpp

window.o: src/engine/window.cpp src/engine/window.h
	g++ -c src/engine/window.cpp

engine.o: src/engine/engine.cpp src/engine/engine.h
	g++ -c src/engine/engine.cpp

shape.o: src/shapes/shape.cpp src/shapes/shape.h
	g++ -c src/shapes/shape.cpp

fileManager.o: src/engine/fileManager.cpp src/engine/fileManager.h
	g++ -c src/engine/fileManager.cpp

clean:
	del *.o