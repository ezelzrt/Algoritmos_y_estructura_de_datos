#include "tp0.h"

/* *****************************************************************
 *                     FUNCIONES A COMPLETAR                       *
 *         (ver en tp0.h la documentación de cada función)         *
 * *****************************************************************/

void swap(int *x, int *y) {
    int aux = *x;
    *x = *y;
    *y = aux;
}


int maximo(int vector[], int n) {
    if (n == 0) {return -1;}
    
    int max_pos = 0;
    int max = vector[0];
    for (int i = 1; i < n; i++){
        if (vector[i] > max){
            max_pos = i;
            max = vector[i];
        }
    }
    return max_pos;
}


int comparar(int vector1[], int n1, int vector2[], int n2) {
    int menor_n = n1 < n2 ? n1 : n2;

    for (int i = 0; i < menor_n; i++){
        if (vector1[i] < vector2[i]){ return -1;}
        if (vector1[i] > vector2[i]){ return 1;}
    }
    if (n1 == n2){ return 0;}
    if (menor_n == n1){ return -1;}
    return 1;
}


void seleccion(int vector[], int n) {
    for (int i = n; i > 0; i--){
        int pos_max = maximo(vector, i);
        swap(&(vector[pos_max]), &(vector[i-1]));
    }
}
