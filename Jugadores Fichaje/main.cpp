
#include <iostream>
#include <fstream>
#include <string>
using namespace std;
#include "league.h"

// Declaración de funciones
int resuelveCaso();

int main() {
#ifndef DOMJUDGE
	std::ifstream in("jugadoresFichajes.in");
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
	std::ofstream out("jugadoresFichajes_2.out");
	auto coutbuf = std::cout.rdbuf(out.rdbuf());
#endif

	resuelveCaso();

#ifndef DOMJUDGE // para dejar todo como estaba al principio
	std::cin.rdbuf(cinbuf);
	std::cout.rdbuf(coutbuf);
	system("PAUSE");
#endif
	return 0;
}

int resuelveCaso() {
	tListaJugadores listaj;
	tListaFichajes lista;
	float total = 0;

	if (cargarListaJugadores(listaj) && cargarListaFichajes(lista)) {
		mostrarListaJugadores(listaj);
		mostrarListaFichajes(lista);
		cout << endl << "Y ahora veamos el total y como quedan las listas" << endl << endl;
		hazFichajes(listaj, lista, total);
		cout << "El total de los fichajes es " << total << " millones de euros" << endl;
		cout << endl;
		mostrarListaJugadores(listaj);
		mostrarListaFichajes(lista);
		liberar(listaj);
		liberar(lista);
	}
	else
		cout << "Error en la carga de informacion" << endl;

	return 0;
}