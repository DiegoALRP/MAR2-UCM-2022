
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

void coche(int n, int precio, const vector<int> &valor, const vector<int> &canti, vector<int> &sol) {
    
    sol[0] = 0;
    
    for (int i = 1; i <= n; i++) {
        for (int j = precio; j >= 0; j--) {
            for (int k = 1; k <= canti[i-1] && k*valor[i-1] <= j; k++) {
                
                int temp = sol[j - (k*valor[i-1])];
                if (temp != INF) temp += k;
                if (temp < sol[j]) sol[j] = temp;
            }
        }
    }
}

bool resuelveCaso() {

    //leer entrada
    int n;
    cin >> n;
   
    if (!std::cin)  // fin de la entrada
      return false;
    
    vector<int> valor = vector<int>(n);
    vector<int> canti = vector<int>(n);
    for (int i = 0; i < n; i++) {
        cin >> valor[i];
    }
    for (int i = 0; i < n; i++) {
        cin >> canti[i];
    }
    
    int precio;
    cin >> precio;
    
    vector<int> sol = vector<int>(precio+1, INF);
    
    coche(n, precio, valor, canti, sol);
    
    int res = sol[precio];
    
    if (res != INF) {
        
        cout << "SI " << res << endl;
    }
    else {
        cout << "NO" << endl;
    }

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
