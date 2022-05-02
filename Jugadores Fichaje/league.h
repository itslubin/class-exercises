
#ifndef league_h
#define league_h


#include<iostream>
#include<fstream>
#include<string>
using namespace std;

const int MAX_JUGADORES = 50;
const int MAX_FichajeS = 20;


typedef struct {
	string id, nombre;
	string equipo;
	float precio;
} tJugador;

typedef tJugador* tPtrJugador;

typedef struct {
	tPtrJugador jugadores;
	int contador;
} tListaJugadores;

typedef struct {
	string id, equipo;
	float cantidad;
} tFichaje;

typedef tFichaje* tPtrFichaje;
typedef tPtrFichaje tArray[MAX_FichajeS];

typedef struct {
	tArray Fichajes;
	int contador;
} tListaFichajes;

// carga la lista de jugadores desde cin
bool cargarListaJugadores(tListaJugadores& listaj);

// carga una lista de Fichajes desde cin
bool cargarListaFichajes(tListaFichajes& lista);

// muestra la lista de jugadores por pantalla
void mostrarListaJugadores(const tListaJugadores& listaj);

// muestra la lista de Fichajes por pantalla
void mostrarListaFichajes(const tListaFichajes& lista);

// realiza los Fichajes que son posibles, computando el importe total  y dejando actualizada la lista de jugadores
void hazFichajes(tListaJugadores& listaj, tListaFichajes& lista, float& total);

// libera la memoria dinamica utilizada con la lista de jugadores
void liberar(tListaJugadores& listaj);

// libera la memoria dinamica utilizada con la lista de Fichajes
void liberar(tListaFichajes& lista);

#endif
