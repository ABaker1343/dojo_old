CC=g++
CFLAGS=-g -lGL -ldojo -L. -I. $(shell pkg-config --cflags freetype2) -Wall -Wl,-rpath='$$ORIGIN' $(shell pkg-config --libs freetype2)

SOURCE=$(wildcard *.cpp)
OBJECT=$(patsubst .cpp, .o, $(SOURCE))

out : $(SOURCE)
	$(CC) -o game tester.cpp $(CFLAGS)
	$(CC) -o game2 test2.cpp $(CFLAGS)
	$(CC) -o game3 3dtester.cpp $(CFLAGS)
	$(CC) -o game4 tester4.cpp $(CFLAGS)
	$(CC) -o game5 tester5.cpp $(CFLAGS)
	$(CC) -o game6 tester6.cpp $(CFLAGS)

game7:
	$(CC) -o game7 tester7.cpp $(CFLAGS)

clean:
	rm game
	rm game2
	rm game3
	rm game4
	rm game5
	rm game6
	rm game7
