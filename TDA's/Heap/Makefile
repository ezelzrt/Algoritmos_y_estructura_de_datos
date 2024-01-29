CC = gcc
CFLAGS = -g -std=c99 -Wall -Wconversion -Wno-sign-conversion -Werror -Wtype-limits
VALGRIND = valgrind --leak-check=full --track-origins=yes --show-reachable=yes
CMD = pruebas

build: heap.c heap.h testing.c testing.h heap_pruebas.c
	clear
	$(CC) $(CFLAGS) main.c heap.c testing.c heap_pruebas.c -o pruebas
	$(VALGRIND) ./$(CMD)	
run: build