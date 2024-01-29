#include "lista.h"
#include "testing.h"
#include <stdio.h>
#include <stdlib.h>

#include "pila.h"

typedef struct suma_corte{
    int cant;
    int suma;
}suma_corte_t;

bool sumar_primeros_5(void* dato, void* extra){
    suma_corte_t *suma_cor = (suma_corte_t*)extra;
    suma_cor->cant++;
    suma_cor->suma += *((int*)dato);   
    return suma_cor->cant < 5;
}

bool n2_en_lista(void* elemento, void* extra){
    if ((*(int*)elemento) == 2){
        *(bool*)extra = true;
        return false;
    }
        return true;
}

bool sumar_todos(void* dato, void* extra){
    *((int*)extra) += *((int*)dato);
    return true;
}

/*Pruebas para una lista recien creada*/
static void pruebas_lista_vacia(void) {
    printf("INICIO DE PRUEBAS DE LISTA SIN ELEMENTOS\n");
    // se crea una lista sin elementos
    lista_t *lista = lista_crear();

    
    print_test("la lista está vacía", lista_esta_vacia(lista));
    
    // largo de una lista vacía es 0
    print_test("lista vacia tiene largo 0", lista_largo(lista) == 0);

    // ver_primero en una lista vacía devuelve NULL
    print_test("Ver primero de una lista vacia es invaĺido", lista_ver_primero(lista) == NULL);

    // ver ultimo de una lista vacia devuelve NULL
    print_test("Ver ultimo de una lista vacia es invaĺido", lista_ver_ultimo(lista) == NULL);


   lista_destruir(lista, NULL);
}

static void pruebas_con_null(void){
    printf("INICIO DE PRUEBAS DE LISTA CON NULL\n");

    lista_t* lista = lista_crear();

    void* elem = NULL;
    void* elem2 = NULL;

    print_test("se agregó NULL", lista_insertar_primero(lista, elem));
    print_test("la lista no esta vacia", !lista_esta_vacia(lista));
    print_test("agregó otro NULL", lista_insertar_primero(lista, elem2));
    print_test("el largo de la lista es 2", lista_largo(lista) == 2);
    print_test("se borró un elemento y es NULL", lista_borrar_primero(lista) == elem);
    print_test("la lista no esta vacia", !lista_esta_vacia(lista));
    print_test("borro otro elemento", lista_borrar_primero(lista) == elem);
    print_test("la lista esta vacia", lista_esta_vacia(lista));

    lista_destruir(lista, NULL);
}

static void pruebas_algunos_elementos(void){
    printf("INICIO DE PRUEBAS DE LISTA CON POCOS ELEMENTOS\n");
    // se crea una lista sin elementos
    lista_t *lista = lista_crear();

    int elem = 1;
    int elem2 = 2;
    int elem3 = 3;

    // insertamos el primer elemento al principio
    print_test("se insertó el primer elemento",lista_insertar_primero(lista, (void*)&elem));
    print_test("el largo de la lista es 1", lista_largo(lista) == 1);
    print_test("el primero también es el ultimo de la lista", *((int*)lista_ver_ultimo(lista)) == elem);
    print_test("el primer elemento de la lista es el que insertamos", *((int*)lista_ver_primero(lista)) == elem);

    // insertamos el segundo elemento al final
    print_test("Se insertó el segundo elemento al final", lista_insertar_ultimo(lista, (void*)&elem2));
    print_test("el largo de la lista es 2", lista_largo(lista) == 2);
    print_test("el elemento que insertamos es el ultimo",*((int*)lista_ver_ultimo(lista)) == elem2);

    // insertamos el ultimo elemento al principio
    print_test("Se insertó el tercer elemento al principio", lista_insertar_primero(lista, (void*)&elem3));
    print_test("el largo de la lista es 3", lista_largo(lista) == 3);
    print_test("el elemento que insertamos es el primero", *((int*)lista_ver_primero(lista)) == elem3);

    // Borramos elementos al principio
    print_test("Se borró al primer elemento de la lista", *((int *)lista_borrar_primero(lista)) == elem3);
    print_test("el largo de la lista es 3", lista_largo(lista) == 2);
    print_test("el primero de la lista es el que corresponde ", *((int *)lista_ver_primero(lista)) == elem);
    print_test("Se borró al primer elemento de la lista", *((int *)lista_borrar_primero(lista)) == elem);
    print_test("el largo de la lista es 3", lista_largo(lista) == 1);
    print_test("el primero de la lista es el que corresponde ", *((int *)lista_ver_primero(lista)) == elem2);

    lista_destruir(lista, NULL);
}

static void pruebas_volumen(void){
    printf("INICIO DE PRUEBAS DE LISTA CON VOLUMEN\n");
    // se crea lista sin elementos
    lista_t *lista = lista_crear();

    int arr[4000];
    bool ok = true;
    for(int i = 0; i < 2000; i++){
        arr[i] = i;
        ok&= lista_insertar_primero(lista, &arr[i]);
        ok&= *((int*)lista_ver_primero(lista)) == arr[i];
        ok&= lista_largo(lista) == i+1;
    }
    print_test("se insertaron 2000 elementos al principio y se manntuvo el invariante", ok);

    for(int i = 2000; i < 4000; i++){
        arr[i] = i;
        ok&= lista_insertar_ultimo(lista, &arr[i]);
        ok&= *((int*)lista_ver_ultimo(lista)) == arr[i];
        ok&= lista_largo(lista) == i+1;
    }
    print_test("se insertaron 2000 elementos al final y se manntuvo el invariante", ok);
    lista_destruir(lista, NULL);

}

static void pruebas_destruir_con_free(void){
    printf("INICIO DE PRUEBAS DE LISTA CON FREE\n");
    // se crea lista sin elementos
    lista_t *lista = lista_crear();
    bool ok = true;
    for(int i = 0; i < 500; i++){
        int *p = malloc(sizeof(int));
        *p = i;
        ok&= lista_insertar_primero(lista, p);
        ok&= *((int*)lista_ver_primero(lista)) == *p;
    }
    print_test("se insertaron 500 elementos al principio y se mantuvo el invariante", ok);

    lista_destruir(lista, free);
}


void pila_destruir_wrapper(void *valor){
    pila_destruir(valor);
}

static void pruebas_destruccion_pilas(void){
    printf("INICIO PRUEBAS DE DESTRUCCION CON PILAS\n");

    lista_t *lista = lista_crear();
    int n1 = 1;
    int n2 = 2;
    int n3 = 3;
    
    pila_t *pila1 = pila_crear();
    pila_apilar(pila1, &n1);
    pila_apilar(pila1, &n2);

    pila_t *pila2 = pila_crear();
    pila_apilar(pila2, &n3);

    print_test("Inserto al final una pila con datos apilados", lista_insertar_ultimo(lista, pila1));
    print_test("Inserto al final otra pila con datos apilados", lista_insertar_ultimo(lista, pila2));
    print_test("La lista no esta vacia", !lista_esta_vacia(lista));

    lista_destruir(lista, pila_destruir_wrapper);
}

static void pruebas_iter_interno_sin_corte(void){
    printf("INICIO DE PRUEBAS DE ITERADOR INTERNO SIN CORTE\n");
    // se crea lista sin elementos
    lista_t *lista = lista_crear();
    int arr[100];
    bool ok = true;
    int suma_100 = 0;
    int suma = 0;
    for(int i = 0; i< 100; i++){
        arr[i] = i;
        ok&= lista_insertar_primero(lista, &arr[i]);
        suma_100 += i;
    }
    print_test("se insertaron 100 elementos en la lista", ok);    
    lista_iterar(lista, sumar_todos, &suma);
    print_test("despues de iterar la lista el valor de suma es es igual al valor de suma_100", suma == suma_100);
    lista_destruir(lista, NULL);
}

static void pruebas_iter_interno_con_corte(void){
    printf("INICIO DE PRUEBAS DE ITERADOR INTERNO SIN CORTE\n");
    // se crea lista sin elementos
    lista_t *lista = lista_crear();
    bool ok = true;
   
    suma_corte_t *suma_cort = malloc(sizeof(suma_corte_t));
    print_test("suma_cort se creó correctamente", suma_cort);
    suma_cort->cant = 0;
    suma_cort->suma = 0;
    int arr[] = {1,2,3,4,5,6,7,8,9,10};
    for(int i = 0; i < 10; i++){
        ok&= lista_insertar_ultimo(lista, &arr[i]);
    }
    print_test("se insertaron 10 elementos", ok);

    lista_iterar(lista, sumar_primeros_5, (void*)suma_cort);
    print_test("la suma de los primeros 5 elementos de la lista es 15", suma_cort->suma == 15);
    lista_destruir(lista, NULL);
    free(suma_cort);
}


static void pruebas_iter_externo(){
    printf("INICIO DE PRUEBAS ITERADOR EXTERNO\n");


    lista_t* lista = lista_crear();
    lista_iter_t* iter = lista_iter_crear(lista);
    
    print_test("Ver actual con el iterador en lista vacia da NULL", !lista_iter_ver_actual(iter));
    print_test("Avanzar el iterador en lista vacia es invalido", !lista_iter_avanzar(iter));
    print_test("Borrar con el iterador en lista vacia es invalido", lista_iter_borrar(iter) == NULL);
    print_test("Iterador recien crado en lista vacia esta al final", lista_iter_al_final(iter));
    
    int n0 = 0;
    int n1 = 1;
    int n2 = 2;
    int n3 = 3;
    int n4 = 4;
    print_test("Inserto elemento con el iterador", lista_iter_insertar(iter, &n1));
    print_test("Insertar un elemento en la posicion en la que se crea el iterador esta al principio", lista_ver_primero(lista) == &n1);
    print_test("Ver actual del iterador es el elemento recien agregado", lista_iter_ver_actual(iter) == &n1);
    print_test("Avanzo el iterador", lista_iter_avanzar(iter));
    print_test("Inserto otro elemento con el iterador", lista_iter_insertar(iter, &n0));
    print_test("Ver actual del iterador es el elemento recien agregado", lista_iter_ver_actual(iter) == &n0);
    print_test("El ultimo de la lista es el elemento recien agregado", lista_ver_ultimo(lista) == &n0);
    print_test("Borro con el iterador y es elemento que corresponde", lista_iter_borrar(iter) == &n0);
    print_test("El iterador esta al final", lista_iter_al_final(iter));
    print_test("El ultimo de la lista es el que corresponde", lista_ver_ultimo(lista) == &n1);
    print_test("Inserto elemento con el iterador", lista_iter_insertar(iter, &n4));
    print_test("Inserto elemento con el iterador", lista_iter_insertar(iter, &n3));
    print_test("Inserto elemento con el iterador", lista_iter_insertar(iter, &n2));
    print_test("El iterador no esta al final", !lista_iter_al_final(iter));
    print_test("Ver actual del iterador es el elemento recien agregado", lista_iter_ver_actual(iter) == &n2);
    print_test("El ultimo de la lista es el que corresponde", lista_ver_ultimo(lista) == &n4);
    print_test("Borro con el iterador", lista_iter_borrar(iter) == &n2);
    print_test("Ver actual del iterador es el elemento que corresponde", lista_iter_ver_actual(iter) == &n3);
    print_test("Avanzo el iterador",lista_iter_avanzar(iter));
    print_test("Ver actual del iterador es el elemento que corresponde", lista_iter_ver_actual(iter) == &n4);
    
    bool esta_en_lista = false; 
    lista_iterar(lista, n2_en_lista, (void*)esta_en_lista);    
    print_test("El elemento del medio borrado con el iterador no esta", !esta_en_lista);

    lista_iter_destruir(iter);
    lista_destruir(lista, NULL);
}

void pruebas_lista_estudiante(){
    pruebas_lista_vacia();
    pruebas_con_null();
    pruebas_algunos_elementos();
    pruebas_volumen();
    pruebas_destruir_con_free();
    pruebas_destruccion_pilas();
    pruebas_iter_interno_sin_corte();
    pruebas_iter_interno_con_corte();
    pruebas_iter_externo();
}

#ifndef CORRECTOR
int main(void){
    pruebas_lista_estudiante();
    return failure_count() > 0;
}
#endif
