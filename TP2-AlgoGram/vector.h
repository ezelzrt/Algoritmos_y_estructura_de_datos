#include <stdbool.h>

typedef struct vector vector_t;
typedef void (*destruir_dato_t)(void*);

/* Crea un vector dinamico
 * Post: devuelve un vector vacio
 */
vector_t* vector_crear();

// Almacena el dato en la ultima posición 
// Pre: el vector fue creado
// Post: se almacenó el valor en la ultima posición.
// Devuelve false si no pudo guardar el dato, true si
// se guardó el dato con éxito.
bool vector_guardar(vector_t* vector, void* dato);

// Devuelve la cantidad
// Pre: el vector fue creado
size_t vector_cantidad(vector_t* vector);

// Devuelve el dato que se encuentra en pos
// Pre: el vector fue creado
// Post: se devolvio el dato en la posición pos. Devuelve NULL si la
// posición es inválida.
void* vector_obtener(vector_t* vector, size_t pos);

// Borra el dato que se encuentra en pos
// Pre: el vector fue creado
// Post: se devolvio el dato borrado, devulve NULL si la posicion
// es invalida.
void* vector_borrar(vector_t* vector, size_t pos);

// Devuelve el tamaño del vector
// Pre: el vector fue creado
// Post: se devolvio el tamaño del vector
size_t vector_tam(vector_t* vector);

// Elimina el vector, llamando a la función dada para cada elemento del mismo.
// El puntero a la función puede ser NULL, en cuyo caso no se llamará.
// Post: se llamó a la función indicada con cada elemento del vector. El vector
// dejó de ser válido.
void vector_destruir(vector_t* vector, destruir_dato_t destruir);