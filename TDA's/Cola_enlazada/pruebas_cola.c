#include "cola.h"
#include "testing.h"

#include "nodo.h"
#include "pila.h"

#include <stdlib.h>
#include <stdio.h>

static void pruebas_cola_vacia(void){
    printf("\n> COMIENZO PRUEBAS COLA VACIA <\n");
    
    cola_t* cola = cola_crear();
    print_test("La cola recien creada esta vacía", cola_esta_vacia(cola));
    print_test("Ver primero da NULL", cola_ver_primero(cola) == NULL);
    print_test("Desencolar da NULL", cola_desencolar(cola) == NULL);

    cola_destruir(cola, NULL);
}

static void pruebas_invariante_cola(void){
    printf("\n> COMIENZO PRUEBAS INVARIANTE DE COLA <\n");

    cola_t* cola = cola_crear();
    int n1 = 1;
    int n2 = 2;
    int n3 = 3;
    print_test("Encolo elemento1", cola_encolar(cola, &n1));
    print_test("Veo que el elemento1 sea el primero", cola_ver_primero(cola) == &n1);
    print_test("Encolo elemento2", cola_encolar(cola, &n2));
    print_test("Encolo elemento3", cola_encolar(cola, &n3));
    print_test("Veo que el elemento1 siga siendo el primero", cola_ver_primero(cola) == &n1);
    print_test("Desencolo y es elemento1", cola_desencolar(cola) == &n1);
    print_test("Desencolo y es elemento2", cola_desencolar(cola) == &n2);
    print_test("Veo que el elemento3 sea el primero", cola_ver_primero(cola) == &n3);
    print_test("Desencolo y es elemento3", cola_desencolar(cola) == &n3);
    print_test("La cola esta vacia", cola_esta_vacia(cola));
    print_test("Desencolar da NULL", cola_desencolar(cola) == NULL);
    print_test("Ver primero da NULL", cola_ver_primero(cola) == NULL);

    cola_destruir(cola, NULL);
}

static void pruebas_volumen(void){
    printf("\n> INICIO PRUEBAS DE VOLUMEN <\n");

    cola_t* cola = cola_crear();

    int lista[1000];

    bool ok = true;
    bool ver_primero_ok = true;
    int i;
    for (i = 0; i < 1000; i++){

        if (!cola_encolar(cola, &lista[i])){
            ok = false;
        }
        if (cola_ver_primero(cola) != &lista[0]){
            ver_primero_ok = false;
        }
    }
    print_test("Encolo 1000 elementos", ok);
    print_test("Veo que el primero sea siempre el primer elemento encolado", ver_primero_ok);

    ok = true;
    ver_primero_ok = true;
    i = 0;
    while (!cola_esta_vacia(cola)){
        if (cola_ver_primero(cola) != &lista[i]){
            ver_primero_ok = false;
        }
        if (cola_desencolar(cola) != &lista[i]){
            ok = false;
        }
        i++;
    }
    print_test("Desencolo los 1000 elementos", ok);
    print_test("A medida que desencolo, veo que el primero sea el correcto", ver_primero_ok);
    print_test("La cola esta vacia", cola_esta_vacia(cola));

    cola_destruir(cola, NULL);
}

static void pruebas_elemento_null(void){
    printf("\n> INICIO PRUEBAS CON ELEMENTO NULL <\n");

    cola_t *cola = cola_crear();

    void *n0 = NULL;
    void *n1 = NULL;
    print_test("Encolar NULL es valido", cola_encolar(cola, n0));
    print_test("Encolo otro NULL", cola_encolar(cola, n1));
    print_test("La cola no esta vacia", !cola_esta_vacia(cola));
    print_test("Veo que el primero sea el primer NULL encolado", cola_ver_primero(cola) == n1);
    print_test("Desencolar da NULL", cola_desencolar(cola) == NULL);
    print_test("La cola sigue sin estar vacia", !cola_esta_vacia(cola));

    cola_destruir(cola, NULL);
}

static void pruebas_destruccion_nodos(void){
    printf("\n> INICIO PRUEBAS DE DESTRUCCION CON NODOS <\n");

    cola_t *cola = cola_crear();

    int n1 = 1;
    int n2 = 2;
    nodo_t *nodo1 = nodo_crear(&n1);
    nodo_t *nodo2 = nodo_crear(&n2);
    print_test("Encolo un nodo", cola_encolar(cola, nodo1));
    print_test("Encolo otro nodo", cola_encolar(cola, nodo2));
    print_test("Veo que el primero sea el primer nodo encolado", cola_ver_primero(cola) == nodo1);

    cola_destruir(cola, free);
}

void pila_destruir_wrapper(void *valor){
    pila_destruir(valor);
}

static void pruebas_destruccion_pilas(void){
    printf("\n> INICIO PRUEBAS DE DESTRUCCION CON PILAS <\n");

    cola_t *cola = cola_crear();
    int n1 = 1;
    int n2 = 2;
    int n3 = 3;
    
    pila_t *pila1 = pila_crear();
    pila_apilar(pila1, &n1);
    pila_apilar(pila1, &n2);

    pila_t *pila2 = pila_crear();
    pila_apilar(pila2, &n3);

    print_test("Encolo una pila con datos apilados", cola_encolar(cola, pila1));
    print_test("Encolo otra pila con datos apilados", cola_encolar(cola, pila2));
    print_test("La cola no esta vacia", !cola_esta_vacia(cola));

    cola_destruir(cola, pila_destruir_wrapper);
}


void pruebas_cola_estudiante(void){
    pruebas_cola_vacia();
    pruebas_invariante_cola();
    pruebas_volumen();
    pruebas_elemento_null();
    pruebas_destruccion_nodos();
    pruebas_destruccion_pilas();
}


/*
 * Función main() que llama a la función de pruebas.
 */

#ifndef CORRECTOR  // Para que no dé conflicto con el main() del corrector.

int main(void) {
    pruebas_cola_estudiante();
    return failure_count() > 0;  // Indica si falló alguna prueba.
}

#endif
