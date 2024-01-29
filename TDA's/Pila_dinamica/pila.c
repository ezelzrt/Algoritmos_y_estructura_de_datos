#include "pila.h"

#include <stdlib.h>
#include <stdbool.h>

/* Definición del struct pila proporcionado por la cátedra.
 */
struct pila {
    void **datos;
    size_t cantidad;   // Cantidad de elementos almacenados.
    size_t capacidad;  // Capacidad del arreglo 'datos'.
};

/* *****************************************************************
 *                    PRIMITIVAS DE LA PILA
 * *****************************************************************/
#define CAPACIDAD_INICIAL 10
#define AUMENTO_REDIMENSION 2
#define DISMINUCION_REDIMENSION 2

pila_t *pila_crear(void){
    pila_t *pila = malloc(sizeof(pila_t));
    if (pila == NULL){
        return NULL;
    }
    pila->datos = malloc(CAPACIDAD_INICIAL * sizeof(void*));
    if (pila->datos == NULL){
        free(pila);
        return NULL;
    }
    pila->cantidad = 0;
    pila->capacidad = CAPACIDAD_INICIAL;
    return pila;
}

void pila_destruir(pila_t *pila){
    free(pila->datos);
    free(pila);
}

bool pila_redimensionar(pila_t *pila, size_t capacidad_nueva){
    void *datos_nuevos = realloc(pila->datos, capacidad_nueva * sizeof(void*));
    if (datos_nuevos == NULL){
        return false;
    }
    pila->capacidad = capacidad_nueva;
    pila->datos = datos_nuevos;
    return true;
}

bool pila_esta_vacia(const pila_t *pila){
    return pila->cantidad == 0;
}

bool pila_apilar(pila_t *pila, void *valor){
    size_t capacidad = pila->capacidad; 
    if (pila->cantidad+1 == capacidad){
        if (!pila_redimensionar(pila, capacidad * AUMENTO_REDIMENSION)){
            return false;
        }
    }
    pila->datos[pila->cantidad] = valor;
    pila->cantidad++;
    return true;
}

void *pila_ver_tope(const pila_t *pila){
    if (pila_esta_vacia(pila)){
        return NULL;
    }
    return pila->datos[pila->cantidad - 1];
}

void *pila_desapilar(pila_t *pila){
    if (pila_esta_vacia(pila)){
        return NULL;
    }
    if (pila->cantidad * 4 <= pila->capacidad && pila->capacidad > CAPACIDAD_INICIAL){
        if (!pila_redimensionar(pila, pila->capacidad / DISMINUCION_REDIMENSION)){
            return NULL;
        }
    }
    pila->cantidad--;
    return pila->datos[pila->cantidad];
}
