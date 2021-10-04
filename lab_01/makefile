CFLAGS:=-std=c99 -Wvla -Werror -Wall -pedantic

app.exe : main.o long_real.o
	gcc $^ -o app.exe

main.o : main.c long_real.h
	gcc $(CFLAGS) -c main.c -o main.o

long_real.o : long_real.c long_real.h
	gcc $(CFLAGS) -c long_real.c -o long_real.o

clean :
	rm *.o *.exe
