#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "lista.h"

typedef struct nodo{
    void* dato;
    struct nodo* prox;
} nodo_t;

struct lista{
    size_t largo;
    nodo_t* prim;
    nodo_t* ult;
};

struct lista_iter{
    nodo_t *anterior;
    nodo_t *actual;
    lista_t *lista;
};

typedef void (*destruir_dato)(void *);


nodo_t* nodo_crear(void* valor){
    nodo_t* nodo = malloc(sizeof(nodo_t));
    if(!nodo) return NULL;
    nodo->dato = valor;
    nodo->prox = NULL;
    return nodo;
}

lista_t *lista_crear(){
    lista_t *lista = malloc(sizeof(lista_t));
    if(lista == NULL) return NULL;
    
    lista->prim = NULL;
    lista->ult = NULL;
    lista->largo = 0;
    return lista;
}

bool lista_esta_vacia(const lista_t *lista){
    return lista->largo == 0;
}

bool lista_insertar_primero(lista_t *lista, void* valor){
    nodo_t *nuevo = nodo_crear(valor);
    if(!nuevo) return false;

    if(lista_esta_vacia(lista)){
        lista->prim = nuevo;
        lista->ult = lista->prim;
        lista->largo++;
        return true;
    }
    nuevo->prox = lista->prim;
    lista->prim = nuevo;
    lista->largo++;
    return true;
}

void *lista_borrar_primero(lista_t *lista){
    if(lista_esta_vacia(lista)) return NULL;
    nodo_t* viejo = lista->prim;
    void* valor = viejo->dato;
    lista->prim = lista->prim->prox;
    free(viejo);
    lista->largo--;
    if(lista->largo == 0) lista->ult = NULL;
    return valor;
}

bool lista_insertar_ultimo(lista_t *lista, void *dato){
    if(lista_esta_vacia(lista)){
        return lista_insertar_primero(lista, dato);  
    }
    nodo_t* nuevo = nodo_crear(dato);
    if(nuevo == NULL) return false;

    lista->ult->prox = nuevo;
    lista->ult = nuevo;
    lista->largo++;
    return true;
}

void *lista_ver_primero(const lista_t *lista){
    return lista->prim == NULL? NULL: lista->prim->dato;
}

void *lista_ver_ultimo(const lista_t* lista){
    return lista->ult == NULL? NULL: lista->ult->dato;
}

size_t lista_largo(const lista_t *lista){
    return lista->largo;
}

void lista_destruir(lista_t *lista, destruir_dato func){
        nodo_t *act = lista->prim;
        while(act){
            nodo_t* viejo = act;
            act = act->prox;
            if(func) func(viejo->dato);   
            free(viejo);
        }
    free(lista);
}

void lista_iterar(lista_t *lista, bool visitar(void *dato, void *extra), void *extra){
    nodo_t *act = lista->prim;
    bool ok = true;
    while(ok && act){
        ok = visitar(act->dato, extra);
        act = act->prox;
    }
}


lista_iter_t *lista_iter_crear(lista_t *lista){
    lista_iter_t* iter = malloc(sizeof(lista_iter_t));
    if(iter == NULL) return NULL;

    iter->lista = lista;
    iter->actual = lista->prim;
    iter->anterior = NULL;
    return iter;
}

bool lista_iter_al_final(const lista_iter_t *iter){
    return iter->actual == NULL;   
}

bool lista_iter_avanzar(lista_iter_t *iter){
    if(lista_iter_al_final(iter)) return false;
    iter->anterior = iter->actual;
    iter->actual = iter->actual->prox;
    return true;
}

bool lista_iter_insertar(lista_iter_t *iter, void* dato){
    nodo_t* nuevo = nodo_crear(dato);
    if(nuevo == NULL) return false;
    
    if (lista_iter_al_final(iter))  iter->lista->ult = nuevo;

    if(iter->anterior == NULL){
        iter->lista->prim = nuevo;
    }else{  
   iter->anterior->prox = nuevo;
    } 
   nuevo->prox = iter->actual;
   iter->actual = nuevo;
   iter->lista->largo++;
   return true;    
}

void* lista_iter_borrar(lista_iter_t *iter){
    if(lista_iter_al_final(iter) || !(iter->lista->prim)) return NULL;
    nodo_t *viejo = iter->actual;
    void* dato = viejo->dato;
    iter->lista->largo--;
    if(iter->lista->largo == 0) iter->lista->ult = NULL;
    if(iter->anterior == NULL){
         iter->actual = iter->actual->prox;
         iter->lista->prim = iter->actual;
         free(viejo);
         return dato;     
     }
    if (iter->actual->prox == NULL){
         iter->lista->ult = iter->anterior;
     }
     iter->anterior->prox = iter->actual->prox;
     iter->actual = iter->actual->prox;
     free(viejo);
     return dato;
}

void *lista_iter_ver_actual(const lista_iter_t *iter){
    nodo_t *actual = iter->actual;
    return actual? actual->dato: actual;
}

void lista_iter_destruir(lista_iter_t *iter){
    free(iter);
}
