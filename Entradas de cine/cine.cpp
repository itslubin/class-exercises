
// ****************************************************

// Prueba de evaluación del día 12 de junio de 2020
// Alumno/a: Lubin Ye
// email:  lubinye@ucm.es
// Grupo: B

// ****************************************************

#include <iostream>
#include <string>
#include <fstream>
using namespace std;

#include "cine.h"


int procesarEntradas(tListaPelis& listaPelis, tListaPeticiones& listaEntradas) {
	int coste = 0;
	for (int i = 0; i < listaEntradas.numEntradasPendientes; i++) {
		// Buscamos dónde está el titulo de la pelicula solicitada en la listaPelis
		int pos = buscarPeli(listaEntradas.arrayEntradas[i].titulo, listaPelis);
		if (pos != -1) { // Si la hemos encontrado en la listaPelis
			// Vemos que si hay localidades disponibles con respecto a las solicitadas
			if (listaPelis.arrayPelis[pos]->num_disponibles > listaEntradas.arrayEntradas[i].num_solicitadas) {
				coste += listaPelis.arrayPelis[pos]->precio * listaEntradas.arrayEntradas[i].num_solicitadas;
				// Actualizar las localidades de listaPelis
				listaPelis.arrayPelis[pos]->num_disponibles -= listaEntradas.arrayEntradas[i].num_solicitadas;
				// Actualizar las entradas pendientes
				listaEntradas.arrayEntradas[i].num_solicitadas = 0;
			}
			else {
				// Actualizar las entradas pendientes
				if (listaPelis.arrayPelis[pos]->num_disponibles == listaEntradas.arrayEntradas[i].num_solicitadas) {
					listaEntradas.arrayEntradas[i].num_solicitadas = 0;
				}
				else {
					listaEntradas.arrayEntradas[i].num_solicitadas -= listaPelis.arrayPelis[pos]->num_disponibles;
				}
				// Actualizar el coste total de las entradas ya posibles de cobrar
				coste += listaPelis.arrayPelis[pos]->precio * listaPelis.arrayPelis[pos]->num_disponibles;
				// Si es que se han acabado las entradas de una pelicula
				listaPelis.arrayPelis[pos] = nullptr;
			}
		}
	}
	return coste;
}

int buscarPeli(string titulo, const tListaPelis& listaPelis) { 
	int pos = -1;
	int i = 0;
	while ( pos == -1 && i < listaPelis.numPelis) {
		if (listaPelis.arrayPelis[i] != nullptr && listaPelis.arrayPelis[i]->titulo == titulo) {
			pos = i;
		}
		else {
			i++;
		}
	}
	return pos;
}
void destruirlistaEntradas(tListaPeticiones& listaEntradas) {
	delete[] listaEntradas.arrayEntradas;
	listaEntradas.numEntradasPendientes = 0;
}

void destruirlistaPelis(tListaPelis& listaPelis) {
	for (int i = 0; i < listaPelis.numPelis; i++) {
		if (listaPelis.arrayPelis[i] != nullptr) {
			delete listaPelis.arrayPelis[i];
			listaPelis.arrayPelis[i] = nullptr;
		}
	}
}

void inicializarListaEntradas(tListaPeticiones& listaEntradas) {
	listaEntradas.numEntradasPendientes = 0;
	listaEntradas.capacidad = 20;
	listaEntradas.arrayEntradas = new tEntradas[listaEntradas.capacidad];
}

void inicializarListaPelis(tListaPelis& listaPelis) {
	listaPelis.numPelis = 0;
}

bool cargar(tListaPelis& listaPelis, tListaPeticiones& listaEntradas) {

	string titulo;
	cin >> titulo;

	if (!cin) // ERROR de carga
		return false;

	while (titulo != "---") { // Centinela
		listaPelis.arrayPelis[listaPelis.numPelis] = new tPeli;
		listaPelis.arrayPelis[listaPelis.numPelis]->titulo = titulo;
		cin >> listaPelis.arrayPelis[listaPelis.numPelis]->precio;
		cin >> listaPelis.arrayPelis[listaPelis.numPelis]->annyo;
		cin >> listaPelis.arrayPelis[listaPelis.numPelis]->num_disponibles;
		listaPelis.numPelis++;
		cin >> titulo;
	}

	cin >> titulo;

	while (titulo != "000") {
		if (listaEntradas.numEntradasPendientes == listaEntradas.capacidad)
			ampliar(listaEntradas);
		listaEntradas.arrayEntradas[listaEntradas.numEntradasPendientes].titulo = titulo;
		cin >> listaEntradas.arrayEntradas[listaEntradas.numEntradasPendientes].num_solicitadas;
		listaEntradas.numEntradasPendientes++;
		cin >> titulo;
	}
	return true;
}



void visualizarPelis(const tListaPelis& listaPelis) {
	cout << endl ;
	cout << "   *****   Lista de pelis   *****   " << endl << endl;

	for (int i = 0; i < listaPelis.numPelis; i++) {
		if (listaPelis.arrayPelis[i] != nullptr) {
			cout << listaPelis.arrayPelis[i]->titulo << " - "
				<< listaPelis.arrayPelis[i]->precio << " euros - "
				<< listaPelis.arrayPelis[i]->annyo << " - "
				<< listaPelis.arrayPelis[i]->num_disponibles << " localidades disponibles." << endl;
		}
	}
	cout << endl;
}


void visualizarPeticiones(const tListaPeticiones& listaEntradas) {

	cout << "   *****   Lista de entradas pendientes por procesar   *****" << endl << endl;

	for (int i = 0; i < listaEntradas.numEntradasPendientes; i++) {
		if (listaEntradas.arrayEntradas[i].num_solicitadas > 0) {
			cout << listaEntradas.arrayEntradas[i].titulo << " - "
				<< listaEntradas.arrayEntradas[i].num_solicitadas << " entradas solicitadas." << endl;
		}
	}
	cout << endl;
}



void ampliar(tListaPeticiones& lista) {

	tEntradas* aux = new tEntradas[2 * lista.capacidad];

	for (int i = 0; i < lista.numEntradasPendientes; i++)
	{
		aux[i] = lista.arrayEntradas[i];
	}

	delete[] lista.arrayEntradas; //OJO! usar [] para vectores din�micos
	lista.arrayEntradas = aux;
	lista.capacidad *= 2;
	aux = nullptr;
}



