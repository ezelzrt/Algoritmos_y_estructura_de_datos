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

bool pila_redimensionar(pila_t *pila){
    size_t n = pila->capacidad;

    if (pila->cantidad == n){
        n *= 2;
    } else {
    if (pila->cantidad * 4 <= n && n > CAPACIDAD_INICIAL){
        n /= 2;
    } else {
        return true;
    }
    }
    void *datos_nuevos = realloc(pila->datos, n * sizeof(void*));
    if (datos_nuevos == NULL){
        if (n > pila->capacidad){
            pila->cantidad--;
        } else {
            pila->cantidad++;
        }
        return false;
    }
    pila->capacidad = n;
    pila->datos = datos_nuevos;
    return true;
}

bool pila_esta_vacia(const pila_t *pila){
    return pila->cantidad == 0;
}

bool pila_apilar(pila_t *pila, void *valor){
    pila->datos[pila->cantidad] = valor;
    pila->cantidad++;
    return pila_redimensionar(pila);
}

void *pila_ver_tope(const pila_t *pila){
    if (pila_esta_vacia(pila)){
        return NULL;
    }
    void *dato = pila->datos[pila->cantidad - 1];

    return dato;
}

void *pila_desapilar(pila_t *pila){
    if (pila_esta_vacia(pila)){
        return NULL;
    }
    pila->cantidad--;
    if (!pila_redimensionar(pila)){
        return NULL;
    }
    return pila->datos[pila->cantidad];
}
