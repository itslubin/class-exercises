
// Autor/a: Lubin Ye
// email: lubinye@ucm.es
// Nombre del problema: Eliminar los digitos pares de un numero


#include <iostream>
#include <fstream>
#include <string>
// Introduce más librerías si son necesarias
using namespace std;

bool resuelveCaso();
string digitoimpar(unsigned long long int num);

int main() {
   // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
   std::ifstream in("casos.txt");
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

// Se trata de una funcion que recibe un numero y devuelve sus numeros impares
string digitoimpar(unsigned long long int num) {
    string impares;
    int digito;
    if (num == 0) {
        impares = "";
    }
    else {
        digito = num % 10;
        if (digito % 2 == 1) {
            impares = digitoimpar(num / 10) + to_string(digito);
        }
        else {
            impares = digitoimpar(num / 10);
        }
    }
    return impares;
}

// resuelve un caso de prueba
bool resuelveCaso() {
    unsigned long long int num;
    string impares;
   // leer los datos de la entrada
    cin >> num;
   
   if (!std::cin)  // fin de la entrada
      return false;
   impares = digitoimpar(num);
   // escribir sol
   if (impares == "") {
       impares = "0";
   }
   cout << impares << endl;
   return true;
}

