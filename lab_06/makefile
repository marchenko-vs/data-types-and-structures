CC := gcc
CFLAGS := -std=c99 -Wall -Werror -Wvla
OBJS := main.o bs_tree.o avl_tree.o hash_table.o universal.o array.o

app.exe : $(OBJS)
	$(CC) $(OBJS) -o app.exe

main.o : main.c avl_tree.h bs_tree.h hash_table.h
	$(CC) $(CFLAGS) main.c -c -o main.o

avl_tree.o : avl_tree.c avl_tree.h
	$(CC) $(CFLAGS) avl_tree.c -c -o avl_tree.o

bs_tree.o : bs_tree.c bs_tree.h
	$(CC) $(CFLAGS) bs_tree.c -c -o bs_tree.o

hash_table.o : hash_table.c hash_table.h
	$(CC) $(CFLAGS) hash_table.c -c -o hash_table.o

universal.o : universal.c universal.h
	$(CC) $(CFLAGS) universal.c -c -o universal.o

array.o : array.c array.h
	$(CC) $(CFLAGS) array.c -c -o array.o

.PHONY : clean

clean :
	rm *.o *.png *.exe *.gv
