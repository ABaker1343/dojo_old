CC=g++
CFLAGS=-Wall -I. -lGL -lGLU -lglut -lglfw

#OBJ=fileHandler.o gameObject.o window.o renderable.o glad.o gameObject2DSprite.o camera2D.o gameObject2DAnimatedSprite.o gameObject2DCollisionBox.o camera3D.o gameObject3DTextured.o gameObjectSpotLightSource.o gameObjectPointLightSource.o

#HEADERS=fileHandler.hpp gameObject.hpp win.hppw.hpp renderable.hpp gameObject2DSprite camera2D.hpp gameObject2DAnimatedSprite.hpp gameObject2DCollisionBox.hpp camera3D.hpp gameObject3DTextured.hpp gameObjectSpotLightSource.hpp gameObjectPointLightSource.hpp

HEADERS=$(wildcard headers/*.hpp) $(wildcard headers/*.h) $(wildcard gameObjects/headers/*.hpp)

#SOURCE=fileHandler.cpp gameObject.cpp win.cppw.cpp renderable.cpp glad.c gameObject2DSprite camera2D.cpp gameObject2DAnimatedSprite.cpp gameObject2DCollisionBox.cpp camera3D.cpp gameObject3DTextured.cpp gameObjectSpotLightSource.cpp gameObjectPointLightSource.cpp

SOURCE=$(wildcard *.cpp) $(wildcard gameObjects/*.cpp)

OBJ=$(patsubst %.cpp, %.o, $(SOURCE)) glad.o

../libdojo.so: $(OBJ)
	$(CC) -shared -o ../libdojo.so $(OBJ) $(CFLAGS)

%.o: %.cpp headers/%.hpp
	$(CC) -fPIC -c -o $@ $< $(CFLAGS)

glad.o: glad.c
	$(CC) -fPIC -c -o $@ $< $(CFLAGS)

clean:
	rm gameObjects/*.o
	rm *.o

show:
	echo "$(OBJ)"
	echo "$(SOURCE)"
	echo "$(HEADERS)"
