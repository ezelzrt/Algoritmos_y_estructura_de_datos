#define _GNU_SOURCE
#include "algogram.h"

void login(hash_t* usuarios, char** usuario_actual){
    char* nombre_usuario = pedir_linea();
    if(*usuario_actual) {
        fprintf(stdout, "Error: Ya habia un usuario loggeado\n");
        free(nombre_usuario);
        return;
    }    
    if(!hash_pertenece(usuarios, nombre_usuario)){
        fprintf(stdout, "Error: usuario no existente\n");
        free(nombre_usuario);
        return;
    }
    *usuario_actual = strdup(nombre_usuario);
    free(nombre_usuario);
    fprintf(stdout, "Hola %s\n", *usuario_actual);
}

void logout(char** usuario_actual){
    if(!*usuario_actual){
        fprintf(stdout, "Error: no habia usuario loggeado\n");
        return;
    }
    free(*usuario_actual);
    *usuario_actual = NULL;
    fprintf(stdout, "Adios\n");
}

 post_t* publicar(hash_t* usuarios, char* usuario_actual, size_t id_post){
     if(!usuario_actual){
         fprintf(stdout, "Error: no habia usuario loggeado\n");
         return NULL;
     }
     char* texto = pedir_linea();
     post_t* publicacion = post_crear(texto, id_post, usuario_actual);
     agregar_al_feed(usuarios, id_post, usuario_actual);
     free(texto);
     return publicacion;
 }

int ver_siguiente_feed(hash_t* usuarios, char* usuario_actual){
    if(!usuario_actual) return -1;

    usuario_t* usuario = (usuario_t*)hash_obtener(usuarios, usuario_actual);
    int id = obtener_id_siguiente_feed(usuario);
    return id >= 0 ? id : -1; 
}

int likear_post(char* usuario_actual){
    if(!usuario_actual) return -1;

    char* id = pedir_linea();
    int id_post = atoi(id);
    free(id);
    return id_post >= 0 ? id_post : -1;
}

int mostrar_likes(){
    char* id = pedir_linea();
    int id_post = atoi(id);
    free(id);
    return id_post;
}

