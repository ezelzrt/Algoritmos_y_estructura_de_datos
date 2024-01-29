

class Heap:
    def __init__(self, comparar): 
        self.comparar = comparar
        self.datos = []
        self.cant = 0


    def esta_vacio(self):
        return self.cant == 0

    def upheap(self, hijo):
        if hijo == 0:
            return
        padre =  (hijo - 1) // 2

        if self.comparar(self.datos[padre], self.datos[hijo]) >= 0: 
            print(f"el {padre} es mayor que el {hijo}")
            return

        self.datos[hijo], self.datos[padre] = self.datos[padre], self.datos[hijo]
        self.upheap(padre)
                
    def encolar(self, elemento):
        self.datos.append(elemento)
        self.datos[self.cant] = elemento
        self.upheap(self.cant)
        self.cant += 1

    def downheap(self, act):
        if 2 * act >= self.cant: return 

        izq = 2 * act + 1
        der = 2 * act + 2
        if der >= self.cant: max_ = izq 
        else: max_ = izq if self.comparar(self.datos[izq], self.datos[der]) > 0  else der

        if self.comparar(self.datos[max_], self.datos[act]) > 0: 
            self.datos[max_], self.datos[act] = self.datos[act], self.datos[max_]
        self.downheap(max_)

    def desencolar(self):
        if self.esta_vacio():
            return None 
        valor = self.datos[0]
        self.datos[0], self.datos[self.cant - 1] = self.datos[self.cant - 1], self.datos[0] 
        self.cant -= 1
        self.downheap(0)
        return valor

    def cantidad(self):
        return self.cant

    def ver_max(self):
        return self.datos[0] if not self.esta_vacio() else None 

def comparar_int(a, b):
    if a == b: return 0

    return 1 if a > b else -1
