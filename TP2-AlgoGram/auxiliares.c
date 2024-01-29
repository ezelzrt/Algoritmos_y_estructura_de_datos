#define _GNU_SOURCE
#include "auxiliares.h" 

void _destruir_usuario(void* usuario){
    destruir_usuario((usuario_t*)usuario);
}

void _post_destruir(void* post){
    post_destruir((post_t*)post);
}

hash_t* entrada_archivo(FILE* archivo){
    char* linea = NULL;
    size_t tam;
    int afinidad = 0;
    hash_t* usuarios = hash_crear(_destruir_usuario);
    while((getline(&linea, &tam, archivo)) != EOF){ 
        linea[strlen(linea) - 1] = '\0';
        char* nombre = linea;
        usuario_t* usuario = crear_usuario(nombre, afinidad);
        afinidad++;
        hash_guardar(usuarios, nombre, usuario);
    }
    free(linea);
    fclose(archivo); 
    return usuarios;
}

char* pedir_linea(){
    char* linea = NULL;
    size_t tam;
    ssize_t res = getline(&linea, &tam, stdin);
    linea[strlen(linea) - 1] = '\0';
    return res == EOF ? NULL : linea; 
}

void imprimir_lista(lista_t* lista_likes){
    lista_iter_t* iter = lista_iter_crear(lista_likes);
    fprintf(stdout, "El post tiene %ld likes:\n", lista_largo(lista_likes));
    while(!lista_iter_al_final(iter)){
        const char* clave = (char*)lista_iter_ver_actual(iter);
        fprintf(stdout, "\t%s\n", clave);
        lista_iter_avanzar(iter);
    }
    lista_iter_destruir(iter);
}

void imprimir_post(post_t* post){
    const char* texto = post_obtener_texto(post);
    const char* autor = post_obtener_autor(post);
    fprintf(stdout, "Post ID %ld\n", post_obtener_id(post));
    fprintf(stdout, "%s dijo: %s\n", autor, texto);
    fprintf(stdout, "Likes: %ld\n", post_cant_likes(post));
}
