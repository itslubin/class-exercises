
// Nombre del problema: Coleccion de fotos (implementacion con memoria dinamica)

#include <iostream>
#include <fstream>
#include <string>
// Introduce más librerías si son necesarias
using namespace std;

const int MAX_FOTOS = 50;

struct tFoto {
    string titulo, tema;
};

typedef tFoto* tPuntFoto;
typedef tPuntFoto tArrayPunt[200];

struct tArrayDFotos {
    tArrayPunt array;
    int cont = 0;
};

struct tListaFotos {
    tPuntFoto arrayFotos[200];
    int cont = 0;
};

void cargar(tListaFotos& listaFotos);
void inicializarArrays(tListaFotos listaFotos, tArrayDFotos& p1, tArrayDFotos& p2);
void mostrarTitulo(const tArrayDFotos& lista);
void mostrarTituloTema(const tArrayDFotos& lista);
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

void cargar(tListaFotos& listaFotos) { //Carga las fotos en la lista
    cin.ignore();
    for (int i = 0; i < listaFotos.cont; i++) {
        listaFotos.arrayFotos[i] = new tFoto;
        getline(cin, listaFotos.arrayFotos[i]->titulo);
    }
    for (int i = 0; i < listaFotos.cont; i++) {
        getline(cin, listaFotos.arrayFotos[i]->tema);
    }
}

void inicializarArrays(tListaFotos listaFotos, tArrayDFotos& p1, tArrayDFotos& p2) { //Ordena los arrays de punteros
    bool inter = true;
    int i = 0;
    // Se ordenan los titulos de menor a mayor
    while ((i < listaFotos.cont - 1) && inter) {
        // Desde el primer elemento hasta el penúltimo o no haya que seguir
        inter = false;
        for (int j = listaFotos.cont - 1; j > i; j--) {
            // Desde el último hasta el siguiente a i
            if (listaFotos.arrayFotos[j]->titulo < listaFotos.arrayFotos[j - 1]->titulo) {
                tFoto tmp;
                tmp = *listaFotos.arrayFotos[j];
                *listaFotos.arrayFotos[j] = *listaFotos.arrayFotos[j - 1];
                *listaFotos.arrayFotos[j - 1] = tmp;
                inter = true;
            }
        }
        if (inter) {
            i++;
        }
    }

    // Inicializar el contador
    p1.cont = listaFotos.cont; 
    // Se copia listaFotos ya ordenada a p1
    for (int i = 0; i < listaFotos.cont; i++) {
        p1.array[i] = new tFoto(*listaFotos.arrayFotos[i]);
    }

    // Se ordena por tema
    inter = true;
    i = 0;
    while ((i < listaFotos.cont - 1) && inter) {
        // Desde el primer elemento hasta el penúltimo o no haya que seguir
        inter = false;
        for (int j = listaFotos.cont - 1; j > i; j--) {
            // Desde el último hasta el siguiente a i
            if (listaFotos.arrayFotos[j]->tema < listaFotos.arrayFotos[j - 1]->tema) {
                tFoto tmp;
                tmp = *listaFotos.arrayFotos[j];
                *listaFotos.arrayFotos[j] = *listaFotos.arrayFotos[j - 1];
                *listaFotos.arrayFotos[j - 1] = tmp;
                inter = true;
            }
        }
        if (inter) {
            i++;
        }
    }

    // Inicializar el contador
    p2.cont = listaFotos.cont;
    // Se copia listaFotos ya ordenada por temas y titulos a p2
    for (int i = 0; i < listaFotos.cont; i++) {
        p2.array[i] = new tFoto(*listaFotos.arrayFotos[i]);
    }
}

void mostrarTitulo(const tArrayDFotos& lista) {
    for (int i = 0; i < lista.cont; i++) {
        cout << lista.array[i]->titulo << endl;
    }
}

void mostrarTituloTema(const tArrayDFotos& lista) {
    for (int i = 0; i < lista.cont; i++) {
        cout << lista.array[i]->tema << " - " << lista.array[i]->titulo << endl;
    }
}

void destruirtListaFotos(tListaFotos& lista) {
    for (int i = 0; i < lista.cont; i++) {
        delete lista.arrayFotos[i];
        lista.arrayFotos[i] = nullptr;
    }
    lista.cont = 0;
}

void destruirtArrayDFotos(tArrayDFotos& lista) {
    for (int i = 0; i < lista.cont; i++) {
        delete lista.array[i];
        lista.array[i] = nullptr;
    }
    lista.cont = 0;
}

bool resuelveCaso() {
    // Declaracion de variables
   tListaFotos listaFotos;
   tArrayDFotos p1, p2;
   cin >> listaFotos.cont;
   // leer los datos de la entrada
   if (listaFotos.cont == 0) {
       return false;
   }
   cargar(listaFotos);
   inicializarArrays(listaFotos, p1, p2);
   // escribir sol
   mostrarTitulo(p1);
   cout << endl;
   mostrarTituloTema(p2);

   destruirtArrayDFotos(p1);
   destruirtArrayDFotos(p2);
   destruirtListaFotos(listaFotos);
   
   return true;
}
