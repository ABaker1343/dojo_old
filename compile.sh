#!/bin/bash
LD_LIBRARY_PATH="./"
g++ -o game tester.cpp -lGL -ldojo -L. -I. -Wall -Wl,-rpath='$ORIGIN'
