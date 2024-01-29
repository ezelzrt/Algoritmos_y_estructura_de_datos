#define _POSIX_C_SOURCE 200809L
#include "testing.h"
#include "heap.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>  // For ssize_t in Linux.
#include <stdbool.h>

int comparar_int(const void* a, const void*b){
    if(*(int*)a == *(int*)b) return 0;

    return *(int*)a > *(int*)b ? 1: -1;
}

bool esta_ordenado(void* elementos[], size_t n){
    for(size_t i = 1; i < n; i++){
        if(comparar_int(elementos[i], elementos[i - 1]) < 0) return false; 
    }
    return true;
}

static void prueba_crear_heap_vacio()
{   
    printf("COMIENZO PRUEBAS HEAP VACIO\n");
    heap_t* heap = heap_crear(comparar_int);

    print_test("Prueba heap crear vacio", heap);
    print_test("Prueba  la cantidad de elementos es 0", heap_cantidad(heap) == 0);
    print_test("Prueba heap ver max es NULL", !heap_ver_max(heap));
    print_test("Prueba heap desencolar devuelve NULL", !heap_desencolar(heap));
    heap_destruir(heap, NULL);
}

static void prueba_heap_encolar(){
    printf("COMIENZO PRUEBAS HEAP ENCOLAR\n");
    heap_t* heap = heap_crear(comparar_int);
    int *a = malloc(sizeof(int));
    int *b = malloc(sizeof(int));
    int *c = malloc(sizeof(int));
    int *d = malloc(sizeof(int));
    *a = 3;
    *b = 5;
    *c  = 10;
    *d = 7;    
    print_test("se encolo el elemento a", heap_encolar(heap, a));
    print_test("el maximo ahora es a", (int*)heap_ver_max(heap) == a);
    print_test("Prueba  la cantidad de elementos es 1", heap_cantidad(heap) == 1);
    print_test("se encolo el elemento b", heap_encolar(heap, b));
    print_test("Prueba  la cantidad de elementos es 2", heap_cantidad(heap) == 2);
    print_test("el maximo ahora es b", (int*)heap_ver_max(heap) == b);
    print_test("se encolo el elemento c", heap_encolar(heap, c));
    print_test("Prueba  la cantidad de elementos es 3", heap_cantidad(heap) == 3);
    print_test("el maximo ahora es c", (int*)heap_ver_max(heap) == c);
    print_test("se encolo el elemento d", heap_encolar(heap, d));
    print_test("Prueba  la cantidad de elementos es 4", heap_cantidad(heap) == 4);
    print_test("el maximo sigue siendo c", (int*)heap_ver_max(heap) == c);
    heap_destruir(heap, free);
}

static void prueba_heap_desencolar(){
    printf("COMIENZO PRUEBAS HEAP DESENCOLAR\n");
    heap_t* heap = heap_crear(comparar_int);    
    int a = 3;
    int b = 1;
    int c = 15;
    int d = 12;
    bool ok = true;

    /* Inserta varios elementos y verifica el invariante*/
    ok += heap_encolar(heap, &a);
    ok += (int*)heap_ver_max(heap) == &a;
    ok += heap_cantidad(heap) == 1;
    ok += heap_encolar(heap, &b);
    ok += heap_cantidad(heap) == 2;
    ok += (int*)heap_ver_max(heap) == &a;
    ok += heap_encolar(heap, &c);
    ok += heap_cantidad(heap) == 3;
    ok += (int*)heap_ver_max(heap) == &c;
    ok += heap_encolar(heap, &d);
    ok += heap_cantidad(heap) == 4;
    ok += heap_ver_max(heap) == &c;
    print_test("se encolaron 4 elementos, se mantuvo el invariante del heap y la cantidad de elementos es correcta", ok);

    /* desencola los elementos insertados y verifica que se cumple el invariante */
    print_test("heap desencolar es igual al elemento que estaba en el maximo", (int*)heap_desencolar(heap) == &c);
    print_test("el maximo ahora es d", (int*)heap_ver_max(heap) == &d);
    print_test("la cantidad de elementos ahora es 3", heap_cantidad(heap) == 3);
    print_test("heap desencolar es igual al elemento que estaba en el maximo", (int*)heap_desencolar(heap) == &d);
    print_test("el maximo ahora es a", (int*)heap_ver_max(heap) == &a);
    print_test("la cantidad de elementos ahora es 2", heap_cantidad(heap) == 2);
    print_test("heap desencolar es igual al elemento que estaba en el maximo", (int*)heap_desencolar(heap) == &a);
    print_test("el maximo ahora es b", (int*)heap_ver_max(heap) == &b);
    print_test("la cantidad de elementos ahora es 1", heap_cantidad(heap) == 1);
    print_test("heap desencolar es igual al elemento que estaba en el maximo", (int*)heap_desencolar(heap) == &b);
    print_test("la cantidad de elementos ahora es 0", heap_cantidad(heap) == 0);
    print_test("el heap ahora esta vacio", heap_esta_vacio(heap));
    heap_destruir(heap, NULL);
}

static void prueba_heapsort(){
    printf("COMIENZO PRUEBAS HEAPSORT\n");

    int elem = 1;
    int elem2 = 2;
    int elem3 = 3;
    int elem4 = 4;
    int elem5 = 5;
    int elem6 = 6;
    int elem7 = 30;
    int elem8 = 50;
    int elem9 = 15;
    int elem10 = 32;

    void* ordenado[] = {&elem, &elem2, &elem3, &elem4, &elem5, &elem6, &elem7};
    void* inverso[] = {&elem8, &elem10, &elem7, &elem6, &elem5, &elem4};
    void * desordenado[] = {&elem6, &elem10, &elem8, &elem2, &elem,&elem9, &elem3, &elem7};
    void* desordenado_2[] = {&elem7, &elem10, &elem9, &elem3};
    void* desordenado_3[] = {&elem10, &elem8, &elem9, &elem3, &elem, &elem4, &elem6};
    heap_sort(ordenado, 7, comparar_int);
    heap_sort(inverso, 6, comparar_int);
    heap_sort(desordenado, 8, comparar_int);
    heap_sort(desordenado_2, 4, comparar_int);
    heap_sort(desordenado_3, 7, comparar_int);
    /*se le aplica heapsort a cada uno de los arreglos*/
    print_test("el arreglo ordenado esta ordenado", esta_ordenado(ordenado, 7));
    print_test("el arreglo inverso ahora esta ordenado", esta_ordenado(inverso, 6));
    print_test("el arreglo desordenado ahora esta ordenado", esta_ordenado(desordenado, 8));
    print_test("el segundo arreglo desordenado ahora esta ordenado", esta_ordenado(desordenado_2, 4));
    print_test("el tercer arreglo desordenado ahora esta ordenado", esta_ordenado(desordenado_3, 7));
}

static void prueba_heap_volumen(){
    printf("COMIENZO PRUEBAS VOLUMEN\n");
    heap_t* heap = heap_crear(comparar_int);
    bool ok = true;
    int arr[3000];
    size_t i;
    for(i = 0; i < 3000; i++){
        arr[i] = (int)i;
        ok += heap_encolar(heap, &arr[i]);
        ok += heap_cantidad(heap) == (i + 1);
        ok += *(int*)heap_ver_max(heap) == i;
    }
    print_test("se encolaron 3000 elementos y se mantuvo el invariante", ok);
    for(i = 2999; i > 0; i--){
        ok += (int*)heap_desencolar(heap) == &arr[i];
        ok += heap_ver_max(heap) == &arr[i-1];
        ok += heap_cantidad(heap) == i;
    }
    print_test("se desencolaron 2999 elementos y se mantuvo el invariante", ok);
    ok += (int*)heap_desencolar(heap) == &arr[0];
    print_test("el heap esta vacio", heap_esta_vacio(heap));
    heap_destruir(heap, NULL);
}

void pruebas_heap_estudiante()
{
    prueba_crear_heap_vacio();
    prueba_heap_encolar();
    prueba_heap_desencolar();
    prueba_heapsort();
    prueba_heap_volumen();
}

#ifndef CORRECTOR
int main(void){
    pruebas_heap_estudiante();
}
#endif
