
#ifndef cine_h
#define cine_h

#include <string>
using namespace std;

const int MAX_Pelis = 50;

typedef struct {
	string titulo;
	int precio;
	int annyo;
	int num_disponibles;
}tPeli;

// Lista de pelis disponibles en la cartelera
typedef struct {
	tPeli* arrayPelis[MAX_Pelis];
	int numPelis;
}tListaPelis;

typedef struct {
	string titulo;
	int num_solicitadas;
}tEntradas;

// Lista de entradas pendientes de confirmar 
typedef struct {
	tEntradas* arrayEntradas;
	int numEntradasPendientes, capacidad;
	// int numEntradasPendientes es como el contador del array dinámico
}tListaPeticiones;

// Prototipos
void inicializarListaEntradas(tListaPeticiones& listaEntradas);
void inicializarListaPelis(tListaPelis& listaPelis);
void ampliar(tListaPeticiones& lista);
bool cargar(tListaPelis& listaPelis, tListaPeticiones& listaEntradas);
void visualizarPelis(const tListaPelis& listaPelis);
void visualizarPeticiones(const tListaPeticiones& listaEntradas);
int procesarEntradas(tListaPelis& listaPelis, tListaPeticiones& listaEntradas); /*recibe una lista de películas y una lista de entradas solicitadas y, con las entradas solicitadas que
son posibles, calcula el coste total de las entradas y deja actualizada la lista
de películas.*/
int buscarPeli(string titulo, const tListaPelis& listaPelis); //Si encuentra la peli, me devuelve la posicion en la que ubica la pelicula en el array o -1 si no lo encuentra
void destruirlistaEntradas(tListaPeticiones& listaEntradas); // Libera la memoria del montón
void destruirlistaPelis(tListaPelis& listaPelis); // Libera la memoria del montón

#endif // !cine_h
