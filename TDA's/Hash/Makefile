CC = gcc
CFLAGS = -g -std=c99 -Wall -Wconversion -Wno-sign-conversion -Werror -Wtype-limits
VALGRIND = valgrind --leak-check=full --track-origins=yes --show-reachable=yes
CMD = pruebas

build: hash.c hash.h testing.c testing.h hash_pruebas.c
	clear
	$(CC) $(CFLAGS) main.c hash.c testing.c hash_pruebas.c -o pruebas
	$(VALGRIND) ./$(CMD)	
run: build