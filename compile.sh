#!/bin/bash
LD_LIBRARY_PATH="./"
g++ -o game tester.cpp -lGL -ldojo -L. -I. -Wall -Wl,-rpath='$ORIGIN'
g++ -o game2 test2.cpp -lGL -ldojo -L. -I. -Wall -Wl,-rpath='$ORIGIN'
g++ -o game3 3dtester.cpp -lGL -ldojo -L. -I. -Wall -Wl,-rpath='$ORIGIN'
g++ -o game4 tester4.cpp -lGL -ldojo -L. -I. -Wall -Wl,-rpath='$ORIGIN'
g++ -o game5 tester5.cpp -lGL -ldojo -L. -I. -Wall -Wl,-rpath='$ORIGIN'
