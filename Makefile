CC = g++ -std=c++0x
CFLAGS = -Wall -Werror -ansi -pedantic -g

all: Body

Body: main.o body.o SpaceObject.o Spaceship.o Universe.o star.o
	$(CC) $(FLAGS) -o body main.o body.o SpaceObject.o Spaceship.o Universe.o star.o -lsfml-graphics -lsfml-window -lsfml-system
main.o: main.cpp
	$(CC) $(Flags) -c main.cpp
body.o: body.cpp SpaceObject.cpp SpaceObject.hpp NonCopyClass.hpp
	$(CC) $(FLAGS) -c body.cpp
SpaceObject.o: SpaceObject.cpp SpaceObject.hpp
	$(CC) $(FLAGS) -c SpaceObject.cpp

Spaceship.o: Spaceship.cpp Spaceship.hpp	
	$(CC) $(FLAGS) -c Spaceship.cpp

Universe.o: Universe.cpp Universe.hpp
	$(CC) $(FLAGS) -c Universe.cpp

clean:
	rm -rf body *.o *.~