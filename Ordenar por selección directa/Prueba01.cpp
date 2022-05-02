
#include <iostream>
#include <fstream>
// Introduce más librerías si son necesarias
using namespace std;

struct tArrayDatos {
	int array[100];
	int cont = 0;
};

void resolver(tArrayDatos& datos);
void resuelveCaso();

int main() {
	// ajustes para que cin extraiga directamente de un fichero
	 // redirige el flujo del cin al del fichero
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
// recibe un caso único y devuelve el caso ordenado
void resolver(tArrayDatos& datos) {
	// ordenar el array
	for (int i = 0; i < datos.cont - 1; i++) {
		int menor = i;
		// Desde i + 1 hasta el final...
		for (int j = i + 1; j < datos.cont; j++) {
			if (datos.array[j] < datos.array[menor])
				menor = j;
		}
		if (menor > i) {
			int tmp;
			tmp = datos.array[i];
			datos.array[i] = datos.array[menor];
			datos.array[menor] = tmp;
		}
	}
}

// resuelve un caso de prueba (cada uno de ellos), leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {

	// leer los datos de la entrada
	tArrayDatos array_numeros;
	int num;
	cin >> num;
	while (num != 0) {
		array_numeros.array[array_numeros.cont] = num;
		array_numeros.cont++;
		cin >> num;
	}
	resolver(array_numeros);

	// escribir solución

	for (int i = 0; i < array_numeros.cont; i++) {
		if (i == array_numeros.cont - 1) {
			cout << array_numeros.array[i];
		}
		else {
			cout << array_numeros.array[i] << " ";
		}
	}
	cout << endl;
}
