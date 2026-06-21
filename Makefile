

CC = gcc



CFLAGS = -Wall -Wextra -O3 -march=native -std=c11


SRC_DIR = src


SOURCES = \
	$(SRC_DIR)/main.c \
	$(SRC_DIR)/rbtree.c \
	$(SRC_DIR)/benchmark.c \
	$(SRC_DIR)/csv.c


TARGET = rbtree_benchmark


all:
	$(CC) $(CFLAGS) $(SOURCES) -o $(TARGET) -lm


clean:
	rm -f $(TARGET)

rebuild: clean all