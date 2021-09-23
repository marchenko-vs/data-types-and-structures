#!/bin/bash

gcc -std=c99 -Wall -Werror -Wvla -pedantic -c main.c
gcc -std=c99 -Wall -Werror -Wvla -pedantic -c long_real.c

gcc main.o long_real.o -o app.exe

rm *.o
