#include "cola.h"

#include <stdlib.h>


typedef struct nodo{
    void* dato;
    struct nodo* prox;
} nodo_t;

nodo_t* nodo_crear(void* valor){
    nodo_t* nodo = malloc(sizeof(nodo_t));
    if (!nodo){
        return NULL;
    }
    nodo->dato = valor;
    nodo->prox = NULL;
    return nodo;
}

void nodo_destruir(nodo_t* nodo){
    free(nodo);
}


typedef struct cola {
    nodo_t* prim;
    nodo_t* ult;
} cola_t;

cola_t *cola_crear(void){
    cola_t* cola = malloc(sizeof(cola_t));
    if (!cola){
        return NULL;
    }
    cola->prim = NULL;
    cola->ult = NULL;
    return cola;
}

void cola_destruir(cola_t *cola, void (*destruir_dato)(void *)){    
    nodo_t* act = cola->prim; 
    while (act){
        nodo_t* sig = act->prox;
        if (destruir_dato){
            destruir_dato(act->dato);
        }
        nodo_destruir(act);
        act = sig;
    }
    free(cola);
}

bool cola_esta_vacia(const cola_t *cola){
    return cola->prim == NULL;
}

bool cola_encolar(cola_t *cola, void *valor){
    nodo_t* nodo = nodo_crear(valor);
    if (!nodo){
        return false;
    }
    if (cola_esta_vacia(cola)){
        cola->prim = nodo;
    } else {
        cola->ult->prox = nodo;
    }
    cola->ult = nodo;
    return true;
}

void *cola_ver_primero(const cola_t *cola){
    return cola_esta_vacia(cola) ? NULL : cola->prim->dato;
}

void *cola_desencolar(cola_t *cola){
    if (cola_esta_vacia(cola)){
        return NULL;
    }
    void* valor = cola->prim->dato;
    nodo_t* sig = cola->prim->prox;
    nodo_destruir(cola->prim);

    if (sig == NULL){
        cola->ult = NULL;
    }
    cola->prim = sig;
    return valor;
}
