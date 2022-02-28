
// Nombre y Apellidos
// Diego Alejandro
// Rodriguez Pereira

// Comentario general sobre la solución,
// explicando cómo se resuelve el problema

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int vacas(const vector<int> &comida, vector<vector<int>> &matriz, int cubos, int i, int j) {
    
    if (matriz[i][j] != -1) {
        return matriz[i][j];
    }
    if (i > j) {
        
        matriz[i][j] = 0;
    }
    else if (i == j) {
        
        matriz[i][j] = comida[i];
    }
    else if (i + 1 == j) {
        
        if (comida[i] > comida[j]) {
            matriz[i][j] = comida[i];
        }
        else {
            matriz[i][j] = comida[j];
        }
    }
    else {
        
        int izq_1 = comida[i+1];
        int der_1 = comida[j];
        int a;
        if (izq_1 > der_1) {
            a = vacas(comida, matriz, cubos, i + 2, j) + comida[i];
        }
        else {
            a = vacas(comida, matriz, cubos, i + 1, j - 1) + comida[i];
        }
        
        int izq_2 = comida[i];
        int der_2 = comida[j - 1];
        int b;
        if (izq_2 > der_2) {
            b = vacas(comida, matriz, cubos, i + 1, j - 1) + comida[j];
        }
        else {
            b = vacas(comida, matriz, cubos, i, j - 2) + comida[j];
        }
        
        if (a > b) {
            matriz[i][j] = a;
        }
        else {
            matriz[i][j] = b;
        }
    }
    
    return matriz[i][j];
}

bool resuelveCaso() {

    //leer entrada
    int cubos;
    cin >> cubos;
   
    if (cubos == 0)  // fin de la entrada
      return false;
    
    vector<int> comida = vector<int>(cubos);
    for (int i = 0; i < cubos; i++) {
        
        cin >> comida[i];
    }
    
    vector<vector<int>> matriz(cubos, vector<int>(cubos, -1));

    //escribir resultado
    
    int res = vacas(comida, matriz, cubos, 0, cubos - 1);
    
    cout << res << endl;
   
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
