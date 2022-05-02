

#include <fstream>
#include <iostream>
#include <string>
using namespace std;

#include "Oposiciones.h"

bool cargarOpositores(tListaOpositores& listaop) {
	cin >> listaop.cont;
	if (!cin) {
		return false;
	}
	else {
		for (int i = 0; i < listaop.cont; i++) {
			tOpositor opositor;
			cin >> opositor.id;
			int j = 0; // j actúa como contador de num_apr
			int nota_ej;
			cin >> nota_ej;
			while (nota_ej >= APROBADO) {
				opositor.nota[j] = nota_ej;
				j++;
				cin >> nota_ej;
			}
			if (nota_ej > 0) { // Si acaba con un suspenso, la nota final es un 0
				opositor.nota[j] = nota_ej;
				opositor.num_apr = j;
			}
			else { // si acaba con un 0, está aprobado y calculamos su nota media
				opositor.num_apr = j--;

				// Calculo de la nota media
				for (int k = 0; k < opositor.num_apr; k++) {
					opositor.nota_final += opositor.nota[k];
				}

				opositor.nota_final = opositor.nota_final / double(opositor.num_apr);
			}
			listaop.opositores[i] = new tOpositor(opositor);
		}
		return true;
	}
}

void ordenar(tListaOpositores& listaop) {
	bool inter = true;
	int i = 0;
	while ((i < listaop.cont - 1) && inter) {
		// Desde el primer elemento hasta el penúltimo o no haya que seguir
		inter = false;
		for (int j = listaop.cont - 1; j > i; j--) {
			// Desde el último hasta el siguiente a i
			if (listaop.opositores[j]->nota_final > listaop.opositores[j - 1]->nota_final) {
				PtrOp tmp;
				tmp = listaop.opositores[j];
				listaop.opositores[j] = listaop.opositores[j - 1];
				listaop.opositores[j - 1] = tmp;
				inter = true;
			}
		}
		if (inter) {
			i++;
		}
	}
}

void eliminarOrdenado(tListaOpositores& listaop, int pos) {
	for (int i = pos; i < listaop.cont - 1; i++) {
		listaop.opositores[i] = listaop.opositores[i + 1];
	}
	listaop.cont--;
}

void candidatosConPlaza(tListaOpositores& listaop, tListaAprobPlaza& listaaprob, int plazas_apr) {
	int aprobados = 0;
	//Calcular el numero de aprobados y eliminar a los aprobados
	for (int i = 0; i < listaop.cont; i++) {
		if (listaop.opositores[i]->nota_final >= APROBADO) {
			aprobados++;
		}
	}

	// Creacion del array dinamico de aprobados con plaza
	listaaprob.opositor = new string[plazas_apr];

	// Como recibe la lista de aprobados de mayor a menor, directamente copiamos a los aprobados
	
	// Si hay más plazas que aprobados
	if (plazas_apr >= aprobados) {
		// copiamos todos "id" de los aprobados al array
		for (int i = 0; i < aprobados; i++) {
			listaaprob.opositor[i] = listaop.opositores[i]->id;
		}
		listaaprob.cont = aprobados;
		for (int i = 0; i < aprobados; i++) {
			eliminarOrdenado(listaop, 0);
		}
	}

	else {
		for (int i = 0; i < plazas_apr; i++) {
			listaaprob.opositor[i] = listaop.opositores[i]->id;
		}
		listaaprob.cont = plazas_apr;

		for (int i = 0; i < plazas_apr; i++) {
			eliminarOrdenado(listaop, 0);
		}
	}
}

void mostrarListaOpositores(const tListaOpositores& listaop) {

	for (int i = 0; i < listaop.cont; i++) {
		cout << "Identificador " << listaop.opositores[i]->id << " - nota final " << listaop.opositores[i]->nota_final << endl;
	}
}

void mostrarAprobadosConPlaza(const tListaAprobPlaza& listaaprob) {
	for (int i = 0; i < listaaprob.cont; i++) {
		cout << "Identificador " << listaaprob.opositor[i] << endl;
	}
}

void liberarListaOpositores(tListaOpositores& listaop) {
	for (int i = 0; i < listaop.cont; i++) {
		delete listaop.opositores[i];
	}
	listaop.cont = 0;
}

void liberarListaAprobados(tListaAprobPlaza& listaapr) {
	delete[] listaapr.opositor;
	listaapr.opositor = nullptr;
	listaapr.cont = 0;
}