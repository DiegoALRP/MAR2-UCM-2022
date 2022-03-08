
// Nombre y Apellidos
// Diego Alejandro
// Rodriguez Pereira

// Comentario general sobre la solución,
// explicando cómo se resuelve el problema

#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

const int INF = 99999;

struct Nodo {
    vector<int> sol; //Vector solucion, que indica el trabajo que se le ha asignado al funcionario i
    vector<bool> marca; //Vector de marcas que indica cuales han sido los trabajos ya tomados
    int k; //Nivel en el que estamos
    double tiempo; //tiempo acumulado hasta el momento
    double tiempo_estimado; //tiempo estimado que se puede obtener
    bool operator < (Nodo const& otro) const {
        return otro.tiempo_estimado < tiempo_estimado;
    }
};

void funcionarios_rp(const vector<vector<int>> &matriz, const vector<int> &min_acum, vector<int> &mejor_sol, int &tiempo_mejor, int n) {
    
    Nodo Y;
    Y.sol = vector<int>(n);
    Y.marca = vector<bool>(n, false);
    Y.k = -1;
    Y.tiempo = 0;
    Y.tiempo_estimado = min_acum[0];
    priority_queue<Nodo> cola;
    cola.push(Y);
    tiempo_mejor = INF;
    
    while (!cola.empty() && cola.top().tiempo_estimado < tiempo_mejor) {
        Y = cola.top();
        cola.pop();
        Nodo X(Y);
        X.k++;
        
        for (int i = 0; i < n; i++) {
            
            if (!Y.marca[i]) { //Test de factibilidad
                X.sol[X.k] = i;
                X.marca[i] = true;
                X.tiempo = Y.tiempo + matriz[X.k][i];
                X.tiempo_estimado = X.tiempo + min_acum[X.k+1]; //Puede que sea k y no k+1
                if (X.tiempo_estimado < tiempo_mejor) {
                    if (X.k == n - 1) {
                        mejor_sol = X.sol;
                        tiempo_mejor = X.tiempo;
                    }
                    else {
                        cola.push(X);
                    }
                }
                X.marca[i] = false;
            }
        }
    }
}


bool resuelveCaso() {

    //leer entrada
    int n;
    cin >> n;
   
    if (n == 0)  // fin de la entrada
      return false;

    vector<int> min(n, INF); //El tiempo minimo que trabaja cada funcionario
    vector<vector<int>> matriz(n, vector<int>(n)); //Matriz que indica cuanto tiempo dura el funcionario i con el trabajo j
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> matriz[i][j];
            if (matriz[i][j] < min[i]) {
                min[i] = matriz[i][j];
            }
        }
    }
    
    vector<int> min_acum(n + 1, 0);
    for (int i = n - 1; i >= 0; i--) {
        min_acum[i] = min[i] + min_acum[i+1];
    }
    
    vector<int> mejor_sol(n);
    int tiempo_mejor = INF;
    
    funcionarios_rp(matriz, min_acum, mejor_sol, tiempo_mejor, n);
    
    cout << tiempo_mejor << endl;
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
