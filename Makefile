output: main.o particle.o vector2.o
	g++ main.o particle.o vector2.o -o soft-body-sim -lsfml-graphics -lsfml-window -lsfml-system
	soft-body-sim.exe

main.o: cpp/main.cpp
	g++ -c -Isrc/include cpp/main.cpp

particle.o: cpp/particle.cpp header/particle.h
	g++ -c cpp/particle.cpp

vector2.o: cpp/vector2.cpp header/vector2.h
	g++ -c cpp/vector2.cpp

clean:
	del *.o