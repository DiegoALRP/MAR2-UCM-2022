
// Nombre y Apellidos
// Diego Alejandro
// Rodriguez Pereira

// Comentario general sobre la solución,
// explicando cómo se resuelve el problema

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

const int INF = 999999;

void bombillas(int n, int pmax, int pmin, const vector<int> &p, const vector<int> &c, vector<int> &bombi) {
    
    bombi[0] = 0;
    for (int i = 0; i < n; i++) {
        for (int j = p[i]; j <= pmax; j++) {
            
            if (bombi[j - p[i]] != INF && bombi[j] > (bombi[j - p[i]] + c[i])) {
                bombi[j] = bombi[j - p[i]] + c[i];
            }
        }
    }
}

bool resuelveCaso() {

    //leer entrada
    int n, pmax, pmin;
    cin >> n >> pmax >> pmin;
   
    if (!std::cin)  // fin de la entrada
      return false;
    
    vector<int> p = vector<int>(n, 0);
    for (int i = 0; i < n; i++) {
        cin >> p[i];
    }
    
    vector<int> c = vector<int>(n, 0);
    for (int i = 0; i < n; i++) {
        cin >> c[i];
    }
    
    vector<int> bombi(pmax + 1, INF);
    
    bombillas(n, pmax, pmin, p, c, bombi);
    
    int menor = bombi[pmin];
    int indice = pmin;
    for (int i = pmin; i <= pmax; i++) {
        if (bombi[i] < menor) {
            menor = bombi[i];
            indice = i;
        }
    }
    
    if (menor != INF) {
        cout << menor << " " << indice << endl;
    }
    else {
        cout << "IMPOSIBLE" << endl;
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
