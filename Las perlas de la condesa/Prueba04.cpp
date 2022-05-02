// Nombre del problema: Problema 4 - Las perlas de la Condesa

#include <iostream>
#include <fstream>
// Introduce más librerías si son necesarias
using namespace std;

// Estructuras
struct tLista {
    int array[1000];
    int cont = 0;
};

// Funciones
bool resolver(tLista& listaP);
bool resuelveCaso();

int main() {
    // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
    std::ifstream in("datos.in");
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
bool resolver(tLista& listaP) {

    if (listaP.cont % 2 == 0)
        return false;

    // Organizar la lista de menor a mayor (método burbuja)
    bool inter = true;
    int i = 0;
    while ((i < listaP.cont) && inter) {
        inter = false;
        for (int j = listaP.cont - 1; j > i; j--) {
            if (listaP.array[j] < listaP.array[j - 1]) {
                int aux;
                aux = listaP.array[j];
                listaP.array[j] = listaP.array[j - 1];
                listaP.array[j - 1] = aux;
                inter = true;
            }
        }
        if (inter) {
            i++;
        }
    }

    // Ver si hay parejas de cada, si no, es que no se puede (for)

    bool pareja = true;
    int t = 0;
    // Hasta el penúltimo índice comparamos los elementos, ya que no queremos comparar el 0
    while ((t < listaP.cont - 1) && pareja) {
        if (listaP.array[t] != listaP.array[t + 1]) {
            pareja = false;
        }
        else {
            t = t + 2;
        }
    }

    return pareja;
}

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {

    tLista listaP;
    // leer los datos de la entrada

    int i = 0;
    cin >> listaP.array[i];

    // Si estamos en el caso centinela
    if (listaP.array[i] == 0) {
        return false;
    }

    while (listaP.array[i] != 0) {
        i++;
        cin >> listaP.array[i];
    }

    // El contador es el índice más uno
    listaP.cont = i;

    // Resolver el caso y escribir la solución

    bool pareja = resolver(listaP);

    if (pareja) {
        int j = 0;
        while (j < listaP.cont - 1) {
            cout << listaP.array[j] << " ";
            j = j + 2;
        }
        while (j >= 0) {
            cout << listaP.array[j];
            if (j > 0) {
                cout << " ";
            }
            j = j - 2;
        }
        cout << endl;
    }

    else {
        cout << "NO" << endl;
    }

    return true;
}