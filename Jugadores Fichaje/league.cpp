
#include<iostream>
#include<fstream>
#include<string>
using namespace std;
#include "league.h"


bool cargarListaJugadores(tListaJugadores& listaj) {
	char aux;
	tJugador jugador;
	int numJugadores;

	listaj.contador = 0;
	listaj.jugadores = new tJugador[MAX_JUGADORES];
	cin >> numJugadores;
	for (int i = 0; i < numJugadores; i++) {
		cin >> jugador.id;
		cin.get(aux);
		getline(cin, jugador.nombre);
		getline(cin, jugador.equipo);
		cin >> jugador.precio;
		listaj.jugadores[i] = jugador;
		listaj.contador = listaj.contador + 1;
	}
	string aux2;
	cin >> aux2;  // recoge --
	return true;
}

bool cargarListaFichajes(tListaFichajes& lista) {

	int numFichajes;
	tFichaje trans;
	char aux;

	lista.contador = 0;
	cin >> numFichajes;
	for (int i = 0; i < numFichajes; i++) {
		cin >> trans.id;
		cin.get(aux);
		getline(cin, trans.equipo);
		cin >> trans.cantidad;
		lista.Fichajes[i] = new tFichaje(trans);
		lista.contador = lista.contador + 1;

	}
	return true;
}

void mostrarListaJugadores(const tListaJugadores& listaj) {
	cout << "********* LISTA DE JUGADORES *********" << endl;
	for (int i = 0; i < listaj.contador; i++) {
		cout << listaj.jugadores[i].id << " - " << listaj.jugadores[i].nombre << " ";
		cout << listaj.jugadores[i].equipo << " " << listaj.jugadores[i].precio << " mill. euros " << endl;
	}
	cout << endl;
}

void mostrarListaFichajes(const tListaFichajes& lista) {
	cout << "*********  LISTA DE FICHAJES  *********" << endl;
	for (int i = 0; i < lista.contador; i++) {
		if (lista.Fichajes[i] != nullptr) {
			cout << lista.Fichajes[i]->id << " - "
				<< lista.Fichajes[i]->equipo << " "
				<< lista.Fichajes[i]->cantidad << " mill. euros" << endl;
		}
	}
	cout << endl;
}

int buscarJugador(string id, const tListaJugadores& listaj) { // Busca la posicion del array de listaj donde se halla el jugador buscado, devuelve su posicion si lo encuntra o -1 en caso contrario
	int pos = -1;
	int i = 0;
	while (pos == -1 && i < listaj.contador) {
		if (id == listaj.jugadores[i].id) {
			pos = i;
		}
		else {
			i++;
		}
	}

	return pos;
}

void hazFichajes(tListaJugadores& listaj, tListaFichajes& lista, float& total) {
	for (int i = 0; i < lista.contador; i++) {
		// Buscar en la listaj si está el identificador del jugador que queremos fichar
		int pos = buscarJugador(lista.Fichajes[i]->id, listaj);
		if (pos != -1 && lista.Fichajes[i]->cantidad >= listaj.jugadores[pos].precio) {
			// Si está y lo aportado es suficiente para ficharlo
			// se actualiza el valor/coste total
			total += lista.Fichajes[i]->cantidad;
			// Si lo podemos fichar (se quita de la lista de fichajes) y se actualiza el equipo al que pertenece ese jugador
			listaj.jugadores[pos].equipo = lista.Fichajes[i]->equipo;
			delete lista.Fichajes[i];
			lista.Fichajes[i] = nullptr;
			// Si no lo podemos fichar o no está, se desestima (es decir, se deja en la lista de fichajes)
		}
	}
}

void liberar(tListaJugadores& listaj) {
	delete[] listaj.jugadores;
	listaj.contador = 0;
}

void liberar(tListaFichajes& lista) {
	for (int i = 0; i < lista.contador; i++) {
		if (lista.Fichajes[i] != nullptr) {
			delete lista.Fichajes[i];
			lista.Fichajes[i] = nullptr;
		}
	}
	lista.contador = 0;
}