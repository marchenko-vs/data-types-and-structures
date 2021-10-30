CC := gcc
CFLAGS := -std=c99 -Wall -Werror -Wvla -pedantic
OBJS := out/main.o out/array_stack.o out/list_stack.o out/info.o

app.exe : out/ $(OBJS)
	$(CC) $(OBJS) -o app.exe

out/ :
	mkdir out/

out/main.o : src/main.c inc/array_stack.h inc/list_stack.h inc/info.h
	$(CC) $(CFLAGS) -I inc/ $< -c -o out/main.o

out/array_stack.o : src/array_stack.c inc/array_stack.h
	$(CC) $(CFLAGS) -I inc/ $< -c -o out/array_stack.o

out/list_stack.o : src/list_stack.c inc/list_stack.h
	$(CC) $(CFLAGS) -I inc/ $< -c -o out/list_stack.o

out/info.o : src/info.c inc/info.h inc/array_stack.h inc/list_stack.h
	$(CC) $(CFLAGS) -I inc/ $< -c -o out/info.o

.PHONY : clean

clean :
	rm -rf out/ *.txt *.o *.gcov *.exe
