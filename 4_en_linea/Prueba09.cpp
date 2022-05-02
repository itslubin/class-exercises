
// Nombre del problema: 4 en línea

#include <iostream>
#include <fstream>
// Introduce más librerías si son necesarias
using namespace std;

const int MAX_FILAS = 6, MAX_COLUMNAS = 7, MAX_DIR = 8, FICHAS_GANADOR = 4;

const int incF[8] = { 1,1,0,-1,-1,-1,0,1 };
const int incC[8] = { 0,1,1,1,0,-1,-1,-1 };

struct tTablero {
    char m[MAX_FILAS][MAX_COLUMNAS];
    int fila = 0, col = 0;
};

bool resuelveCaso();
bool dentro(int x, int y);
bool comprobar(const tTablero& tablero, char& ficha);

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

bool dentro(int x, int y) {
    return (x >= 0 && x < MAX_FILAS && y >= 0 && y < MAX_COLUMNAS);
}

bool comprobar(const tTablero& tablero, char& ficha) { // Recibe el tablero con las fichas y comprueba si hay ganador, devuelve la ficha ganadora (letra del jugador)
    int cont, i, j, k;
    cont = 1; // Contador del avance de las posiciones radialmente
    i = 0;
    k = 0; // Contador del array de las posiciones radiales
    bool hay_ganador = false;//para que siga el bucle si han coincidido 2 letras
    while (i < MAX_FILAS && !hay_ganador) {
        j = 0;
        while (j < MAX_COLUMNAS && !hay_ganador) {
            cont = 1;
            k = 0;
            if (tablero.m[i][j] != 'X') {
                do { // Entonces, miro a ver si hay cuatro iguales
                    if (dentro(i + incF[k] * cont, j + incC[k] * cont) && tablero.m[i][j] == tablero.m[i + incF[k] * cont][j + incC[k] * cont]) {
                        cont++; //Si van coincidiendo voy mirando si hay más iguales
                    }
                    else {
                        k++; // Cambio de radial
                        cont = 1;
                    }
                } while (cont < FICHAS_GANADOR && !hay_ganador && k < MAX_DIR);
            }
            if (cont == FICHAS_GANADOR) { // Que es 4
                hay_ganador = true;
                ficha = tablero.m[i + incF[k]][j + incC[k]];
            }
            j++;
        }
        i++;
    }
    return hay_ganador;
}

// resuelve un caso de prueba
bool resuelveCaso() {
   
    int total_fichas;
    tTablero tablero;
    char ficha = 'X';
    int array[MAX_COLUMNAS]; //Será el contador del aumento de filas en cada columna

    for (int i = 0; i < MAX_COLUMNAS; i++) {
        array[i] = 0;
    }

    // leer los datos de la entrada
    cin >> total_fichas;

    if (total_fichas == 0) {
        return false;
    }

    // Inicializamos el tablero con 'X'
    for (int i = 0; i < MAX_FILAS; i++) {
        for (int j = 0; j < MAX_COLUMNAS; j++) {
            tablero.m[i][j] = 'X';
        }
    }

    for (int i = 0; i < total_fichas; i++) {
        cin >> tablero.col;
        if (i % 2 == 0) {
            tablero.m[array[tablero.col]][tablero.col] = 'A';
        }
        else {
            tablero.m[array[tablero.col]][tablero.col] = 'B';
        }
        array[tablero.col]++;
    }
   
   // escribir sol

    if (comprobar(tablero, ficha)) {
        if (ficha == 'A') {
            cout << "Gana A";
        }
        else if (ficha == 'B') {
            cout << "Gana B";
        }
    }
    
    else {
        cout << "Empate";
    }

    cout << endl;
   
   return true;
}