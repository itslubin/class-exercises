
#ifndef Oposiciones_h
#define Oposiciones_h

#include <string>
using namespace std;

const int MAX_OPOSITORES = 100;
const int MAX_EJERCICIOS = 7;
const int APROBADO = 5;

// definicion de tipos
struct tOpositor {
	string id;
	int nota[MAX_EJERCICIOS];
	int num_apr;
	double nota_final = 0;
};

typedef tOpositor* PtrOp;

typedef PtrOp tArray[MAX_OPOSITORES];

struct tListaOpositores {
	tArray opositores;
	int cont = 0;
};

typedef string* Ptrid;

struct tListaAprobPlaza {
	Ptrid opositor;
	int cont = 0;
};

// definicion de los prototipos de los subprogramas pedidos

bool cargarOpositores(tListaOpositores& listaop);
void ordenar(tListaOpositores& listaop);
void mostrarListaOpositores(const tListaOpositores& listaop);
void candidatosConPlaza(tListaOpositores& listaop, tListaAprobPlaza& listaaprob, int plazas_apr);
void mostrarAprobadosConPlaza(const tListaAprobPlaza& listaaprob);
void liberarListaOpositores(tListaOpositores& listaop);
void liberarListaAprobados(tListaAprobPlaza& listaapr);

#endif /* Catalogo_h */
