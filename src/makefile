CC=g++
CFLAGS=-Wall -I. -lGL -lGLU -lglut -lglfw
OBJ=fileHandler.o gameObject.o window.o renderable.o glad.o gameObject2DSprite.o camera2D.o gameObject2DAnimatedSprite.o
HEADERS=fileHandler.hpp gameObject.hpp win.hppw.hpp renderable.hpp gameObject2DSprite camera2D.hpp gameObject2DAnimatedSprite.hpp
SOURCE=fileHandler.cpp gameObject.cpp win.cppw.cpp renderable.cpp glad.c gameObject2DSprite camera2D.cpp gameObject2DAnimatedSprite.cpp

../libdojo.so: $(OBJ)
	$(CC) -shared -o ../libdojo.so $^ $(CFLAGS)

%.o: %.cpp headers/%.hpp
	$(CC) -fPIC -c -o $@ $< $(CFLAGS)

glad.o: glad.c
	$(CC) -fPIC -c -o $@ $< $(CFLAGS)

clean:
	rm *.o
