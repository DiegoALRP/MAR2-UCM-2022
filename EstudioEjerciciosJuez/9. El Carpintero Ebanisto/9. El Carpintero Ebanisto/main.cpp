
// Nombre y Apellidos
// Diego Alejandro
// Rodriguez Pereira

// Comentario general sobre la solución,
// explicando cómo se resuelve el problema

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

const int INF = 99999999;

void ebanisto(int i, int j, int l, int n, const vector<int> &c, vector<vector<int>> &matriz) {
    
    for (int d = 2; d <= n+1; d++) {
        for (int i = 0; i <= n - d + 1; i++) {
            j = i + d;
            
            if (j == i + 1) {
                matriz[i][j] = 0;
            }
            else {
                matriz[i][j] = INF;
                for (int k = i+1; k < j; k++) {
                    int temp = matriz[i][k] + matriz[k][j] + 2*(c[j]-c[i]);
                    if (temp < matriz[i][j]) {
                        matriz[i][j] = temp;
                    }
                }
            }
        }
    }
}

bool resuelveCaso() {

    //leer entrada
    int l, n;
    cin >> l >> n;
   
    if (l == 0 && n == 0)  // fin de la entrada
      return false;

    vector<int> c = vector<int>(n+2);
    c[0] = 0; c[n+1] = l;
    for (int i = 1; i <= n; i++) {
        cin >> c[i];
    }
    
    vector<vector<int>> matriz(n+2, vector<int>(n+2, 0));
    
    ebanisto(0, l, l, n, c, matriz);
    
    cout << matriz[0][n+1] << endl;
    //escribir resultado
   
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
