CC := gcc
CFLAGS := -std=c99 -Wall -Werror
OBJS := out/main.o out/graph.o

app.exe : $(OBJS)
	$(CC) $(OBJS) -o app.exe

out/main.o : src/main.c inc/graph.h
	mkdir -p out/
	$(CC) $(CFLAGS) -I inc/ $< -c -o out/main.o

out/graph.o : src/graph.c inc/graph.h
	$(CC) $(CFLAGS) -I inc/ $< -c -o out/graph.o
