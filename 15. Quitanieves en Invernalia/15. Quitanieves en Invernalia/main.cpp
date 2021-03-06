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

struct Nodo {
    vector<int> sol; //sol[i]=j contiene el conjunto solucion donde al carro i se le asigna la carretera j
    vector<bool> marca; //vector de marcas que contiene informacion sobre si se ha enviado un quitanieves a la carretera i o no.
    int k; // carro actual
    double calidad; //Calidad actual
    double calidad_estimada; //Cota superior, estimacion optimista
    bool operator < (Nodo const& otro) const {
        return otro.calidad_estimada > calidad_estimada;
    }
};

void quitanieves_rp(const vector<vector<int>> &calidades, const vector<int> &anchura_carro, const vector<int> &anchura_carretera, const vector<int> &max_acum, vector<int> &mejor_sol, int &mejor_calidad, int n, int m) {
    
    Nodo Y;
    Y.sol = vector<int>(n);
    Y.marca = vector<bool>(m, false);
    Y.k = -1;
    Y.calidad = 0;
    Y.calidad_estimada = max_acum[0];
    priority_queue<Nodo> cola;
    cola.push(Y);
    mejor_calidad = 0;
    
    while (!cola.empty() && cola.top().calidad_estimada > mejor_calidad) {
        
        Y = cola.top();
        cola.pop();
        Nodo X(Y);
        X.k++;
        
        //Caso en el que se envia una quitanieves a alguna de las m carreteras
        for (int i = 0; i < m; i++) {
            
            if (!Y.marca[i] && anchura_carro[X.k] <= anchura_carretera[i]) {
                X.sol[X.k] = i;
                X.marca[i] = true;
                X.calidad = Y.calidad + calidades[X.k][i];
                X.calidad_estimada = X.calidad + max_acum[X.k+1];
                
                if (X.calidad_estimada > mejor_calidad) {
                    if (X.k == n - 1) {
                        mejor_sol = X.sol;
                        mejor_calidad = X.calidad;
                    }
                    else {
                        cola.push(X);
                    }
                }
                X.marca[i] = false;
            }
        }
        
        //Caso en el que no se envia el quitanieves a ninguna carretera
        X.calidad = Y.calidad;
        X.calidad_estimada = X.calidad + max_acum[X.k+1];
        
        if (X.calidad_estimada > mejor_calidad) {
            if (X.k == n - 1) {
                mejor_sol = X.sol;
                mejor_calidad = X.calidad;
            }
            else {
                cola.push(X);
            }
        }
    }
}


void resuelveCaso() {

    //leer entrada
    int n_carros, m_carreteras;
    cin >> n_carros;
    cin >> m_carreteras;
    
    int min = 99999;
    vector<int> anchura_carro(n_carros);
    for (int i = 0; i < n_carros; i++) {
        cin >> anchura_carro[i];
        if (anchura_carro[i] < min) {
            min = anchura_carro[i];
        }
    }
    
    int maxo = -1;
    vector<int> anchura_carretera(m_carreteras);
    for (int i = 0; i < m_carreteras; i++) {
        cin >> anchura_carretera[i];
        if (anchura_carretera[i] > maxo) {
            maxo = anchura_carretera[i];
        }
    }
    
    vector<int> maxi(n_carros, -1);
    vector<vector<int>> calidades(n_carros, vector<int>(m_carreteras));
    for (int i = 0; i < n_carros; i++) {
        for (int j = 0; j < m_carreteras; j++) {
            cin >> calidades[i][j];
            if (calidades[i][j] > maxi[i]) {
                maxi[i] = calidades[i][j];
            }
        }
        
        
    }
    
    vector<int> max_acum(n_carros + 1, 0);
    for (int i = n_carros - 1; i >= 0; i--) {
        max_acum[i] = maxi[i] + max_acum[i + 1];
    }
    
    vector<int> mejor_sol(n_carros);
    int mejor_calidad = 0;
    
    quitanieves_rp(calidades, anchura_carro, anchura_carretera, max_acum, mejor_sol, mejor_calidad, n_carros, m_carreteras);
    
    cout << mejor_calidad << endl;
    //escribir resultado
}

int main() {
   // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
   std::ifstream in("casos.txt");
   auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif
   
    int num_casos;
    cin >> num_casos;
    int i = 0;
    while (i < num_casos) {
        resuelveCaso();
        i++;
    }
   
   // para dejar todo como estaba al principio
#ifndef DOMJUDGE
   std::cin.rdbuf(cinbuf);
   system("PAUSE");
#endif
   return 0;
}
