class _Nodo:

    def __init__(self, dato):
        self.dato = dato
        self.prox = None

class Pila:

    def __init__(self):
        self.tope = None

    def apilar(self, dato):
        nodo = _Nodo(dato)
        nodo.prox = self.tope
        self.tope = nodo

    
    def desapilar(self):
        """ pre: la pila no está vacía """ 
        dato = self.tope.dato
        self.tope = self.tope.prox
        return dato

    def ver_tope(self):
        return self.tope.dato

    def esta_vacia(self):
        '''
        Devuelve True o False según si la pila está vacía o no
        '''
        return self.tope is None