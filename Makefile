CC = g++ -std=c++17
CFLAGS = -Wall -Werror -pedantic -g -MMD -MP
INCLUDE_PATH = -I/opt/homebrew/Cellar/sfml/2.6.1/include
LIBRARY_PATH = -L/opt/homebrew/Cellar/sfml/2.6.1/lib

# Executable name
EXECUTABLE = orbit_simulation

# Object files
OBJECTS = main.o body.o SpaceObject.o Spaceship.o Universe.o

# Dependency files
DEPENDS = $(OBJECTS:.o=.d)

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(CFLAGS) $(INCLUDE_PATH) $(LIBRARY_PATH) -o $(EXECUTABLE) $(OBJECTS) -lsfml-graphics -lsfml-window -lsfml-system

# Compilation rules
main.o: main.cpp
	$(CC) $(CFLAGS) $(INCLUDE_PATH) -c main.cpp

body.o: body.cpp SpaceObject.hpp NonCopyClass.hpp
	$(CC) $(CFLAGS) $(INCLUDE_PATH) -c body.cpp

SpaceObject.o: SpaceObject.cpp SpaceObject.hpp
	$(CC) $(CFLAGS) $(INCLUDE_PATH) -c SpaceObject.cpp

Spaceship.o: Spaceship.cpp Spaceship.hpp
	$(CC) $(CFLAGS) $(INCLUDE_PATH) -c Spaceship.cpp

Universe.o: Universe.cpp Universe.hpp
	$(CC) $(CFLAGS) $(INCLUDE_PATH) -c Universe.cpp

# Clean up generated files
clean:
	rm -rf $(EXECUTABLE) *.o *.d *.dSYM

-include $(DEPENDS)
