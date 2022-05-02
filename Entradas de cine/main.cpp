
#include <iostream>
#include <string>
#include <fstream>
using namespace std;
#include "cine.h"

bool resuelveCaso();

int main() {
	// ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
	std::ifstream in("datos_cine.in");
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
	std::ofstream out("datos_cine_2.out");
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

bool resuelveCaso() {

	tListaPelis listaPelis;
	tListaPeticiones listaEntradas;
	inicializarListaPelis(listaPelis);
	inicializarListaEntradas(listaEntradas);

	bool cargado = cargar(listaPelis, listaEntradas);

	//  Ha habido un error en la carga.
	if (!cargado) {
		return false;
	}

	// Se han cargado los datos correctamente

	int coste = procesarEntradas(listaPelis, listaEntradas);

	visualizarPelis(listaPelis);
	visualizarPeticiones(listaEntradas);

	cout << "    El coste total es: " << coste << endl << endl;

	destruirlistaEntradas(listaEntradas);
	destruirlistaPelis(listaPelis);
	
	return true;
}
