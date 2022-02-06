//Nombre: Diego Alejandro Rodriguez Pereira.
//Usuario Domjudge: 270.

// Comentario general sobre la solución,
// explicando cómo se resuelve el problema

#include <iostream>
#include <fstream>
#include <string.h>

using namespace std;
// función que resuelve el problema
// comentario sobre el coste, O(f(N)), donde N es ...
/*Solucion resolver(Datos datos) {
}*/

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
   
   // leer los datos de la entrada
   
   cout << "hola2\n";

   if (!std::cin)  // fin de la entrada
      return false;
   
   cout << "hola3\n";

   int a;

    std::cin >> a;
    std::cout << "a: " << a << endl;

   //Solucion sol = resolver(datos);
   
   // escribir sol
   
   return true;
}

int main() {
   // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
   std::ifstream in("casos.txt");
   auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif
   
   while (cin) {

      int c = 1;
      cin >> c;
      cout << c << endl;
   }
   
   // para dejar todo como estaba al principio
#ifndef DOMJUDGE
   std::cin.rdbuf(cinbuf);
   system("PAUSE");
#endif
   return 0;
}
