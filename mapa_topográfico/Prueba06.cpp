
#include <iostream>
#include <fstream>
// Introduce más librerías si son necesarias
using namespace std;

// Declaración de constantes

const int MAX_FILAS = 100;
const int MAX_COLUMNAS = 100;

typedef int tTabla[MAX_FILAS][MAX_COLUMNAS];

struct tMatriz {
    tTabla matriz;
    int filas, columnas;
};

struct tPosicion {
    int fila = 0;
    int columna = 0;
};

istream &operator>>(istream& in, tMatriz& m);
tPosicion resolver(tMatriz m, int& mayor);
bool resuelveCaso();

int main() {
   // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
   std::ifstream in("casos.in");
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

istream& operator>>(istream& in, tMatriz& m) {
    in >> m.filas >> m.columnas;
    for (int i = 0; i < m.filas; i++) {
        for (int j = 0; j < m.columnas; j++) {
            in >> m.matriz[i][j];
        }
    }
    return in;
}

// dada una matriz que representa la cuadrícula devuelve la altura maximo y la posicion en que se encuentra
tPosicion resolver(tMatriz m, int& mayor) {
    tPosicion posicion;
    mayor = m.matriz[0][0];
    for (int i = 0; i < m.filas; i++) {
        for (int j = 0; j < m.columnas; j++) {
            if (m.matriz[i][j] > mayor) {
                mayor = m.matriz[i][j];
                posicion.fila = i;
                posicion.columna = j;
            }
        }
    }

    return posicion;
}

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
   
    tMatriz matriz;
    tPosicion posicion_mayor;
    int mayor;
   // leer los datos de la entrada

    cin >> matriz;
   
   if (!std::cin)  // fin de la entrada
      return false;
   
   // escribir sol

   posicion_mayor = resolver(matriz, mayor);

   cout << mayor << " " << posicion_mayor.fila << " " << posicion_mayor.columna << endl;
   
   return true;
}

