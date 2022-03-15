
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

const int INF = 999999999;
const int MAX_PRODUCTOS = 3;

struct Nodo {
    
    vector<int> sol; //sol[i] contiene el supermercado j donde se compra el producto i
    vector<int> marcas; //marcas[i] contiene el numero de productos que se compra en el supermercado i
    int k;
    double gasto;
    double gasto_estimado;
    bool operator<(Nodo const& otro) const {
        return otro.gasto_estimado < gasto_estimado;
    }
};

void compra_rp(int m, int n, const vector<vector<int>> &matriz_precios, const vector<int> &v_estimacion, vector<int> &mejor_sol, int &mejor_gasto) {
    
    Nodo Y;
    Y.sol = vector<int>(n, -1);
    Y.marcas = vector<int>(m, 0);
    Y.k = -1;
    Y.gasto = 0;
    Y.gasto_estimado = v_estimacion[0];
    priority_queue<Nodo> cola;
    cola.push(Y);
    mejor_gasto = INF;
    
    while (!cola.empty() && cola.top().gasto_estimado < mejor_gasto) {
        
        Y = cola.top();
        cola.pop();
        Nodo X(Y);
        X.k++;
        
        for (int i = 0; i < m; i++) {
            
            if (Y.marcas[i] < 3) {
                X.sol[X.k] = i;
                X.marcas[i]++;
                X.gasto = Y.gasto + matriz_precios[i][X.k];
                X.gasto_estimado = X.gasto + v_estimacion[X.k+1];
                if (X.gasto_estimado < mejor_gasto) {
                    if (X.k == n - 1) {
                        mejor_sol = X.sol;
                        mejor_gasto = X.gasto;
                    }
                    else {
                        cola.push(X);
                    }
                }
                X.marcas[i]--;
                X.gasto = Y.gasto;
                X.gasto_estimado = v_estimacion[X.k+1];
            }
        }
    }
}

void resuelveCaso() {

    //leer entrada
    int m_supermercados, n_productos;
    cin >> m_supermercados >> n_productos;
    
    vector<int> producto_mas_barato = vector<int>(n_productos, INF);
    vector<vector<int>> matriz_precios(m_supermercados, vector<int>(n_productos));
    for (int i = 0; i < m_supermercados; i++) {
        for (int j = 0; j < n_productos; j++) {
            cin >> matriz_precios[i][j];
            if (matriz_precios[i][j] < producto_mas_barato[j]) {
                producto_mas_barato[j] = matriz_precios[i][j];
            }
        }
    }
    
    vector<int> producto_barato = vector<int>(n_productos + 1);
    for (int i = n_productos - 1; i >= 0; i--) {
        producto_barato[i] = producto_mas_barato[i] + producto_barato[i+1];
    }
    
    vector<int> mejor_sol;
    int mejor_gasto = INF;
    compra_rp(m_supermercados, n_productos, matriz_precios, producto_barato, mejor_sol, mejor_gasto);
    
    cout << mejor_gasto << endl;
    //escribir resultado
   
}

int main() {
   // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
   std::ifstream in("casos.txt");
   auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif
   
    int numCasos;
    std::cin >> numCasos;
    for (int i = 0; i < numCasos; ++i)
        resuelveCaso();
   
   // para dejar todo como estaba al principio
#ifndef DOMJUDGE
   std::cin.rdbuf(cinbuf);
   system("PAUSE");
#endif
   return 0;
}
