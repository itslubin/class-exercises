
#include <iostream>
#include <fstream>
// Introduce más librerías si son necesarias
using namespace std;

struct tCto{
    int cto[500];
    int cont = 0;
};

void resuelveCaso();
tCto resolver(tCto conjunto1, tCto conjunto2);

int main() {
   // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
   std::ifstream in("datos.in");
   auto cinbuf = std::cin.rdbuf(in.rdbuf());
   std::ofstream out("datos.out");
   auto coutbuf = std::cout.rdbuf(out.rdbuf());
#endif
   
   int numCasos;
   std::cin >> numCasos;
   for (int i = 0; i < numCasos; ++i)
      resuelveCaso();
   
   // para dejar todo como estaba al principio
#ifndef DOMJUDGE
   std::cin.rdbuf(cinbuf);
   std::cout.rdbuf(coutbuf);
   system("PAUSE");
#endif
   return 0;
}

// función que resuelve el problema
tCto resolver(tCto conjunto1, tCto conjunto2) {
    tCto c_sol;
   // Escoger los valores comunes a ambos conjuntos
   // Primero ver elementos comunes ambos conjuntos

    int t = 0;
    for (int i = 0; i < conjunto1.cont; i++) {
        bool iguales = false;
        int j = 0;
        do {
            if (conjunto1.cto[i] == conjunto2.cto[j]) {
                c_sol.cto[t] = conjunto1.cto[i];
                conjunto2.cto[j] = -1;
                t++;
                iguales = true;
            }
            j++;
        } while ((j < conjunto2.cont) && !iguales);
    }

    c_sol.cont = t++;

    if (t != 0) {
        // Luego ordenar el conjunto c_sol
        bool inter = true;
        int k = 0;
        while ((k < c_sol.cont - 1) && inter) {
            // Desde el primer elemento hasta el penúltimo o no haya que seguir
            inter = false;
            for (int o = c_sol.cont - 1; o > k; o--) {
                // Desde el último hasta el siguiente a i
                if (c_sol.cto[o] < c_sol.cto[o - 1]) {
                    int tmp;
                    tmp = c_sol.cto[o];
                    c_sol.cto[o] = c_sol.cto[o - 1];
                    c_sol.cto[o - 1] = tmp;
                    inter = true;
                }
            }
            if (inter) {
                k++;
            }
        }
    }

    return c_sol;

}

// resuelve un caso de prueba
void resuelveCaso() {
    tCto conjunto1, conjunto2, c_sol;

   // lectura de los dos conjuntos
    int i = 0;
    cin >> conjunto1.cto[i];
    while (conjunto1.cto[i] != 0) {
        i++;
        cin >> conjunto1.cto[i];
    }
    if (conjunto1.cto[0] != 0) {
        conjunto1.cont = i++;
    }

    int j = 0;
    cin >> conjunto2.cto[j];
    while (conjunto2.cto[j] != 0) {
        j++;
        cin >> conjunto2.cto[j];
    }
    if (conjunto2.cto[0] != 0) {
        conjunto2.cont = j++;
    }
   
    c_sol = resolver(conjunto1, conjunto2);

   // escribir solución
    for (int t = 0; t < c_sol.cont; t++) {
        cout << c_sol.cto[t] << " ";
   }

    cout << endl;

}
