#include "usuario.h"

struct usuario{
    char* nombre;
    int id;
    heap_t* feed;
};

struct afinidad_post{
    int afinidad;
    size_t id_post;
};

int comparar_afinidad(const void* a, const void* b){
    afinidad_post_t x = *(afinidad_post_t*)a; 
    afinidad_post_t y = *(afinidad_post_t*)b;
    if(x.afinidad == y.afinidad) return x.id_post < y.id_post ? 1 : -1;
    
    return x.afinidad < y.afinidad ? 1 : -1;
} 


usuario_t* crear_usuario(char* nombre, int id){
    usuario_t* usuario = malloc(sizeof(usuario_t));
    usuario->nombre = strdup(nombre);
    usuario->id = id;
    heap_t* feed = heap_crear(comparar_afinidad);
    usuario->feed = feed;
    return usuario;
}

void destruir_usuario(usuario_t* usuario){
    heap_destruir(usuario->feed, free);
    free(usuario->nombre);
    free(usuario);
}

void agregar_al_feed(hash_t* usuarios, size_t id_post, char* nombre_actual){
    hash_iter_t* iter = hash_iter_crear(usuarios);
    int id_actual = ((usuario_t*)hash_obtener(usuarios, nombre_actual))->id;
    if(!iter) return;
    
    while(!hash_iter_al_final(iter)){
        char* clave = (char*)hash_iter_ver_actual(iter);
        usuario_t* otro_usuario = (usuario_t*)hash_obtener(usuarios, clave);
        if(id_actual != otro_usuario->id){
            int afinidad = otro_usuario->id - id_actual;
            afinidad = afinidad > 0 ? afinidad : -afinidad;
            afinidad_post_t* afinidad_ultimo_post = malloc(sizeof(afinidad_post_t));
            afinidad_ultimo_post->id_post = id_post;
            afinidad_ultimo_post->afinidad = afinidad;
            heap_encolar(otro_usuario->feed, afinidad_ultimo_post);
        }
        hash_iter_avanzar(iter);
    }
    hash_iter_destruir(iter);
}

int obtener_id_siguiente_feed(usuario_t* usuario){
    if(heap_esta_vacio(usuario->feed)) return -1;
    afinidad_post_t* afi = (afinidad_post_t*)heap_desencolar(usuario->feed);
    int id = (int)afi->id_post;
    free(afi);
    return id;
}
