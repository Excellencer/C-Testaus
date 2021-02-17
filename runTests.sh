#!/bin/bash
make
gcc -o yksikko yksikko.c tiedostonkasittely.o tietorakenne.o -Wall -std=c99 -pedantic -lcunit -g

valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --log-file=valgrind-yksikko.txt ./yksikko



