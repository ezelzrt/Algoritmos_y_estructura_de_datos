#include "pila.h"
#include "testing.h"

#include <stdbool.h>
#include <stdio.h>

static void prueba_pila_vacia(void) {
    printf("\n> INICIO PRUEBAS DE PILA VACIA <\n");

    pila_t *pila = pila_crear();
    print_test("Pila recien creeada esta vacia", pila_esta_vacia(pila));
    print_test("Veo el tope de pila vacia me da NULL", pila_ver_tope(pila) == NULL);
    print_test("Desapilar de pila vacia me da NULL", pila_desapilar(pila) == NULL);

    pila_destruir(pila);
}

static void pruebas_apilar_desapilar(void){
    printf("\n> INICIO PRUEBAS APILAR Y DESAPILAR ELEMENTOS <\n");

    pila_t *pila = pila_crear();
    int n0 = 0;
    int *p0 = &n0;
    int n1 = 1;
    int *p1 = &n1;
    print_test("Apilo un elemento", pila_apilar(pila, p0));
    print_test("Veo que el elemento que apile sea el tope", pila_ver_tope(pila) == p0);
    print_test("Apilo otro elemto", pila_apilar(pila, p1));
    print_test("Veo que el ultimo elemento que apile sea el tope", pila_ver_tope(pila) == p1);
    print_test("Desapilo un elemento", pila_desapilar(pila));
    print_test("Verifico que el tope siga siendo el primer elemento", pila_ver_tope(pila) == p0);

    pila_destruir(pila);
}

static void pruebas_volumen(void){
    printf("\n> INICIO PRUEBAS DE VOLUMEN <\n");

    pila_t *pila = pila_crear();

    int lista[1000];

    bool ok = true;
    bool ver_tope_ok = true;
    int i;
    for (i = 0; i < 1000; i++){

        if (!(pila_apilar(pila, &lista[i]))){
            ok = false;
        }
        if (pila_ver_tope(pila) != &lista[i]){
            ver_tope_ok = false;
        }
    }
    print_test("Apilo 1000 elementos", ok);
    print_test("Veo que el tope sea siempre el ultimo elemento apilado", ver_tope_ok);

    ok = true;
    ver_tope_ok = true;
    while (!pila_esta_vacia(pila)){
        i--;
        if (pila_ver_tope(pila) != &lista[i]){
            ver_tope_ok = false;
        }
        if (pila_desapilar(pila) != &lista[i]){
            ok = false;
        }
    }

    print_test("Desapilo los 1000 elementos", ok);
    print_test("A medida que desapilo, veo que el tope sea el correcto", ver_tope_ok);
    print_test("La pila esta vacia", pila_esta_vacia(pila));

    pila_destruir(pila);
}

static void pruebas_invariante_de_pila(void){
    printf("\n> INICIO PRUEBAS INVARIANTE DE PILA <\n");

    pila_t *pila = pila_crear();
    
    int n1 = 1;
    int n2 = 2;
    print_test("Apilo elemento1", pila_apilar(pila, &n1));
    print_test("Apilo elemento2", pila_apilar(pila, &n2));
    print_test("Desapilo y es elemento2", pila_desapilar(pila) == &n2);
    print_test("Desapilo y es elemento1", pila_desapilar(pila) == &n1);
    print_test("Pila esta vacia", pila_esta_vacia(pila));
    print_test("Desapilar da NULL", pila_desapilar(pila) == NULL);
    print_test("Ver tope da NULL", pila_ver_tope(pila) == NULL);

    pila_destruir(pila);
}

static void pruebas_elemento_null(void){
    printf("\n> INICIO PRUEBAS CON ELEMENTO NULL <\n");

    pila_t *pila = pila_crear();

    void *n0 = NULL;
    void *n1 = NULL;
    print_test("Apilar NULL es valido", pila_apilar(pila, n0));
    print_test("Apilo otro NULL", pila_apilar(pila, n1));
    print_test("La pila no esta vacia", !pila_esta_vacia(pila));
    print_test("Veo que el tope sea NULL", pila_ver_tope(pila) == n1);
    print_test("Desapilar da NULL", pila_desapilar(pila) == NULL);
    print_test("La pila sigue sin estar vacia", !pila_esta_vacia(pila));

    pila_destruir(pila);
}

void pruebas_pila_estudiante() {
    prueba_pila_vacia();
    pruebas_apilar_desapilar();
    pruebas_volumen();
    pruebas_invariante_de_pila();
    pruebas_elemento_null();
}

/*
 * Función main() que llama a la función de pruebas.
 */

#ifndef CORRECTOR  // Para que no dé conflicto con el main() del corrector.

int main(void) {
    pruebas_pila_estudiante();
    return failure_count() > 0;  // Indica si falló alguna prueba.
}

#endif
