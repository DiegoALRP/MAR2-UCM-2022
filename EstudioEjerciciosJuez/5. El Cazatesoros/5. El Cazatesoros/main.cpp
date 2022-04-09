
// Nombre y Apellidos
// Diego Alejandro
// Rodriguez Pereira

// Comentario general sobre la solución,
// explicando cómo se resuelve el problema

#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

using namespace std;

void cazatesoros(int n, int T, const vector<int> &p, const vector<int> &v, vector<vector<int>> &tesoro) {
    
    for (int i = 0; i <= n; i++){
        for (int j = 0; j <= T; j++) {
            
            if (i == 0 || j == 0) tesoro[i][j] = 0;
            else {
                
                if (j >= 3*p[i-1]) {
                    
                    int a = tesoro[i-1][j];
                    int b = tesoro[i-1][j - 3*p[i-1]] + v[i-1];
                    
                    if (a > b) tesoro[i][j] = a;
                    else tesoro[i][j] = b;
                }
                else {
                    tesoro[i][j] = tesoro[i-1][j];
                }
            }
        }
    }
}

void reconstruye(int n, int T, const vector<int> &p, const vector<int> &v, vector<vector<int>> &tesoro) {
    
    int contador = 0;
    vector<int> prof;
    vector<int> val;
    
    int i = n;
    int j = T;
    while (i > 0 && j > 0) {
        
        if (tesoro[i][j] != tesoro[i - 1][j]) {
            contador++;
            prof.push_back(p[i-1]);
            val.push_back(v[i-1]);
            j = j - 3*p[i-1];
        }
        i--;
    }
    
    cout << contador << endl;
    
    int tam = prof.size();
    for (int i = tam - 1; i >= 0; i--) {
        cout << prof[i] << " " << val[i] << endl;
    }
    
    cout << "---" << endl;
}

bool resuelveCaso() {

    //leer entrada
    int T;
    cin >> T;
   
    if (!std::cin)  // fin de la entrada
      return false;
    
    int n_tesoros;
    cin >> n_tesoros;
    
    vector<int> p = vector<int>(n_tesoros);
    vector<int> v = vector<int>(n_tesoros);
    for (int i = 0; i < n_tesoros; i++) {
        cin >> p[i] >> v[i];
    }
    
    vector<vector<int>> tesoro(n_tesoros + 1, vector<int>(T + 1));
    
    cazatesoros(n_tesoros, T, p, v, tesoro);
    
    cout << tesoro[n_tesoros][T] << endl;
    
    reconstruye(n_tesoros, T, p, v, tesoro);

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
