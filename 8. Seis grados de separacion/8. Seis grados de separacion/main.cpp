
// Nombre y Apellidos
// Diego Alejandro
// Rodriguez Pereira

// Comentario general sobre la solución,
// explicando cómo se resuelve el problema

// En la solución he aplicado basicamente el algoritmo de floyd visto en clase.
// Coste en tiempo = O(num_personas^3) siendo num_personas el número de vértices en el grafo.
// Coste en espacio = O(num_personas) siendo num_personas el número de vértices en el grafo.

#include <iostream>
#include <fstream>
#include <vector>
#include "Matriz.h"
#include "EnterosInf.h"
#include <unordered_map>
#include <string>
#include <math.h>

using namespace std;

void floyd(int n_personas, Matriz<EntInf> &matrizC) {
    
    for (int k = 0; k < n_personas; k++) {
        for (int i = 0; i < n_personas; i++) {
            for (int j = 0; j < n_personas; j++) {
                
                EntInf temp = matrizC[i][k] + matrizC[k][j];
                
                if (temp < matrizC[i][j]) {
                    
                    matrizC[i][j] = temp;
                }
            }
        }
    }
}

bool resuelveCaso() {

    //leer entrada
    int n_personas;
    int n_relaciones;
    
    cin >> n_personas;
    cin >> n_relaciones;
   
    if (!std::cin)  // fin de la entrada
        return false;
    
    Matriz<EntInf> matrizG = Matriz<EntInf>(n_personas, n_personas, Infinito);
    unordered_map<string, int> hashmap;
    
    string a;
    string b;
    int count = 0;
    for (int i = 0; i < n_relaciones; i++) {
            
        cin >> a;
        cin >> b;
        
        if (hashmap.find(a) == hashmap.end()) {
            //hashmap[a] = 1;
            hashmap.insert((make_pair(a, count)));
            count++;
        }
        if (hashmap.find(b) == hashmap.end()) {
            hashmap.insert((make_pair(b, count)));
            count++;
        }
        
        //cout << "hash1 " << hashmap[a];
        //cout << " hash2 " << hashmap[b] << endl;
        
        matrizG[hashmap[a]][hashmap[b]] = 1;
        matrizG[hashmap[b]][hashmap[a]] = 1;
    }
    
    int i = 0, j = 0;
    while (i < n_personas) {
        matrizG[i][j] = 0;
        i++;
        j++;
    }
    
    Matriz<EntInf> matrizC = Matriz<EntInf>(n_personas, n_personas);
    matrizC = matrizG;
    
    EntInf maxi = 0;
    
    floyd(n_personas, matrizC);
    
    //cout << matrizC;
    
    bool desc = false;
    for (int i = 0; i < n_personas && !desc; i++) {
        for (int j = 0; j < n_personas && !desc; j++) {
        
            if (matrizC[i][j] == Infinito) {
                desc = true;
            }
            else {
                
                if (matrizC[i][j] > maxi) {
                    
                    maxi = matrizC[i][j];
                }
            }
        }
    }
    
    //escribir resultado
    
    if (!desc) {
        
        cout << maxi << endl;
    }
    else {
        
        cout << "DESCONECTADA" << endl;
    }
    
    //cout << endl;
   
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

