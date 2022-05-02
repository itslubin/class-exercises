
// Nombre del problema: La sopa de letras

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <limits>

// Introduce más librerías si son necesarias
using namespace std;

// Constantes
const int MAX_F = 50;
const int MAX_C = 50;
const int ARRAY_DIR = 8;
const int incF[8] = { 1,1,0,-1,-1,-1,0,1 };
const int incC[8] = { 0,1,1,1,0,-1,-1,-1 };

//Tipos
struct tCasilla {
	char letra;
	bool sol = false;
};

struct  tMatriz {
	int nfilas = 0, ncol = 0;
	tCasilla m[MAX_F][MAX_C];
};

struct tPalabra {
	string word;
	int cont = 0;
};

//Prototipos
bool dentro(tMatriz m, int x, int y);
void resuelveCaso();
istream& operator>> (istream& in, tMatriz& m);
ostream& operator<< (ostream& out, tMatriz const& m);
istream& operator>> (istream& in, tPalabra& palabra);


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

istream& operator>> (istream& in, tMatriz& m) {
	in >> m.nfilas >> m.ncol;
	in.ignore(numeric_limits<streamsize>::max(), '\n');
	for (int i = 0; i < m.nfilas; i++) {
		for (int j = 0; j < m.ncol; j++) {
			in.get(m.m[i][j].letra);
		}
		in.ignore(numeric_limits<streamsize>::max(), '\n');
	}
	return in;
}

istream& operator>> (istream& in, tPalabra& palabra) {
	in >> palabra.word;
	palabra.cont = palabra.word.size();
	return in;
}

ostream& operator<< (ostream& out, tMatriz const& m) {
	for (int k = 0; k < m.ncol; k++) {
		out << " -";
	}
	out << endl;
	for (int i = 0; i < m.nfilas; i++) {
		for (int j = 0; j < m.ncol; j++) {
			if (m.m[i][j].sol) {
				out << right << setw(2) << m.m[i][j].letra;
			}
			else {
				out << "  ";
			}
		}
		out << endl;
	}

	for (int k = 0; k < m.ncol; k++) {
		out << " -";
	}
	out << endl << endl;

	return out;
}

bool dentro(tMatriz m, int x, int y) {
	return (x >= 0 && x < m.nfilas && y >= 0 && y < m.ncol);
}

void resuelveCaso() {
   
	tMatriz sopa;
	int num_palabras;
	tPalabra palabra;
	bool encontrado, found;

   // leer los datos de la entrada
	cin >> sopa;

	cin >> num_palabras;

	// Hay que comparar la primera letra de la palabra con la sopa de letras hasta encontrar la misma igual

	int i; //contador de las filas de la matriz
	int j = 0; //contador de las columnas de la matriz
	int a = 0; //contador de la longuitud de la palabra
	int k = 0; // contador del array de cambio radial
	int p = 0; //contador de la posicion de la palabra en la que estoy en sentido directo
	int q = palabra.cont - 1; //contador de la posicion de la palabra en la que estoy en sentido inverso
	int cont = 1; //contador para multiplicar la coordenada radial tantas como la longitud de la palabra, por eso empieza en 1 al tener que multiplicarse
	int dir = 0;

	for (int c = 0; c < num_palabras; c++) {
		cin >> palabra;
		i = 0;
		encontrado = false;
		while (i < sopa.nfilas && !encontrado) {
			j = 0;
			while (j < sopa.ncol && !encontrado) {
				p = 0;
				q = palabra.cont - 1;
				if (sopa.m[i][j].letra == palabra.word[p]) {
					p++; // busco la siguiente letra de la palabra en la sopa
					k = 0;
					while (k < ARRAY_DIR && !encontrado) { // para avanzar radialmente
						found = true;
						cont = 1;
						while (a < palabra.cont && !encontrado && found && dentro(sopa, i + incF[k] * cont, j + incC[k] * cont)) { // para avanzar en una radial hasta el final de la longitud de la palabra
							if (sopa.m[i + incF[k] * cont][j + incC[k] * cont].letra == palabra.word[p]) {
								cont++; // miro la siguiente letra de la sopa radialmente de una manera
								p++; // miro la siguiente letra de mi palabra
								a++; // miro la siguiente letra de mi array de palabra
							}
							else {
								p = 1; // si una letra falla reseteamos el contador de las letras que coinciden
								found = false; // no he encontrado la letra que buscaba
							}
							if (p == palabra.cont) {
								for (int o = 0; o < palabra.cont; o++) {
									sopa.m[i + incF[k] * o][j + incC[k] * o].sol = true;
									encontrado = true;
								}
							}
						}
						a = 0;
						k++;
					}
				}

				else if (sopa.m[i][j].letra == palabra.word[q]) {
					q--; // busco la siguiente letra de la palabra en la sopa
					k = 0;
					while (k < ARRAY_DIR && !encontrado) { // para avanzar radialmente
						found = true;
						cont = 1;
						while (a < palabra.cont && !encontrado && found && dentro(sopa, i + incF[k] * cont, j + incC[k] * cont)) { // para avanzar en una radial hasta el final de la longitud de la palabra
							if (sopa.m[i + incF[k] * cont][j + incC[k] * cont].letra == palabra.word[q]) {
								cont++;  // miro la siguiente letra de la sopa radialmente
								q--; // miro la siguiente letra de mi palabra de forma inversa
								a++; // miro la siguiente letra de mi array de palabra
							}
							else {
								found = false; // no he encontrado la letra que buscaba
								q = palabra.cont - 2; // si una letra falla reseteamos el contador de las letras que coinciden ( -2 por que la primera es -1 y esa sí coincide)
							}
							if (q == -1) {
								for (int o = 0; o < palabra.cont; o++) {
									sopa.m[i + incF[k] * o][j + incC[k] * o].sol = true;
									encontrado = true;
								}
							}
						}
						a = 0;
						k++;
					}
				}
				j++;
			}
			i++;
		}
	}

	// escribir solución
	cout << sopa;
}
