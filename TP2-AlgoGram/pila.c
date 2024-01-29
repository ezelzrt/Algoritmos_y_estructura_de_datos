#include <stdlib.h>
#include "pila.h"
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

// ...

pila_t *pila_crear(void){
    pila_t *pila = malloc(sizeof(pila_t));

    if(pila == NULL){
        return NULL;
    }
    pila->capacidad = 2;
    pila->cantidad = 0;
    pila->datos = malloc(pila->capacidad * sizeof(void *));
    
    if(pila->datos == NULL){
        return NULL;
    } 
    return pila;
}

bool pila_redimensionar(pila_t *pila, size_t tam_nuevo){
    void **datos_nuevo = realloc(pila->datos, tam_nuevo * sizeof(void *));

    if(tam_nuevo > 0 && datos_nuevo == NULL){
        return false;
    }
    pila->datos = datos_nuevo;
    return true;
}

void pila_destruir(pila_t *pila){
    if(pila->datos == NULL){
        free(pila);
        return;
    }
    free(pila->datos);
    free(pila);
}


bool pila_esta_vacia(const pila_t *pila){
    return pila->cantidad == 0;
}

bool pila_apilar(pila_t *pila, void *valor){
    
    if (pila->capacidad == pila->cantidad){
        pila->capacidad *= 2;   
        if(!pila_redimensionar(pila, pila->capacidad)){
            return false;
        }
    }
    pila->datos[pila->cantidad] = valor;
    pila->cantidad++; 
    return true;
}


void *pila_desapilar(pila_t *pila){
    if(pila_esta_vacia(pila)){
        return NULL;
    }
    if ((pila->cantidad) * 4  <= pila->capacidad){
        pila->capacidad = (pila->capacidad) / 2;   
        if(!pila_redimensionar(pila, pila->capacidad)){
            return NULL;
        }
    }
    void* valor = pila->datos[(pila->cantidad) - 1];
    pila->cantidad--;  
    return valor;
}

void *pila_ver_tope(const pila_t *pila){
    if(pila_esta_vacia(pila)){
        return NULL;
    }

    return pila->datos[pila->cantidad - 1];
}