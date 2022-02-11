
// Nombre y Apellidos

// Comentario general sobre la solución,
// explicando cómo se resuelve el problema

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;


void cazatesoros(int oxigeno, int n_cofres, vector<int> &v_profundidad, vector<int> &v_oro, vector<vector<int>> &matriz, int &maxi, int &posi, int &posj) {
    
    matriz[0][0] = 0;
    int consumo;
    int oro;
    for (int i = 1; i <= n_cofres; i++) {
        
        matriz[i][0] = 0;
        consumo = 3*v_profundidad[i-1];
        oro = v_oro[i-1];
        for (int j = 0; j <= oxigeno; j++) {
            
            if (j >= consumo && matriz[i-1][j - consumo] != -1) {
                
                matriz[i][j] = max(matriz[i-1][j], matriz[i-1][j - consumo] + oro);
                
                if (matriz[i][j] > maxi) {
                    
                    maxi = matriz[i][j];
                    posi = i;
                    posj = j;
                }
            }
            else {
                
                matriz[i][j] = matriz[i-1][j];
            }
        }
    }
}

bool resuelveCaso() {
   
    int oxigeno;
    
    cin >> oxigeno;
    
   if (!cin)  // fin de la entrada
      return false;
    
    int n_cofres;
    
    cin >> n_cofres;
    
    vector<int> v_profundidad = vector<int>(n_cofres);
    vector<int> v_oro = vector<int>(n_cofres);
    for (int i = 0; i < n_cofres; i++) {
        
        cin >> v_profundidad[i];
        cin >> v_oro[i];
    }
    
    vector<vector<int>> matriz(n_cofres+1, vector<int>(oxigeno + 1, -1));
    int maxi = 0;
    
    int i;
    int j;
    cazatesoros(oxigeno, n_cofres, v_profundidad, v_oro, matriz, maxi, i , j);
    
    int contador = 0;
    vector<int> indices;
    while (i > 0 && j > 0) {
        
        if (matriz[i][j] > matriz[i-1][j]) {
            
            indices.push_back(i - 1);
            j = j - 3*v_profundidad[i - 1];
            contador++;
        }
        
        i--;
    }
    
    cout << maxi << endl;
    cout << contador << endl;
    
    for (int i = indices.size() - 1; i >= 0; i--) {
        
        cout << v_profundidad[indices[i]] << " " << v_oro[indices[i]] << endl;
    }
    
    cout << "---" << endl;
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
