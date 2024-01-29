CC = gcc
CFLAGS = -g -std=c99 -Wall -Wconversion -Wno-sign-conversion -Werror -Wtype-limits
VALGRIND = valgrind --leak-check=full --track-origins=yes --show-reachable=yes
CMD = pruebas

build: abb.c abb.h testing.c testing.h abb_pruebas.c pila.c pila.h
	clear
	$(CC) $(CFLAGS) abb.c testing.c abb_pruebas.c pila.c -o pruebas
	$(VALGRIND) ./$(CMD)	
run: build