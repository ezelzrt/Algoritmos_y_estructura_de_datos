#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <string.h>
#include "pila.h"
#include "abb.h"
#include <stdlib.h>

typedef struct abb_nodo{
    struct abb_nodo* izq;
    struct abb_nodo* der;
    char* clave;
    void* dato;
}abb_nodo_t;

struct abb{
    abb_nodo_t* raiz;
    abb_comparar_clave_t comparar;
    abb_destruir_dato_t destruir_dato;
    size_t cantidad;    
};

struct abb_iter{
    pila_t* elementos;
};

abb_nodo_t* abb_nodo_crear(const char* clave, void* dato){
    abb_nodo_t* nodo = malloc(sizeof(abb_nodo_t));
    if(!nodo) return NULL;

    nodo->dato = dato;
    char* copia_clave = strdup(clave);
    nodo->clave = copia_clave;
    nodo->izq = NULL;
    nodo->der = NULL;
    return nodo;
}

void* abb_nodo_destruir(abb_t *arbol, abb_nodo_t* nodo){
    void* valor = nodo->dato;
    free(nodo->clave);
    free(nodo);
    return valor;
}

abb_t* abb_crear(abb_comparar_clave_t cmp, abb_destruir_dato_t destruir_dato){
    abb_t* abb = malloc(sizeof(abb_t));
    if(!abb) return NULL;

    abb->destruir_dato = destruir_dato;
    abb->comparar = cmp;
    abb->raiz = NULL;
    abb->cantidad = 0;
    return abb;
}

bool _abb_pertenece(const abb_t *arbol, abb_nodo_t* nodo, const char* clave){
    if(!nodo) return false;
    if(arbol->comparar(nodo->clave, clave) == 0) return true;

    return arbol->comparar(nodo->clave, clave) > 0? _abb_pertenece(arbol, nodo->izq, clave): _abb_pertenece(arbol, nodo->der, clave);
}

bool abb_pertenece(const abb_t *arbol, const char *clave){
    abb_nodo_t* nodo = arbol->raiz;
    return _abb_pertenece(arbol, nodo, clave);
}

bool _abb_guardar(abb_t *arbol, abb_nodo_t* nodo, const char *clave, void *dato, abb_nodo_t* nuevo){
    if(!arbol->raiz){
        arbol->raiz = nuevo;
        return true;
    }
    if(arbol->comparar(nodo->clave, clave) == 0){
        if(arbol->destruir_dato) arbol->destruir_dato(nodo->dato);
        
        nodo->dato = dato;
        return true;
    }
    abb_nodo_t* siguiente;
    if(arbol->comparar(nodo->clave, clave) > 0){
        siguiente = nodo->izq;
        if(!siguiente){
           nodo->izq = nuevo;
           return true;
        }
    } else {
        siguiente = nodo->der;
        if(!siguiente){
            nodo->der = nuevo;
            return true;
        }
    }
    return _abb_guardar(arbol, siguiente, clave, dato, nuevo);
}

bool abb_guardar(abb_t *arbol, const char* clave, void *dato){
    abb_nodo_t* nuevo = NULL;
    if(!abb_pertenece(arbol, clave)){
        nuevo = abb_nodo_crear(clave, dato);
        if(!nuevo) return false;
        arbol->cantidad++;
    }
    return _abb_guardar(arbol, arbol->raiz, clave, dato, nuevo);
}

void* _abb_obtener(const abb_t* arbol, abb_nodo_t* nodo, const char *clave){
    if(arbol->comparar(nodo->clave, clave) == 0){
        void* valor = nodo->dato;
        return valor;
    }
    return arbol->comparar(nodo->clave, clave) > 0? _abb_obtener(arbol, nodo->izq, clave): _abb_obtener(arbol, nodo->der, clave);
}

void* abb_obtener(const abb_t *arbol, const char *clave){
    if(!abb_pertenece(arbol, clave)) return NULL;
    
    return _abb_obtener(arbol, arbol->raiz, clave);
}

abb_nodo_t* ult_izq_der(abb_nodo_t* nodo){
    if(!nodo->der) return nodo;
    return ult_izq_der(nodo->der);
}

bool tiene_2_hijos(abb_t *arbol, abb_nodo_t* nodo, const char* clave){
    if(arbol->comparar(nodo->clave, clave) == 0) return nodo->izq && nodo->der;

    if(arbol->comparar(nodo->clave, clave) > 0) return tiene_2_hijos(arbol, nodo->izq, clave);

    return tiene_2_hijos(arbol, nodo->der, clave);
}

void* _abb_borrar_menos_hijos(abb_t *arbol, abb_nodo_t* nodo, const char* clave){
    if(arbol->comparar(nodo->clave, clave) > 0){
        abb_nodo_t* actual = nodo->izq;
        if(actual && arbol->comparar(actual->clave, clave) == 0){
            nodo->izq = actual->izq? actual->izq: actual->der;
            return abb_nodo_destruir(arbol, actual);
        }
        return _abb_borrar_menos_hijos(arbol, nodo->izq, clave);
    }
    abb_nodo_t* actual = nodo->der;
    if(nodo->der && arbol->comparar(actual->clave, clave) == 0){
        nodo->der = actual->izq? actual->izq: actual->der;
        return abb_nodo_destruir(arbol, actual);
    }
    return _abb_borrar_menos_hijos(arbol, nodo->der, clave);
}

void* cambio_2_hijos(abb_t* arbol, abb_nodo_t* actual){
    void* valor = actual->dato;
    abb_nodo_t* nodo_borrar = ult_izq_der(actual->izq);
    actual->dato = nodo_borrar->dato;
    char* aux = strdup(nodo_borrar->clave);
    _abb_borrar_menos_hijos(arbol, arbol->raiz, nodo_borrar->clave);
    free(actual->clave);
    actual->clave = aux;
    return valor; 
}

void* _abb_borrar_2_hijos(abb_t *arbol, abb_nodo_t* nodo, const char* clave){
      abb_nodo_t* actual;
     if(arbol->comparar(nodo->clave, clave) > 0){
         actual = nodo->izq;
         if(actual && arbol->comparar(actual->clave, clave) == 0){
             return cambio_2_hijos(arbol, actual);}
         
         return _abb_borrar_2_hijos(arbol, nodo->izq, clave);
     }
     actual = nodo->der;
     if(actual && arbol->comparar(actual->clave, clave) == 0){
         return cambio_2_hijos(arbol, actual);
         }
     return _abb_borrar_2_hijos(arbol, nodo->der, clave);
}

void* abb_borrar(abb_t *arbol, const char* clave){
    if(!abb_pertenece(arbol,clave)) return NULL;

    arbol->cantidad--;
    if(arbol->comparar(arbol->raiz->clave, clave) == 0){
        if(tiene_2_hijos(arbol,arbol->raiz, clave)) return cambio_2_hijos(arbol, arbol->raiz);
        abb_nodo_t* raiz = arbol->raiz;
        arbol->raiz = arbol->raiz->izq? arbol->raiz->izq: arbol->raiz->der;
        return abb_nodo_destruir(arbol, raiz);
    }
    return tiene_2_hijos(arbol,arbol->raiz, clave) ? _abb_borrar_2_hijos(arbol, arbol->raiz, clave): _abb_borrar_menos_hijos(arbol, arbol->raiz, clave);
}

size_t abb_cantidad(const abb_t *arbol){
    return arbol->cantidad;
}

void _abb_destruir(abb_t *arbol, abb_nodo_t* nodo){
    if(!nodo) return;

    _abb_destruir(arbol, nodo->izq);
    _abb_destruir(arbol, nodo->der);
    if(arbol->destruir_dato) arbol->destruir_dato(nodo->dato);

    free(nodo->clave); 
    free(nodo);
}

void abb_destruir(abb_t *arbol){
    _abb_destruir(arbol, arbol->raiz);
    free(arbol);
}

bool _abb_in_order(abb_nodo_t* nodo, bool visitar(const char *, void *, void *), void *extra){
    if(!nodo) return true;

    if (!_abb_in_order(nodo->izq, visitar, extra)) return false;

    if (!visitar(nodo->clave, nodo->dato, extra)) return false;

    if (!_abb_in_order(nodo->der, visitar, extra)) return false;
    
    return true;
}

void abb_in_order(abb_t *arbol, bool visitar(const char *, void *, void *), void *extra){
    _abb_in_order(arbol->raiz, visitar, extra);     
}

void solo_hijos_izq(abb_nodo_t* nodo, pila_t* pila){
    if(!nodo) return;

    pila_apilar(pila, (void*)nodo);
    solo_hijos_izq(nodo->izq, pila);
}

abb_iter_t *abb_iter_in_crear(const abb_t *arbol){
    abb_iter_t* iter = malloc(sizeof(abb_iter_t));
    if(!iter) return NULL;

    pila_t *pila = pila_crear();
    if(!pila){
        free(iter);
        return NULL;
    }
    iter->elementos = pila;
    solo_hijos_izq(arbol->raiz, iter->elementos);
    return iter;
}

bool abb_iter_in_al_final(const abb_iter_t *iter){
    return pila_esta_vacia(iter->elementos);
}

bool abb_iter_in_avanzar(abb_iter_t *iter){
    if(abb_iter_in_al_final(iter)) return false;

    abb_nodo_t* desapilado = (abb_nodo_t*)pila_desapilar(iter->elementos);
    if(desapilado->der) solo_hijos_izq(desapilado->der, iter->elementos);
    
    return true;
}

const char *abb_iter_in_ver_actual(const abb_iter_t *iter){
    if(abb_iter_in_al_final(iter)) return NULL;

    abb_nodo_t* actual = (abb_nodo_t*)(pila_ver_tope(iter->elementos));
    return actual->clave;
}

void abb_iter_in_destruir(abb_iter_t* iter){
    pila_destruir(iter->elementos);
    free(iter);
}
