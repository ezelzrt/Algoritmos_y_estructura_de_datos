#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "heap.h"
#include "hash.h"

typedef struct usuario usuario_t;

typedef struct afinidad_post afinidad_post_t;

int comparar_afinidad(const void* a, const void* b);

usuario_t* crear_usuario(char* nombre, int id);

void destruir_usuario(usuario_t* usuario);

void agregar_al_feed(hash_t* usuarios, size_t id_post, char* nombre_actual);

int obtener_id_siguiente_feed(usuario_t* usuario);