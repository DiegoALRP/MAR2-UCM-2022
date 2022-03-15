
// Nombre y Apellidos
// Diego Alejandro
// Rodriguez Pereira

// Comentario general sobre la solución,
// explicando cómo se resuelve el problema

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;


void resuelveCaso() {

    //leer entrada
    int n_plazas, m_comensales;
    cin >> n_plazas >> m_comensales;
    
    vector<vector<double>> distancias(n_plazas, vector<double>(n_plazas));
    for (int i = 0; i < n_plazas; i++) {
        for (int j = 0; j < n_plazas; j++) {
            cin >> distancias[i][j];
        }
    }
    
    vector<vector<int>> allegados(m_comensales, vector<int>(m_comensales));
    for (int i = 0; i < m_comensales; i++) {
        for (int j = 0; j < m_comensales; j++) {
            cin >> allegados[i][j];
        }
    }

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
