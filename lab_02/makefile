CFLAGS:=-std=c99 -Wall -Werror -Wvla -pedantic

app.exe : main.o country.o sort.o
	gcc $^ -o app.exe

main.o : main.c
	gcc $(CFLAGS) main.c -c

country.o : country.c country.h
	gcc $(CFLAGS) country.c -c

sort.o : sort.c sort.h
	gcc $(CFLAGS) sort.c -c

clean :
	rm *.o *.exe
