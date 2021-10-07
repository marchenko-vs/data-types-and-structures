CFLAGS:=-std=c99 -Wall -Werror -Wvla -pedantic

app.exe : main.o country.o
	gcc $^ -o app.exe

main.o : main.c
	gcc $(CFLAGS) main.c -c

country.o : country.c country.h
	gcc $(CFLAGS) country.c -c
