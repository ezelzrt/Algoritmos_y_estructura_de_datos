#define _POSIX_C_SOURCE 200809L
#include <stdbool.h>  
#include <stddef.h>   
#include <stdio.h>
#include <stdlib.h>
#define TAM_INICIAL 2
#include "heap.h"

struct heap{
    void** datos;
    size_t cant;
    size_t tam;
    cmp_func_t cmp;
};

void swap(void **pa, void **pb){
    void *pc; 
    pc  = *pa;
    *pa = *pb;
    *pb = pc;
}

heap_t *heap_crear(cmp_func_t cmp){
    heap_t* heap = malloc(sizeof(heap_t));
    if(!heap) return NULL;

    heap->cmp = cmp;
    heap->tam = TAM_INICIAL;
    heap->datos = malloc(sizeof(void*) * heap->tam);
    if(!heap->datos){
        free(heap);
        return NULL;
    }
    heap->cant = 0;
    return heap;
}

bool heap_redimensionar(heap_t* heap, size_t tam_nuevo){
    void** datos_nuevo = realloc(heap->datos, tam_nuevo * sizeof(void*));
    if(!datos_nuevo) return false;
    heap->tam = tam_nuevo;
    heap->datos = datos_nuevo;
    return true;
}

bool heap_esta_vacio(const heap_t *heap){
    return heap->cant == 0;
}

void upheap(heap_t* heap, size_t hijo){
    if(hijo == 0) return;
    size_t padre = (hijo - 1) / 2;
    if(heap->cmp(heap->datos[padre], heap->datos[hijo]) >= 0) return;

     swap(&heap->datos[padre], &heap->datos[hijo]);
     upheap(heap, padre);
}

bool heap_encolar(heap_t *heap, void *elem){
    if(heap->tam == heap->cant){
        if(!heap_redimensionar(heap, heap->tam * 2)) return false;
     }
    heap->datos[heap->cant] = elem;  
    upheap(heap, heap->cant);
    heap->cant++;
    return true;
}

heap_t *heap_crear_arr(void *arreglo[], size_t n, cmp_func_t cmp){
    heap_t* heap = malloc(sizeof(heap_t));
    if(!heap) return NULL;
    heap->cant = 0;
    heap->tam = TAM_INICIAL;
    heap->cmp = cmp;
    heap->datos = malloc(sizeof(void*) * heap->tam);
    if(!heap->datos){
        free(heap);
        return NULL;
    }
    for(size_t i = 0; i < n; i++){
        heap_encolar(heap, arreglo[i]);
    }
    return heap;
}

void downheap(heap_t* heap, size_t act){
    if((2*act + 1) >= heap->cant) return;
    
    size_t izq = (2 * act  + 1);
    size_t der = (2 * act + 2);
    size_t max = 0;
    if(der >= heap->cant){
        max = izq;
    }else{
        max = heap->cmp(heap->datos[izq], heap->datos[der]) > 0 ? izq : der;
    }
    if(heap->cmp(heap->datos[max], heap->datos[act]) > 0) swap(&heap->datos[act], &heap->datos[max]);
    downheap(heap, max); 
}

void *heap_desencolar(heap_t *heap){
    if(heap_esta_vacio(heap)) return NULL;

    if((heap->cant) * 4 <= heap->tam){
        if(!heap_redimensionar(heap, (heap->tam) / 2)) return false;
    }
    void* valor = heap->datos[0];
    swap(&heap->datos[0], &heap->datos[(heap->cant) - 1]);
    heap->cant--;
    downheap(heap, 0);
    return valor;
}

void heap_destruir(heap_t *heap, void (*destruir_elemento)(void *e)){
    while(!heap_esta_vacio(heap)){
        void* elem = heap_desencolar(heap);
        if(destruir_elemento) destruir_elemento(elem);
    }
    free(heap->datos);
    free(heap);
}

size_t heap_cantidad(const heap_t *heap){
    return heap->cant;
}

void *heap_ver_max(const heap_t *heap){
    return heap_esta_vacio(heap) ? NULL : heap->datos[0];
}

void downheap_arr(void* elementos[], size_t n, size_t act, cmp_func_t cmp){
    if(2 * act + 1 >= n) return;
    size_t izq = 2 * act + 1;
    size_t der = 2* act + 2;
    size_t max;
    if(der >= n){
        max = izq;
    }else{
        max = cmp(elementos[izq], elementos[der]) > 0 ? izq : der;
    }
    if(cmp(elementos[max], elementos[act]) > 0) swap(&elementos[max], &elementos[act]);
    downheap_arr(elementos, n, max, cmp);
}

void heapify(void* elementos[], size_t cant, cmp_func_t cmp){
    for(int i = (int)(cant/ 2) - 1; i >= 0; i--){
        downheap_arr(elementos, cant, (size_t)i, cmp); 
    }
}

void heap_sort(void *elementos[], size_t cant, cmp_func_t cmp){
    heapify(elementos, cant, cmp);
    for(int i = (int)(cant-1); i > 0; i--){
        swap(&elementos[0], &elementos[i]);
        downheap_arr(elementos, (size_t)i, 0, cmp);
    }
}


