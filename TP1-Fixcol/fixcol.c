#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

int fixcol(FILE* archivo, int caracteres){
    char cadena[caracteres];
    for (int j = 0; j < caracteres; j++){
        cadena[j] = '\0';
    }
    while ((fgets(cadena, caracteres, archivo)) != NULL){
        if (cadena[0] == '\n'){
            continue;
        }
        fprintf(stdout, "%s", cadena);
        bool insertar_salto_linea = true;
        for (int i = 1; i < caracteres; i++){
            if (cadena[i] == '\n'){
                insertar_salto_linea = false;
                break;
            }
        }
        if (insertar_salto_linea){
            fprintf(stdout, "\n");
        }
    }
    return 0;
}

int main (int argc, char* argv[]){
    if (argc < 2 || argc > 3 || isalpha(*argv[1]) || *argv[1] == '0'){
        fprintf(stderr, "Error: Cantidad erronea de parametros\n");
        return -1;
    }
    FILE* archivo;
    if (argc < 3){
        archivo = stdin;
    } else {
        archivo = fopen(argv[2], "r");
    }
    if (!archivo){
        fprintf(stderr, "Error: archivo fuente inaccesible\n");
        return -1;
    }
    fixcol(archivo, atoi(argv[1])+1);
    fclose(archivo);
    return 0;
}
