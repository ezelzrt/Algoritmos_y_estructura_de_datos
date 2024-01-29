#define _GNU_SOURCE
#include "auxiliares.h"

void login(hash_t* usuarios, char** usuario_actual);

void logout(char** usuario_actual);

post_t* publicar(hash_t* usuarios, char* usuario_actual, size_t id_post);

int ver_siguiente_feed(hash_t* usuarios, char* usuario_actual);

int likear_post(char* usuario_actual);

int mostrar_likes();
