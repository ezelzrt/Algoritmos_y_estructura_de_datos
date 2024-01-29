#define _GNU_SOURCE
#include "algogram.h"
#include "vector.h"


void algogram(FILE* archivo){
    char* usuario_actual = NULL;
    hash_t* usuarios = entrada_archivo(archivo);
    char* linea = NULL;
    size_t tam;
    vector_t* posts = vector_crear();
     while((getline(&linea, &tam, stdin)) != EOF){
         if(strcmp(linea, "login\n") == 0) login(usuarios, &usuario_actual);
             
         else if(strcmp(linea, "logout\n") == 0) logout(&usuario_actual);

         else if(strcmp(linea, "publicar\n") == 0) {
             post_t* nueva_publicacion = publicar(usuarios, usuario_actual, vector_cantidad(posts));
             if(nueva_publicacion) {
                vector_guardar(posts, nueva_publicacion);
                fprintf(stdout, "Post publicado\n");
             }
         }
         else if(strcmp(linea, "ver_siguiente_feed\n") == 0){ 
            int id = ver_siguiente_feed(usuarios, usuario_actual);
            if(id == -1) fprintf(stdout, "Usuario no loggeado o no hay mas posts para ver\n");
            else{
                post_t* post = vector_obtener(posts, (size_t)id);
                imprimir_post(post);
                } 
         }
        else if(strcmp(linea, "likear_post\n") == 0) {
            int id = likear_post(usuario_actual);
            if(id == -1 || (size_t)id >= vector_cantidad(posts)) fprintf(stdout, "Error: Usuario no loggeado o Post inexistente\n");
            else{
                post_t* post = vector_obtener(posts, (size_t)id);
                post_agregar_like(post, usuario_actual);
                fprintf(stdout, "Post likeado\n");
            }       
        }
        else if(strcmp(linea, "mostrar_likes\n") == 0){ 
           int id = mostrar_likes();
           if(id == -1 || (size_t)id >= vector_cantidad(posts)) fprintf(stdout, "Error: Post inexistente o sin likes\n");
           else{
               post_t* post = vector_obtener(posts, (size_t)id);
               lista_t* lista_likes = post_obtener_likes(post);
               if(lista_esta_vacia(lista_likes)) fprintf(stdout, "Error: Post inexistente o sin likes\n");
               else imprimir_lista(lista_likes);
                
               lista_destruir(lista_likes, NULL);
           }
        }
    }
    free(linea);
    if(usuario_actual) free(usuario_actual);
    hash_destruir(usuarios);
    vector_destruir(posts, _post_destruir);
}

int main(int argc, char* argv[]){
    if(argc < 2) {
        fprintf(stdout, "%s\n", "Error: no se añadió un archivo\n");
        return -1;
        }
    

    FILE *archivo = fopen(argv[1], "r");
    if(archivo == NULL) {
        fprintf(stdout, "%s\n", "Error: archivo fuente inaccesible\n");
        return -1;
    }
    algogram(archivo);
    return 0;
}

