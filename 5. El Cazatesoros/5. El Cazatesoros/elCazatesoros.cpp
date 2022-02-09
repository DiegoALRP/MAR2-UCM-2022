//
//  elCazatesoros.cpp
//  5. El Cazatesoros
//
//  Created by Diego Alejandro Rodriguez Pereira on 9/2/22.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;


int main() {
    
#ifndef DOMJUDGE
   std::ifstream in("casos.txt");
   auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif
   
   while (resuelveCaso());
   
   // para dejar todo como estaba al principio
#ifndef DOMJUDGE
   std::cin.rdbuf(cinbuf);
   system("PAUSE");
#endif
    return 0;
}
