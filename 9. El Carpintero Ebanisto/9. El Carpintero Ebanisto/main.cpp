
// Nombre y Apellidos
// Diego Alejandro
// Rodriguez Pereira

// Comentario general sobre la solución,
// explicando cómo se resuelve el problema

#include <iostream>
#include <fstream>
#include <vector>
#include "EnterosInf.h"

using namespace std;

const int max_int = Infinito._intInf;

int ayuda_por_favor(int tam_tabla, int num_cortes, const vector<int> &cortes, vector<vector<int>> &esfuerzo) {
    
    for (int d = 1; d <= num_cortes + 1; d++) {
        for (int i = 0; i <= num_cortes + 1 - d; i++) {
            int j = i + d;
            
            if (j == i + 1) {
                
                esfuerzo[i][j] = 0;
            }
            else {
                esfuerzo[i][j] = max_int;
                for (int k = i + 1; k < j; k++) {
                    
                    /*if (j > num_cortes + 1 || i > num_cortes + 1 || k > num_cortes + 1) {
                        
                        cout << "Error i: " << i << endl;
                        cout << "Error j: " << j << endl;
                        cout << "Error k: " << k << endl;
                        continue;
                    }*/
                    int temp = esfuerzo[i][k] + esfuerzo[k][j] + 2*(cortes[j] - cortes[i]);
                    //if (temp < max_int && temp < esfuerzo[i][j]) {
                    if (temp < esfuerzo[i][j]) {
                        esfuerzo[i][j] = temp;
                    }
                }
            }
        }
    }
    
    return esfuerzo[0][num_cortes + 1];
}

bool resuelveCaso() {

    //leer entrada
    int tam_tabla, num_cortes;
    
    cin >> tam_tabla >> num_cortes;
   
    if (tam_tabla == 0 && num_cortes == 0)  // fin de la entrada
      return false;
    
    vector<int> cortes = vector<int>(num_cortes + 2, 0);
    for (int i = 1; i <= num_cortes; i++) {
        
        cin >> cortes[i];
    }
    
    cortes[0] = 0;
    cortes[num_cortes + 1] = tam_tabla;
    
    vector<vector<int>> esfuerzo(num_cortes + 2, vector<int> (num_cortes + 2, 0));
    
    int res = ayuda_por_favor(tam_tabla, num_cortes, cortes, esfuerzo);
    
    //cout << "res: " << res << endl;
    cout << res << endl;

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
