CC := gcc
CFLAGS := -std=c99 -Wall -Werror -Wvla -I inc/
INC_DIR := inc/
OBJ_DIR := out/
SRC_DIR := src/
OBJS := $(OBJ_DIR)main.o $(OBJ_DIR)bs_tree.o $(OBJ_DIR)avl_tree.o \
$(OBJ_DIR)hash_table.o $(OBJ_DIR)file_array.o $(OBJ_DIR)info.o

app.exe : $(OBJS)
	$(CC) $^ -o app.exe

$(OBJ_DIR)main.o : $(SRC_DIR)main.c $(INC_DIR)avl_tree.h $(INC_DIR)bs_tree.h $(INC_DIR)file_array.h $(INC_DIR)hash_table.h $(INC_DIR)info.h
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $< -c -o $(OBJ_DIR)main.o

$(OBJ_DIR)avl_tree.o : $(SRC_DIR)avl_tree.c $(INC_DIR)avl_tree.h
	$(CC) $(CFLAGS) $< -c -o $(OBJ_DIR)avl_tree.o

$(OBJ_DIR)bs_tree.o : $(SRC_DIR)bs_tree.c $(INC_DIR)bs_tree.h
	$(CC) $(CFLAGS) $< -c -o $(OBJ_DIR)bs_tree.o

$(OBJ_DIR)hash_table.o : $(SRC_DIR)hash_table.c $(INC_DIR)hash_table.h
	mkdir -p out/
	$(CC) $(CFLAGS) $< -c -o $(OBJ_DIR)hash_table.o

$(OBJ_DIR)file_array.o : $(SRC_DIR)file_array.c $(INC_DIR)file_array.h
	$(CC) $(CFLAGS) $< -c -o $(OBJ_DIR)file_array.o

$(OBJ_DIR)info.o : $(SRC_DIR)info.c $(INC_DIR)info.h $(INC_DIR)bs_tree.h $(INC_DIR)avl_tree.h $(INC_DIR)hash_table.h $(INC_DIR)file_array.h
	$(CC) $(CFLAGS) $< -c -o $(OBJ_DIR)info.o

.PHONY : clean

clean :
	rm -rf out/ *.png *.exe *.gv
