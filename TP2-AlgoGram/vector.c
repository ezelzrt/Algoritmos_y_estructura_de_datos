#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "vector.h"
#define TAM_INICIAL 2

struct vector{
    void** datos;
    size_t cant;
    size_t tam;
};

vector_t* vector_crear(){
    vector_t* vector = malloc(sizeof(vector_t));
    if(!vector) return NULL;

    vector->datos = malloc(sizeof(void*) * TAM_INICIAL);
    if(!vector->datos){ 
        free(vector);
        return NULL;
    }
    vector->tam = TAM_INICIAL;
    vector->cant = 0;
    return vector;
}

bool vector_redimensionar(vector_t* vector, size_t tam_nuevo){
    void** datos_nuevo = realloc(vector->datos, tam_nuevo * sizeof(void*));
    if(!datos_nuevo) return NULL;

    vector->datos = datos_nuevo;
    vector->tam = tam_nuevo;
    return true;
}

bool vector_guardar(vector_t* vector, void* dato){
    if(vector->tam == vector->cant){
        if(!vector_redimensionar(vector, vector->tam * 2)) return false;
    }
    vector->datos[vector->cant] = dato;
    vector->cant++;
    return true;
}

void* vector_borrar(vector_t* vector, size_t pos){
    if(pos > vector->cant) return NULL; 

    if(vector->cant * 4 <= vector->tam){
        if(!vector_redimensionar(vector, (vector->tam)/ 2)) return NULL; 
    }
    void* valor = vector->datos[pos];
    for(size_t i = pos + 1; i < vector->cant; i++){
        vector->datos[i-1] = vector->datos[i];
    }
    vector->cant--;
    return valor;
}

size_t vector_cantidad(vector_t* vector){
    return vector->cant;
}

size_t vector_tam(vector_t* vector){
    return vector->tam;
}

void* vector_obtener(vector_t* vector, size_t pos){
    if(pos >= vector->tam) return NULL;

    return vector->datos[pos];
}

void vector_destruir(vector_t* vector, destruir_dato_t destruir){
    if(destruir){
        for(size_t i = 0; i < vector->cant; i++){
            destruir(vector->datos[i]);
        }
    }
    free(vector->datos);
    free(vector);
}