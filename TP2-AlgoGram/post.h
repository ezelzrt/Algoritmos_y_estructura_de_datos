#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "lista.h"

typedef struct post post_t;

/* Crea un post
 * Post: el post fue creado con un autor, id y un texto */
post_t* post_crear(char* texto, size_t id, char* autor);

/* Pre: el post fue creado
 * Post: el post fue destruido */
void post_destruir(post_t* post);

/* Suma un like al post
 * Pre: el post fue creado 
 * Post: el post tiene un like mas */
bool post_agregar_like(post_t* post, char* usuario);

/* Devuelve una lista con todas las personas que
 * le dieron like al post
 * Pre: el post fue creado
 * Post: Devolvio una lista de las personas que 
 * le dieron al post, en orden alfabetico */
lista_t* post_obtener_likes(post_t* post);

/* Devuelve el texto del post
 * Pre: el post fue creado
 * Post: se devolvio el texto del post */
const char* post_obtener_texto(post_t* post);

/* Devuelve el autor del post
 * Pre: el post fue creado
 * Post: se devolvio el autor del post */
const char* post_obtener_autor(post_t* post);

/* Devuelve el id del post
 * Pre: el post fue creado
 * Post: se devolvio el id del post */
size_t post_obtener_id(post_t* post);

/* Devuelve la cantidad de likes del post
 * Pre: el post fue creado
 * Post: se devolvio la cantidad de likes del post */
size_t post_cant_likes(post_t* post);