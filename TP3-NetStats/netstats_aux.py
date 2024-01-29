from biblioteca import * 
from union_find import *
import os.path
import sys
import random

def archivo_a_grafo(nombre_archivo):
    grafo = Grafo(True, [])
    # path_archivo = obtener_path_absoluto(nombre_archivo)
    with open(nombre_archivo, encoding="utf8") as entrada:
            for linea in entrada:
                campos = linea.rstrip('\n')
                campos = campos.split('\t')
                grafo.agregar_vertice(campos[0])
                for j in range(1, len(campos)):
                     grafo.agregar_vertice(campos[j])
                     grafo.agregar_arista(campos[0], campos[j])
    return grafo
            
def listar_operaciones():
    operaciones = ["camino", "conectados", "ciclo", "diametro", "rango", "navegacion", "clustering", "comunidad"]
    for operacion in operaciones:
       print(operacion)
    
def devolver_cfc(grafo, cfcs, uf, linea):
    lista = []
    for clave in cfcs:
        if uf.find(clave) == uf.find(linea):
            lista = cfcs[clave]
    if not lista:
        lista = componentes_fuertemente_conexas(grafo, linea)
        cfcs[linea] = lista
        for elemento in lista:
            uf.union(linea, elemento)
    return lista

def imprimir_lista(lista):
    for i in range(len(lista)):
        if i != len(lista) - 1:
            print(f"{lista[i]}, ",end='')
        else:
            print(lista[i])

def formato_linea_con_coma(linea):
    linea = linea[1:]
    linea = " ".join(linea)
    linea = linea.split(",")
    return linea

def formato_linea_sin_coma(linea):
    linea = linea[1:]
    linea =  " ".join(linea)
    return linea
        
def formato_imprimir(lista):
    for i in range(len(lista)):
        if i != len(lista) - 1:
            print(f"{lista[i]} -> ", end="")
        else:
            print(lista[i])

def obtener_path_absoluto(archivo):
    '''
    Obtiene el path absoluto del archivo pasado por parametro
    '''
    BASE_DIR = os.path.dirname(os.path.abspath(__file__))
    path = os.path.join(BASE_DIR, archivo)

    return path
