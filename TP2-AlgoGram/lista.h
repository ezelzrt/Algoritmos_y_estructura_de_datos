#ifndef LISTA_H
#define LISTA_H

#include <stdbool.h>
#include <stdlib.h>
/* ******************************************************************
 *                DEFINICION DE LOS TIPOS DE DATOS
 * *****************************************************************/


typedef struct lista lista_t;
typedef struct lista_iter lista_iter_t;

// Crea una lista.
// Post: devuelve una nueva lista vacía.
lista_t *lista_crear(void);

// Destruye la lista. Si se recibe la función destruir_dato por parámetro,
// para cada uno de los elementos de la lista llama a destruir_dato.
// Pre: la lista fue creada. destruir_dato es una función capaz de destruir
// los datos de la lista, o NULL en caso de que no se la utilice.
// Post: se eliminaron todos los elementos de la lista.
void lista_destruir(lista_t *lista, void (*destruir_dato)(void *));

// Devuelve verdadero si la lista no tiene elementos, false en caso contrario.
// Pre: la lista fue creada.
bool lista_esta_vacia(const lista_t *lista);

// Agrega un nuevo elemento a la lista. Devuelve falso en caso de error.
// Pre: la lista fue creada.
// Post: se agregó un nuevo elemento a la lista, dato se encuentra al inicio
// de la lista.
bool lista_insertar_primero(lista_t *lista, void *dato);

// Agrega un nuevo elemento a la lista. Devuelve falso en caso de error.
// Pre: la lista fue creada.
// Post: se agregó un nuevo elemento a la lista, dato se encuentra al final
// de la lista.
bool lista_insertar_ultimo(lista_t *lista, void *dato);

// Saca el primer elemento de la lista. Si la lista tiene elementos, se quita el
// primero de la lista, y se devuelve ese valor. Si la lista está vacía, devuelve
// NULL.
// Pre: la lista fue creada.
// Post: si la lista no estaba vacía, se devuelve el valor del primer elemento
// y la lista contiene un elemento menos.
void *lista_borrar_primero(lista_t *lista);

// Obtiene el valor del primer elemento de la lista. Si la lista tiene
// elementos, se devuelve el valor del primero, si está vacía devuelve NULL.
// Pre: la lista fue creada.
// Post: se devolvió el primer elemento de la lista, cuando no está vacía.
void *lista_ver_primero(const lista_t *lista);

// Obtiene el valor del ultimo elemento de la lista. Si la lista tiene
// elementos, se devuelve el valor del ultimo, si está vacía devuelve NULL.
// Pre: la lista fue creada.
// Post: se devolvió el ultimo elemento de la lista, cuando no está vacía.
void *lista_ver_ultimo(const lista_t* lista);

// Obtiene el valor del largo de la lista.
// Pre: la lista fue creada.
// Post: se devolvió el largo de la lista.
size_t lista_largo(const lista_t *lista);

// Recorre toda la lista. Si se recibe la funcion visitar por parametro, 
// para cada uno de los elementos de la lista llama a visitar.
// Pre: la lista fue creada. visitar es una función capaz de recibir
// los elementos de la lista, o NULL en caso de que no se la utilice.
// Post: se recorrio toda la lista o hasta donde indique visitar.
void lista_iterar(lista_t *lista, bool visitar(void *dato, void *extra), void *extra);


// Crea un iterador externo para una lista.
// Pre: la lista fue creada
// Post: devuelve un iterador externo para una lista.
lista_iter_t *lista_iter_crear(lista_t *lista);

// Avanza el iterador del lista
// Pre: el iterador fue creado
// Post: La posicion actual del iterador cambio a la siguiente
bool lista_iter_avanzar(lista_iter_t *iter);

// Devuelve el elemento actual
// Pre: El iterador fue creado
// Post se devolvió elemento actual al que apunta el iterador
void *lista_iter_ver_actual(const lista_iter_t *iter);

// Devuelve true si el iterador encuentra al final, false sino
// Pre: El iterador fue creado
// Post: Devolvió true si el iterador se encuentra al final, false sino
bool lista_iter_al_final(const lista_iter_t *iter);

// Inserta un dato en la posicion actual en la que se encuentra el iterador
// Pre: El iterador fue creado
// Post: Se insertó el elemento en la posicion actual, y el iterador ahora apunta al nuevo elemento 
bool lista_iter_insertar(lista_iter_t *iter, void *dato);

//Borra el dato que esté en la posicion actual en la que se encuentra el iterador
// Pre: El iterador fue creado
// Post: Se borró el dato que estaba en la posicion actual, y el iterador ahora apunta al siguiente elemento 
void *lista_iter_borrar(lista_iter_t *iter);

// Destruye el iterador
// Pre: el iterador fue creado
// Post: el iterador fue destruido
void lista_iter_destruir(lista_iter_t *iter);
void pruebas_lista_estudiante(void);

#endif