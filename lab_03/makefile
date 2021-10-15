CC := gcc
CFLAGS := -std=c99 -Wall -Werror -Wvla -Wpedantic

app.exe : out/ out/main.o
	$(CC) out/main.o -o app.exe

out/main.o : src/main.c
	$(CC) $(CFLAGS) -c $^ -o out/main.o

out/ :
	mkdir out
	