#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "abb.h"
#include "lista.h"
#include "post.h"


struct post{
    char* texto;
    size_t id;
    char* autor;
    size_t cant_likes;
    abb_t* personas_likes;
};

post_t* post_crear(char* texto, size_t id, char* autor){
    post_t* post = malloc(sizeof(post_t));
    if(!post) return NULL;
    
    post->personas_likes = abb_crear(strcmp, NULL);
    if(!post->personas_likes) free(post);

    post->texto = strdup(texto);
    post->id = id;
    post->autor = strdup(autor);
    post->cant_likes = 0;
    return post;
}

void post_destruir(post_t* post){
    free(post->texto);
    free(post->autor);
    abb_destruir(post->personas_likes);
    free(post);
}

bool post_agregar_like(post_t* post, char* usuario){
    if(abb_pertenece(post->personas_likes, usuario)) return true;
    
    if(!abb_guardar(post->personas_likes, usuario, NULL)) return false;
    
    post->cant_likes++;
    return true;
}

size_t post_cant_likes(post_t* post){
    return post->cant_likes;
}

lista_t* post_obtener_likes(post_t* post){
    abb_iter_t* iter = abb_iter_in_crear(post->personas_likes);
    if(!iter) return NULL;

    lista_t* lista = lista_crear();
    if(!lista) {
        abb_iter_in_destruir(iter);
        return NULL;
    }
    while(!abb_iter_in_al_final(iter)){
        char* clave = (char*)abb_iter_in_ver_actual(iter);
        lista_insertar_ultimo(lista, clave);
        abb_iter_in_avanzar(iter);
    }
    abb_iter_in_destruir(iter);
    return lista;
}

const char* post_obtener_texto(post_t* post){
    return post->texto;
}

const char* post_obtener_autor(post_t* post){
    return post->autor;
}

size_t post_obtener_id(post_t* post){
    return post->id;
}

