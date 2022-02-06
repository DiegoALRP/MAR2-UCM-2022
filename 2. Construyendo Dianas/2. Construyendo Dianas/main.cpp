//
//  main.cpp
//  2. Construyendo Dianas
//
//  Created by Diego Alejandro Rodriguez Pereira on 5/2/22.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

const long long int MAX_INT = 1000000000;

void dianas (int valor, int n_sectores, vector<long long int> v_sectores, vector<vector<long long int>> &matriz) {
    
    matriz[0][0] = 0;
    
    for (int i = 1; i <= n_sectores; i++) {
        
        matriz[i][0] = 0;
        
        for (int j = 1; j <= valor; j++) {
            
            if (v_sectores[i-1] > j) {
                
                matriz[i][j] = matriz[i - 1][j];
            }
            else {
                
                matriz[i][j] = min(matriz[i-1][j], matriz[i][j - v_sectores[i-1]] + 1);
            }
        }
    }
    
    cout << matriz[n_sectores][valor] << endl;
    
    if (matriz[n_sectores][valor] != MAX_INT) {
        
        int i = n_sectores, j = valor;
        
        while (j > 0) {
            
            if (v_sectores[i-1] <= j && matriz[i][j] != matriz[i-1][j]) {
                
                cout << v_sectores[i] << " ";
                j = j - v_sectores[i];
            }
            else {
                
                i--;
            }
        }
    }
    else {
        
        cout << "imposible" << endl;
    }
}

bool resuelveCaso() {
    
    int valor;
    int n_sectores;
    
    cin >> valor;
    cin >> n_sectores;
    
    if (!cin) {
        return false;
    }
    
    vector<long long int> v_sectores = vector<long long int>(n_sectores, 0);
    
    for (int i = 0; i < n_sectores; i++) {
        
        cin >> v_sectores[i];
    }
    
    vector<vector<long long int>> matriz(n_sectores + 1, vector<long long int>(valor + 1, MAX_INT));
    
    dianas(valor, n_sectores, v_sectores, matriz);
    
    return true;
}

int main() {
    
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
