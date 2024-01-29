from cola import *
class Grafo:
    
    def __init__(self, es_dirigido=False, lista_vertices=[]):
        self.vertices = {}
        #if lista_vertices:
        for vertice in lista_vertices:
            self.vertices[vertice] = self.vertices.get(vertice, {})
        self.es_dirigido = es_dirigido
    
    def agregar_vertice(self, v):
        if not v in self.vertices:
            self.vertices[v] = {}
    
    def obtener_vertices(self):
        resultado = []
        for v in self.vertices:
            resultado.append(v)
        return resultado
    
    def agregar_arista(self, v, w, peso=1):
        # if not w in self.vertices[v]:
        #     self.vertices[v][w] = peso
        #     if not self.es_dirigido:
        #         self.vertices[w][v] = peso 
        self.vertices[v][w] = peso
        if not self.es_dirigido:
            self.vertices[w][v] = peso 
    
    def borrar_arista(self, v, w):
        if w in self.vertices[v]:
            self.vertices[v].pop(w)
            if not self.es_dirigido:
                self.vertices[w].pop(v)
    
    def borrar_vertice(self, v):
        for w in self.vertices:
            if v in self.vertices[w]:
                self.vertices[w].pop(v)
    
    def estan_unidos(self, v, w): 
        return w in self.vertices[v]

    def peso_arista(self, v, w):
        return self.vertices[v][w]
    
    def adyacentes(self, v):
        resultado = []
        for w in self.vertices[v]:
            resultado.append(w)
        return resultado

    def __len__(self):
        return len(self.obtener_vertices())

