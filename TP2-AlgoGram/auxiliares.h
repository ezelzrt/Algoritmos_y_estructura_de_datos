#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "usuario.h"
#include "post.h"
#include "lista.h"

hash_t* entrada_archivo(FILE* archivo);

char* pedir_linea();

void imprimir_lista(lista_t* lista);

void imprimir_post(post_t* post);

void _post_destruir(void* post);