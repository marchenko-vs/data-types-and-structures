CC := gcc
CFLAGS := -std=c99 -Wall -Werror -Wvla -Wpedantic -I inc/

app.exe : out/ out/main.o out/matrix.o out/sparse_matrix.o out/info.o
	$(CC) out/main.o out/matrix.o out/sparse_matrix.o out/info.o -o app.exe

out/main.o : src/main.c
	$(CC) $(CFLAGS) -c $^ -o out/main.o

out/matrix.o : src/matrix.c inc/matrix.h
	$(CC) $(CFLAGS) -c src/matrix.c -o out/matrix.o

out/sparse_matrix.o : src/sparse_matrix.c inc/sparse_matrix.h inc/matrix.h
	$(CC) $(CFLAGS) -c src/sparse_matrix.c -o out/sparse_matrix.o

out/info.o : src/info.c inc/info.h
	$(CC) $(CFLAGS) -c src/info.c -o out/info.o

out/ :
	mkdir out

clean :
	rm -rf out/ *.exe
	