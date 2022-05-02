
#include <iostream>
#include <fstream>
// Introduce más librerías si son necesarias
using namespace std;

// Estructuras

struct tLista {
    int array[20000];
    int cont = 0;
};

void resuelveCaso(tLista lista);
int resolver(tLista lista, int& contador);

int main() {
   // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
   std::ifstream in("datos.in");
   auto cinbuf = std::cin.rdbuf(in.rdbuf());
   std::ofstream out("datos.out");
   auto coutbuf = std::cout.rdbuf(out.rdbuf());
#endif
   
   tLista lista;
   int numCasos;
   std::cin >> numCasos;
   for (int i = 0; i < numCasos; ++i) {
       resuelveCaso(lista);
       if (i != numCasos - 1) {
           cout << endl;
       }
   }
   
   // para dejar todo como estaba al principio
#ifndef DOMJUDGE
   std::cin.rdbuf(cinbuf);
   std::cout.rdbuf(coutbuf);
   system("PAUSE");
#endif
   return 0;
}

// función que resuelve el problema
int resolver(tLista lista, int& contador) {
    int mayor = lista.array[0];
    for (int i = 0; i < lista.cont; i++) {
        // escoger el valor máximo de la fila
        if (lista.array[i] > mayor) {
            mayor = lista.array[i];
        }
   }
    // Me cuenta el número de repeticiones que tiene un número
    for (int i = 0; i < lista.cont; i++) {
        if (lista.array[i] == mayor) {
            contador++;
        }
    }

    return mayor;
}

// resuelve un caso de prueba (cada uno de ellos)
void resuelveCaso(tLista lista) {
   // declaración de variables locales
    int sol;
    int contador = 0;
   // leer los datos de la entrada

    cin >> lista.cont;
    for (int i = 0; i < lista.cont; i++) {
        cin >> lista.array[i];
    }

   sol = resolver(lista, contador);
   
   // escribir solución

   if (sol > 0) {
       cout << " " << sol << " " << contador;
   }
   else {
       cout << sol << " " << contador;
   }
}
