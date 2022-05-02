
// Nombre del problema: La fábrica de Papa Noel

#include <iostream>
#include <fstream>
// Introduce más librerías si son necesarias
using namespace std;

// Declaración de constantes
const int N = 100, M = 100;

// Declaración de tipos
struct tMatriz {
    int matriz[N][M];
    int fila = 0, columna = 0;
};

// Prototipos
bool resuelveCaso();
tMatriz operator* (tMatriz const& a, tMatriz const& b); // Multiplica dos matrices
istream& operator>> (istream& in, tMatriz& m); // Lee una matriz
ostream& operator<< (ostream& out, tMatriz const& m); // Imprime por pantalla una matriz


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


tMatriz operator* (tMatriz const& a, tMatriz const& b) {
    tMatriz matriz_result;
    int tmp = 0;
    int i = 0, cont = 0, t = 0;
    while (i < a.fila) {
        for (int j = 0; j < a.columna; j++) {
             tmp = tmp + a.matriz[i][j] * b.matriz[j][t];
        }
        // Introducimos el valor en la matriz
        matriz_result.matriz[i][t] = tmp;
        t++;
        // Contador de cuando termina de multiplicar una fila con una columna
        cont++;
        // Si hemos terminado de multiplicar una fila con todas las columnas reseteamos cont y t, y aumentamos el contador i
        if (cont == b.columna) {
            i++;
            cont = 0;
            t = 0;
        }
        tmp = 0;
    }

    matriz_result.fila = a.fila;
    matriz_result.columna = b.columna;

    return matriz_result;
}

istream& operator>> (istream& in, tMatriz& m) {
    in >> m.fila >> m.columna;
    for (int i = 0; i < m.fila; i++) {
        for (int j = 0; j < m.columna; j++) {
            in >> m.matriz[i][j];
        }
    }
    return in;
}

ostream& operator<< (ostream& out, tMatriz const& m) {
    for (int i = 0; i < m.fila; i++) {
        for (int j = 0; j < m.columna; j++) {
            out << m.matriz[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
    return out;
}

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    tMatriz matriz_1, matriz_2, matriz_sol;

    if (!std::cin)  // fin de la entrada
        return false;

   // leer los datos de la entrada
    cin >> matriz_1;
    cin >> matriz_2;

    matriz_sol = matriz_1 * matriz_2;
   
   // escribir sol

    cout << matriz_sol;
   
   return true;
}

