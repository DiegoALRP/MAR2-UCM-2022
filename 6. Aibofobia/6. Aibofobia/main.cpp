
// Nombre y Apellidos
// Diego Alejandro
// Rodriguez Pereira

// Comentario general sobre la solución,
// explicando cómo se resuelve el problema

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

const int MAX_ENT = 999999;

int aibo(int i, int j, string &palabra, vector<vector<int>> &matriz) {
    
    if (matriz[i][j] != MAX_ENT) return matriz[i][j];
    if (i == j || i > j) {
        
        matriz[i][j] = 0;
        return 0;
    }
    if (palabra[i] == palabra[j]) {
        
        matriz[i][j] = aibo(i + 1, j - 1, palabra, matriz);
    }
    else {
        
        matriz[i][j] = min(aibo(i, j - 1, palabra, matriz), aibo(i + 1, j, palabra, matriz)) + 1;
    }
    
    return matriz[i][j];
}

void reconstruccion(int i, int j, string &palabra, string &word, vector<vector<int>> &matriz) {
    
    if (i > j) return;
    if (i == j) {
        
        word.push_back(palabra[i]);
    }
    else if (palabra[i] == palabra[j]) {
        
        word.push_back(palabra[i]);
        reconstruccion(i + 1, j - 1, palabra, word, matriz);
        word.push_back(palabra[j]);
    }
    else if (matriz[i][j] == matriz[i][j-1]+1) {
        
        word.push_back(palabra[j]);
        reconstruccion(i, j - 1, palabra, word, matriz);
        word.push_back(palabra[j]);
    }
    else {
        
        word.push_back(palabra[i]);
        reconstruccion(i + 1, j, palabra, word, matriz);
        word.push_back(palabra[i]);
    }
}

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
   
   // leer los datos de la entrada
    
    string palabra;
    
    cin >> palabra;
   
   if (!std::cin)  // fin de la entrada
      return false;
    
    int long_palabra = (int) palabra.size();
    
    vector<vector<int>> matriz(long_palabra, vector<int>(long_palabra, MAX_ENT));
   
    int res = aibo(0, long_palabra - 1, palabra, matriz);
    
    string word;
    reconstruccion(0, long_palabra - 1, palabra, word, matriz);
    //cout << "\n\n";
    cout << res << " " << word << endl;
    
   // escribir sol
   
   return true;
}

int main() {
   // ajustes para que cin extraiga directamente de un fichero
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
