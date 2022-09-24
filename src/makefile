CC=g++
CFLAGS=-Wall -I. $(shell pkg-config --cflags freetype2) -lGL -lGLU -lglut -lglfw $(shell pkg-config --libs freetype2)

HEADERS=$(wildcard headers/*.hpp) $(wildcard headers/*.h) $(wildcard gameObjects/headers/*.hpp) $(wildcard menuItems/headers/*.hpp)

SOURCE=$(wildcard *.cpp) $(wildcard gameObjects/*.cpp) $(wildcard menuItems/*.cpp)

OBJ=$(patsubst %.cpp, %.o, $(SOURCE)) glad.o

../libdojo.so: $(OBJ)
	$(CC) -shared -o ../libdojo.so $(OBJ) $(CFLAGS)

%.o: %.cpp headers/%.hpp
	$(CC) -fPIC -c -o $@ $< $(CFLAGS)

glad.o: glad.c
	$(CC) -fPIC -c -o $@ $< $(CFLAGS)

clean:
	rm gameObjects/*.o
	rm menuItems/*.o
	rm *.o

debug: $(OBJ)
	$(CC) -g -shared -o ../libdojo.so $(OBJ) $(CFLAGS)

show:
	echo "$(CFLAGS)"
	echo "$(OBJ)"
	echo "$(SOURCE)"
	echo "$(HEADERS)"
