#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "hash.h"

#define CAPACIDAD_INICIAL 5
#define AUMENTO_REDIMENSION 2
#define DISMINUCION_REDIMENSION 2

typedef enum estado{VACIO, OCUPADO, BORRADO}estado_t;

typedef struct celda{
    void* dato;
    char* clave;
    estado_t estado;
}celda_t;

struct hash{
    celda_t* tabla;
    size_t capacidad;
    size_t cantidad;
    hash_destruir_dato_t destruir_dato;
};

struct hash_iter{
    size_t capacidad;
    size_t actual;
    celda_t* tabla;
};

size_t hash_f(const char *str, size_t largo) {
        size_t hash = 5381;
        int c;
        while ((c = *str++))
            hash = ((hash << 5) + hash) + (size_t)c;
        return hash % largo;
}

size_t pos_vacia(celda_t* tabla, size_t capacidad, size_t pos){
    while (tabla[pos].estado != VACIO){
        if (tabla[pos].estado == BORRADO) break;
        
        pos = (pos+1) % capacidad;
    }
    return pos;
}

size_t pos_real(celda_t* tabla, size_t capacidad, size_t pos, const char* clave){
    while (tabla[pos].estado != VACIO){
        if (tabla[pos].estado == OCUPADO && strcmp(tabla[pos].clave, clave) == 0) return pos;

        pos = (pos+1) % capacidad;
    }
    return capacidad+1;
}

hash_t *hash_crear(hash_destruir_dato_t destruir_dato){
    hash_t* hash = malloc(sizeof(hash_t));
    if(hash == NULL) return NULL;

    hash->capacidad = CAPACIDAD_INICIAL;
    hash->cantidad = 0;
    hash->destruir_dato = destruir_dato;
    hash->tabla = malloc(sizeof(celda_t) * hash->capacidad);
    if(hash->tabla == NULL){
        free(hash);
        return NULL;
    }
    for(size_t i = 0; i < CAPACIDAD_INICIAL; i++){
        hash->tabla[i].estado = VACIO;
    }
    return hash;
}


bool hash_pertenece(const hash_t *hash, const char *clave){
    size_t pos = hash_f(clave, hash->capacidad);
    return hash->capacidad+1 != pos_real(hash->tabla, hash->capacidad, pos, clave);
}


bool hash_redimensionar(hash_t *hash, size_t tam_nuevo){
    celda_t *tabla_nueva = malloc(sizeof(celda_t) * tam_nuevo);
    if(!tabla_nueva) return false;

    for(size_t i = 0; i < tam_nuevo; i++){
        tabla_nueva[i].estado = VACIO;
    }
    for(size_t j = 0; j < hash->capacidad; j++){
        celda_t act = hash->tabla[j];
        if(act.estado == OCUPADO){
            char* copia_clave = strdup(act.clave);
            size_t pos = hash_f(copia_clave, tam_nuevo);
            void* valor = act.dato;
            if(tabla_nueva[pos].estado == OCUPADO){
                pos = pos_vacia(tabla_nueva, tam_nuevo, pos);
            } 
            tabla_nueva[pos].estado = OCUPADO;
            tabla_nueva[pos].clave = copia_clave;
            tabla_nueva[pos].dato = valor;
            free(act.clave);
        }
    }
    free(hash->tabla);
    hash->tabla = tabla_nueva;
    return true;
}


bool hash_guardar(hash_t *hash, const char *clave, void *dato){
    float capacidad = (float)hash->capacidad;
    float cantidad = (float)hash->cantidad;
    if(cantidad/capacidad > 0.69) {
        if(!hash_redimensionar(hash, hash->capacidad * AUMENTO_REDIMENSION)) return NULL;

        hash->capacidad *= AUMENTO_REDIMENSION;
    }
    size_t pos = hash_f(clave, hash->capacidad);
    if(hash->tabla[pos].estado == OCUPADO){
        size_t pos_correcta = pos_real(hash->tabla, hash->capacidad, pos, clave);
        if (pos_correcta < hash->capacidad+1){
            void* viejo = hash->tabla[pos_correcta].dato; 
            if(hash->destruir_dato) hash->destruir_dato(viejo);

            hash->tabla[pos_correcta].dato = dato;
            return true; 
        }
        pos = pos_vacia(hash->tabla, hash->capacidad, pos);
    }
    char* copia_clave = strdup(clave);
    hash->tabla[pos].dato = dato;
    hash->tabla[pos].clave = copia_clave;
    hash->tabla[pos].estado = OCUPADO;
    hash->cantidad++;
    return true;
}

void *hash_borrar(hash_t *hash, const char *clave){
    size_t pos = hash_f(clave, hash->capacidad);
    pos = pos_real(hash->tabla, hash->capacidad, pos, clave);
    if (pos == hash->capacidad+1) return NULL;

    float capacidad = (float)hash->capacidad;
    if(capacidad > CAPACIDAD_INICIAL && (float)hash->cantidad / capacidad < 0.29){
        if(!hash_redimensionar(hash, hash->capacidad / DISMINUCION_REDIMENSION)) return NULL;
        hash->capacidad /= DISMINUCION_REDIMENSION;
        pos = hash_f(clave, hash->capacidad);
        pos = pos_real(hash->tabla, hash->capacidad, pos, clave);

    }
    void* valor = hash->tabla[pos].dato;
    free(hash->tabla[pos].clave);
    hash->tabla[pos].estado = BORRADO;
    hash->tabla[pos].dato = NULL;
    hash->tabla[pos].clave = NULL;
    hash->cantidad--;
    return valor;
}

void *hash_obtener(const hash_t *hash, const char *clave){
    size_t pos = hash_f(clave, hash->capacidad);
    pos = pos_real(hash->tabla, hash->capacidad, pos, clave);
    return pos == hash->capacidad+1? NULL:hash->tabla[pos].dato;
}

void hash_destruir(hash_t *hash){
    for(size_t i = 0; i < hash->capacidad; i++){
        if(hash->tabla[i].estado == OCUPADO){
            void* valor = hash->tabla[i].dato;
            free(hash->tabla[i].clave);
            if(hash->destruir_dato) hash->destruir_dato(valor);
        }
    }
    free(hash->tabla);
    free(hash);
}

size_t hash_cantidad(const hash_t *hash){
    return hash->cantidad;
}

hash_iter_t* hash_iter_crear(const hash_t *hash){
    hash_iter_t* iter = malloc(sizeof(hash_iter_t));
    if(!iter) return NULL;

    iter->tabla = hash->tabla;
    iter->capacidad = hash->capacidad;
    size_t pos = 0;
    while(pos != iter->capacidad && iter->tabla[pos].estado != OCUPADO) pos++;
    iter->actual = pos;
    return iter;
}

bool hash_iter_al_final(const hash_iter_t *iter){
    return iter->actual == iter->capacidad; 
}

bool hash_iter_avanzar(hash_iter_t* iter){
     if(hash_iter_al_final(iter)) return false;

     iter->actual++;
     while(!hash_iter_al_final(iter) && iter->tabla[iter->actual].estado != OCUPADO) iter->actual++;

     if(hash_iter_al_final(iter)) return false;

     return true;
}

const char *hash_iter_ver_actual(const hash_iter_t *iter){
    if(hash_iter_al_final(iter)) return NULL;
    
    return iter->tabla[iter->actual].clave;
}

void hash_iter_destruir(hash_iter_t *iter){
    free(iter);
}
