output: main.o particle.o vector2.o window.o engine.o
	g++ main.o particle.o vector2.o window.o engine.o -o soft-body-sim -lsfml-graphics -lsfml-window -lsfml-system
	soft-body-sim.exe

main.o: cpp/main.cpp
	g++ -c -Isrc/include cpp/main.cpp

particle.o: cpp/particle.cpp header/particle.h
	g++ -c cpp/particle.cpp

vector2.o: cpp/vector2.cpp header/vector2.h
	g++ -c cpp/vector2.cpp

window.o: cpp/window.cpp header/window.h
	g++ -c cpp/window.cpp

engine.o: cpp/engine.cpp header/engine.h
	g++ -c cpp/engine.cpp

clean:
	del *.o