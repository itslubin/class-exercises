
#include <fstream>
#include <iostream>
using namespace std;

#include "Oposiciones.h"


bool resuelveCaso();


// NO CAMBIAR LA FUNCIÓN MAIN
int main() {
    // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
    std::ifstream in("opositores.in");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
    std::ofstream out("opositores_2.out");
    auto coutbuf = std::cout.rdbuf(out.rdbuf());
#endif

    int numCasos;
    std::cin >> numCasos;
    for (int i = 0; i < numCasos; ++i) {
        resuelveCaso();
    }

    // para dejar todo como estaba al principio
#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    std::cout.rdbuf(coutbuf);
    system("PAUSE");
#endif
    return 0;
}



bool resuelveCaso() {
    // declaración de varaibles
    tListaOpositores listaop;
    tListaAprobPlaza listaapr;
    int plazas_op;
    bool booleano;
    cin >> plazas_op;
    // 1.- carga desde fichero la información de los opositores: llama a cargarOpositores

    booleano = cargarOpositores(listaop);
    
    // 2.- ordena la posición de los opositores en relación a su media: llama ordenar

    ordenar(listaop);

    // 3.- muestra la lista ordenada de opositores: llama a mostrarListaOpositores

    cout << "Lista con todos los opositores ordenados por calific. media" << endl << endl;
    mostrarListaOpositores(listaop);

    // 4.- crea la lista dinámica de opositores con plaza: llama a candidatosConPlaza

    candidatosConPlaza(listaop, listaapr, plazas_op);

    cout << endl << "Número de plazas: "<< plazas_op << endl << endl;
    
    // 5.- muestra las dos listas: llama a mostrarListaOpositores y mostrarAprobadosConPlaza

    cout << "Lista de opositores que no tienen plaza y suspensos" << endl << endl;

    mostrarListaOpositores(listaop);

    cout << endl << "Lista de opositores que tienen plaza" << endl << endl;

    mostrarAprobadosConPlaza(listaapr);
        
    // 6.- evita las fugas de memoria: llama a liberarListaOpositores y liberarListaAprobados
    
    liberarListaOpositores(listaop);
    liberarListaAprobados(listaapr);

    return booleano;
}
