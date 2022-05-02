
// Nombre del problema: Calcular el numero de digitos de un numero

#include <iostream>
#include <fstream>
#include <string>
// Introduce más librerías si son necesarias
using namespace std;

//PROTOTIPOS
bool resuelveCaso();
int contarDigitos(unsigned long long int numero);

int main() {
   // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
   std::ifstream in("1.in");
   auto cinbuf = std::cin.rdbuf(in.rdbuf());
   std::ofstream out("datos.out");
   auto coutbuf = std::cout.rdbuf(out.rdbuf());
#endif
   
   while (resuelveCaso());
   
   // para dejar todo como estaba al principio
#ifndef DOMJUDGE
   std::cin.rdbuf(cinbuf);
   std::cout.rdbuf(coutbuf);
   system("PAUSE");
#endif
   return 0;
}

// función que resuelve el problema
int contarDigitos(unsigned long long int numero) {
    int res;
    if (numero > 0) {
        res = 1 + contarDigitos(numero / 10);
    }
    else {
        res = 0;
    }
    return res;
}

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    unsigned long long int numero;
    int num_dig;
   // leer los datos de la entrada

    cin >> numero;
    if (!std::cin)  // fin de la entrada
        return false;

    num_dig = contarDigitos(numero);
   
   // escribir sol

    cout << num_dig << endl;
   
   return true;
}

