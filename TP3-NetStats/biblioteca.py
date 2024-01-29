from grafo import *
from cola import *
from pila import *
from random import *
from collections import *

def grados_entrada(grafo):
    gr_entrada = {}
    for v in grafo.obtener_vertices():
        gr_entrada[v] = 0
    for v in grafo.obtener_vertices():
        for w in grafo.adyacentes(v):
            gr_entrada[w] += 1
    return gr_entrada

def orden_topologico(grafo):
    cola = Cola()
    resultado = []
    gr_ent = grados_entrada(grafo)
    for v in grafo.obtener_vertices():
        if gr_ent[v] == 0:
            cola.encolar(v)
    while not cola.esta_vacia():
        v = cola.desencolar()
        resultado.append(v)
        for w in grafo.adyacentes(v):
            gr_ent[w] -= 1
            if gr_ent[w] == 0:
                cola.encolar(w)
    return resultado

def bfs(grafo, origen): 
    cola = Cola()
    cola.encolar(origen)
    padres = {}
    visitados = set()
    visitados.add(origen)
    padres[origen] = None
    while not cola.esta_vacia():
        v = cola.desencolar()
        for w in grafo.adyacentes(v):
            if w not in visitados:
                padres[w] = v
                cola.encolar(w)
                visitados.add(w)
    return padres

def bfs_en_rango(grafo, origen, n):
    cola = Cola()
    cola.encolar(origen)
    orden = {}
    visitados = set()
    visitados.add(origen)
    orden[origen] = 0
    cant = 0
    while not cola.esta_vacia():
        v = cola.desencolar()
        if orden[v] == n: cant += 1
        for w in grafo.adyacentes(v):
            if w not in visitados:
                orden[w] = orden[v] + 1
                cola.encolar(w)
                visitados.add(w)
    return cant

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

def rango(grafo, pagina, n):
    return bfs_en_rango(grafo, pagina, n)

def _primer_link(grafo, pagina,lista, contador):
    lista.append(pagina)
    if not grafo.adyacentes(pagina) or contador == 20:
        return
    primero = grafo.adyacentes(pagina)[0]
    _primer_link(grafo, primero, lista, contador + 1)

def primer_link(grafo, pagina):
    lista = []
    contador = 0
    _primer_link(grafo, pagina, lista, contador)
    return lista

def camino_mas_corto(grafo, origen, destino):
    padres = bfs(grafo, origen)
    return reconstruir_camino(padres, origen, destino)

def reconstruir_camino(padres, origen, destino):
    recorrido = []
    actual = destino
    if not destino in padres:
        return recorrido
    while actual != origen:
        recorrido.append(actual)
        actual = padres[actual]
    return recorrido 

def _componentes_fuertemente_conexas(grafo,v, visitados, orden, mb, orden_contador, apilados, pila, todas_cfc):
    visitados.add(v)
    orden[v] = orden_contador[0]
    mb[v] = orden[v]
    apilados.add(v)
    pila.appendleft(v)
    orden_contador[0] += 1    
    for w in grafo.adyacentes(v):
        if w not in visitados:
            _componentes_fuertemente_conexas(grafo, w, visitados, orden, mb, orden_contador, apilados, pila, todas_cfc)    
        if w in apilados:
            mb[v] = min(mb[v], mb[w])
    if orden[v] == mb[v] and len(pila) > 0:
        nueva_cfc = []
        while True:
            w = pila.popleft()
            apilados.remove(w)
            nueva_cfc.append(w)
            if w == v:
                break
        todas_cfc.append(nueva_cfc)
        
def componentes_fuertemente_conexas(grafo, origen):
    visitados = set()
    todas_cfc = []
    orden = {}
    mb = {}
    apilados = set()
    pila = deque()
    contador = [0]    
    _componentes_fuertemente_conexas(grafo,origen, visitados,orden, mb, contador, apilados, pila, todas_cfc)
    return todas_cfc.pop() 

def caminos_minimos(grafo, origen):
    q = Cola()
    visitados = set()
    distancia = {}
    distancia[origen] = 0
    visitados.add(origen)
    q.encolar(origen)
    padres = {}
    padres[origen] = None
    while not q.esta_vacia():
        v = q.desencolar()
        for w in grafo.adyacentes(v):
            if w not in visitados:
                padres[w] = v
                distancia[w] = distancia[v] + 1
                q.encolar(w)
                visitados.add(w)
    return distancia, padres

def reconstruir_camino(padres, inicio, fin):
    actual = fin
    camino = []
    if not actual in padres:
        return camino
    while actual != inicio:
        camino.append(actual)
        actual = padres[actual]
    camino.append(actual)
    camino.reverse()
    return camino

def diametro(grafo):
    max_min_dist = 0
    camino = []
    for v in grafo.obtener_vertices():
        distancias, padres = caminos_minimos(grafo, v)
        
        for w in distancias:
            if distancias[w] > max_min_dist:
                max_min_dist = distancias[w]
                camino = reconstruir_camino(padres, v, w)
    return max_min_dist, camino
    
def clustering_total(grafo):
    suma_clust = 0
    for pagina in grafo.obtener_vertices():
        suma_clust += clustering(grafo, pagina)
    return round(suma_clust / len(grafo), 3)

def clustering(grafo, pagina = None):
    if not pagina:
        return clustering_total(grafo)
    adyacentes = grafo.adyacentes(pagina)
    gr_salida = len(adyacentes) if not pagina in adyacentes else len(adyacentes) - 1 
    if gr_salida < 2:
        return round(0, 3)
    indice = 0
    lista = grafo.adyacentes(pagina)
    if pagina in lista:
        lista.remove(pagina)
    for v in lista:
        for w in lista:
            if v == w:
                continue
            if grafo.estan_unidos(v,w):
                indice += 1
    valor =  round(indice / ((gr_salida - 1) * gr_salida), 3)
    return valor

def max_freq(label, entradas, v):
    frecuencias = {}
    mayor_frecuencia = 0
    mayor_label = label[entradas[0]]
    for x in entradas:
        if x == v:
            continue
        frecuencias[label[x]] = frecuencias.get(label[x], 0) + 1
        if frecuencias[label[x]] > mayor_frecuencia: 
            mayor_label = label[x]
            mayor_frecuencia = frecuencias[label[x]]
        
    return mayor_label

def comunidades(grafo, pagina):
    label = {}
    entradas = {}
    for i, v in enumerate(grafo.obtener_vertices()):
        label[v] = i
        for w in grafo.adyacentes(v):
            lista_entrada = entradas.get(w, [])
            lista_entrada.append(v)
            entradas[w] = lista_entrada
    cantidad_labels = len(grafo)
    convergencia = 0
    i = 0
    lista = grafo.obtener_vertices()
    while i < 50:
        for v in lista:
            label[v] = max_freq(label, entradas[v], v)
        
        cantidad_actual_labels = len(set(label.values()))
        if cantidad_labels != cantidad_actual_labels:
            convergencia = 0
            cantidad_labels = cantidad_actual_labels
        convergencia += 1
        if convergencia == 5:
            break
        i += 1
    
    resultado = []
    for v in grafo.obtener_vertices():
        if label[v] == label[pagina]:
            resultado.append(v)
    return resultado


def ciclo_valido(grafo, pagina, origen, contador, n):
    if (contador < n-1) or (origen in grafo.adyacentes(pagina)):
        return True
    return False

def _ciclo_n(grafo, pagina, origen, padre, contador, n):
    if len(padre) == n:
        padre[origen] = pagina
        return True

    for w in grafo.adyacentes(pagina):
        if w not in padre:
            if not ciclo_valido(grafo, w, origen, contador+1, n):
                continue
            padre[w] = pagina
            if _ciclo_n(grafo, w, origen, padre, contador+1, n):
                return True
            padre.pop(w)
            
    return False

def ciclo_n(grafo, pagina, n):
    padre = {}
    padre[pagina] = None
    resultado = []
    if _ciclo_n(grafo, pagina, pagina, padre, 0, n):
        resultado = reconstruir_camino(padre, pagina, padre[pagina])
        resultado.append(pagina)
    return resultado
