
#include <iostream>
#include <fstream>
// Introduce más librerías si son necesarias
using namespace std;

struct tSacos {
	int array[1000];
	int cont = 0;
};

void resuelveCaso();
void resolver(tSacos listaS, int& contador);

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
	for (int i = 0; i < numCasos; ++i) {
		resuelveCaso();
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
void resolver(tSacos listaS, int& contador) {
	contador = 0;
	// reordenar la lista de menor a mayor
	bool inter = true;
	int i = 0, aux;
	while ((i < listaS.cont - 1) && inter) {
		inter = false;
		for (int j = listaS.cont - 1; j > i; j--) {
			if (listaS.array[j] < listaS.array[j - 1]) {
				// intercambiamos los valores a modo de burbuja
				aux = listaS.array[j];
				listaS.array[j] = listaS.array[j - 1];
				listaS.array[j - 1] = aux;
				inter = true;
			}
		}
		if (inter) {
			i++;
		}
	}

	// Luego organizamos las parejas (solo pares)

	int t = 0;

	while (t < listaS.cont - 1) {
		if (listaS.array[t] == listaS.array[t + 1]) {
			contador++;
			// Aumentamos en dos porque solo queremos las parejas (pares)
			t = t + 2;
		}
		else {
			t++;
		}
	}

}

// resuelve un caso de prueba (cada uno de ellos), leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
	int num_burros, contador = 0;
	tSacos listaS;

	// leer los datos de la entrada
	cin >> num_burros >> listaS.cont;
	for (int i = 0; i < listaS.cont; i++) {
		cin >> listaS.array[i];
	}

	if (num_burros <= 1000) {

		resolver(listaS, contador);

		// escribimos el número máximo de burros

		if (contador >= num_burros) {
			cout << num_burros;
		}
		else {
			cout << contador;
		}
	}
}
