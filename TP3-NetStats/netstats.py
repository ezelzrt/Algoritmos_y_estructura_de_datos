#!/usr/bin/python3
import sys
from netstats_aux import *
sys.setrecursionlimit(30000)
inFile = sys.argv[1]

def main():
    grafo = archivo_a_grafo(inFile)
    uf = UnionFind(grafo.obtener_vertices())
    cfcs = {}
    resultado_diametro = ()
    for linea in sys.stdin:
        linea = linea.rstrip('\n').split(" ")
        operacion = linea[0]
        if operacion == "": break

        if operacion == "listar_operaciones":
            listar_operaciones()

        if operacion == "camino":
            linea = formato_linea_con_coma(linea)
            lista = camino_mas_corto(grafo, linea[0], linea[1])
            if not lista:
                print("No se encontro recorrido")
            if lista:
                formato_imprimir(lista)
                print(f"Costo: {len(lista) - 1}")

        if operacion == "conectados":
            linea = formato_linea_sin_coma(linea)
            lista = devolver_cfc(grafo, cfcs, uf, linea)
            imprimir_lista(lista)
        
        if operacion == "ciclo":
            linea = formato_linea_con_coma(linea)
            lista = ciclo_n(grafo, linea[0], int(linea[1]))
            if lista:
                formato_imprimir(lista)
            else:
                print("No se encontro recorrido")

        if operacion == "rango":
            linea = formato_linea_con_coma(linea)
            print(rango(grafo, linea[0], int(linea[1])))

        if operacion == "navegacion":
            linea = formato_linea_sin_coma(linea)
            lista = primer_link(grafo, linea)
            formato_imprimir(lista)
              
        if operacion == "clustering":
            linea = formato_linea_sin_coma(linea)
            valor = clustering(grafo) if not linea else clustering(grafo, linea)
            print(valor)
        
        if operacion == "diametro":
            if not resultado_diametro:
                resultado_diametro = diametro(grafo)
            formato_imprimir(resultado_diametro[1])
            print(f"Costo: {resultado_diametro[0]}")   
        
        if operacion == "comunidad":
            linea = formato_linea_sin_coma(linea)
            lista = comunidades(grafo, linea)
            imprimir_lista(lista)
main()