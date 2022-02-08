
// Nombre y Apellidos
// Diego Alejandro
// Rodriguez Pereira

// Comentario general sobre la solución,
// explicando cómo se resuelve el problema

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

void juego(int n, vector<vector<int>> &tablero) {
    
    int resMax = -1;
    int resI = -1;
    int maxi;
    
    for (int i = 1; i < n; i++) {
        
        for (int j = 0; j < n; j++) {
            
            if (j == 0) {
                
                maxi = max(tablero[i-1][j], tablero[i-1][j+1]);
                tablero[i][j] += maxi;
            }
            else if (j == n-1) {
                
                maxi = max(tablero[i-1][j-1], tablero[i-1][j]);
                tablero[i][j] += maxi;
            }
            else {
                
                maxi = max(tablero[i-1][j-1], max(tablero[i-1][j], tablero[i-1][j+1]));
                tablero[i][j] += maxi;
            }
            
            
            if (i == n-1 && tablero[i][j] > resMax) {
                
                resMax = tablero[i][j];
                resI = j + 1;
            }
        }
    }
    
    cout << resMax << " " << resI << endl;
}

bool resuelveCaso() {
   
   // leer los datos de la entrada
    int n;
    cin >> n;
   
    if (!cin)  // fin de la entrada
      return false;
    
    vector<vector<int>> tablero(n, vector<int>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            
            cin >> tablero[i][j];
        }
    }
   
    juego(n, tablero);
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
