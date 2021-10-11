CC := gcc
CFLAGS := -std=c99 -Wvla -Wall -Werror -Wpedantic
OBJS := out/main.o out/country.o out/sort.o out/country_array.o out/info.o

app.exe : out/ out/main.o out/country.o out/sort.o out/country_array.o out/info.o
	$(CC) $(OBJS) -o app.exe

out/main.o : main.c country.h country_array.h sort.h info.h
	$(CC) $(CFLAGS) $< -c -o out/main.o

out/country.o : country.c country.h
	$(CC) $(CFLAGS) $< -c -o out/country.o

out/country_array.o : country_array.c country_array.h
	$(CC) $(CFLAGS) $< -c -o out/country_array.o

out/sort.o : sort.c sort.h
	$(CC) $(CFLAGS) $< -c -o out/sort.o

out/info.o : info.c info.h
	$(CC) $(CFLAGS) $< -c -o out/info.o

out/ :
	mkdir out/

clean :
	rm -rf *.o *.exe out/
