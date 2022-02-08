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
#include "EntInf.h"

using namespace std;

void dianas (int valor, int n_sectores, vector<int> v_sectores, vector<vector<EntInf>> &matriz) {
    
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
    
    if (matriz[n_sectores][valor] != Infinito) {
        
        cout << matriz[n_sectores][valor] << ":";
        
        int i = n_sectores, j = valor;
        
        while (j > 0) {
            
            //if (matriz[i-1][j] >= matriz[i][j] && v_sectores[i-1] <= j && matriz[i][j - v_sectores[i-1]] < matriz[i][j]) {
            if (j >= v_sectores[i-1] && matriz[i][j - v_sectores[i-1]] + 1 == matriz[i][j]) {
            
                cout << " " << v_sectores[i-1];
                j = j - v_sectores[i-1];
            }
            else {
                
                i--;
            }
        }
    }
    else {
        
        cout << "Imposible";
    }
    
    cout << "\n";
}

bool resuelveCaso() {
    
    int valor;
    int n_sectores;
    
    cin >> valor;
    cin >> n_sectores;
    
    if (!cin) {
        return false;
    }
    
    vector<int> v_sectores = vector<int>(n_sectores, 0);
    
    for (int i = 0; i < n_sectores; i++) {
        
        cin >> v_sectores[i];
    }
    
    vector<vector<EntInf>> matriz(n_sectores + 1, vector<EntInf>(valor + 1, Infinito));
    
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
