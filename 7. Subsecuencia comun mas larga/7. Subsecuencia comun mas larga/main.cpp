
// Nombre y Apellidos
// Diego Alejandro
// Rodriguez Pereira

// Comentario general sobre la solución,
// explicando cómo se resuelve el problema

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

int subcomun(int i, int j, const string &word_a, int long_a, const string &word_b, int long_b, vector<vector<int>> &matriz, int &maxi) {
    
    if (matriz[i][j] != -1) {
        
        return matriz[i][j];
    }
    
    if (i == long_a || j == long_b) {
        
        matriz[i][j] = 0;
    }
    else if (word_a[i] == word_b[j]) {
        
        matriz[i][j] = subcomun(i + 1, j + 1, word_a, long_a, word_b, long_b, matriz, maxi) + 1;
    }
    else {
        
        matriz[i][j] = max(subcomun(i + 1, j, word_a, long_a, word_b, long_b, matriz, maxi), subcomun(i, j + 1, word_a, long_a, word_b, long_b, matriz, maxi));
    }
    
    if (matriz[i][j] > maxi) {
        
        maxi = matriz[i][j];
    }
    
    return matriz[i][j];
}

void reconstruye(int i, int j, string &res, const string &word_a, int long_a, const string &word_b, int long_b, vector<vector<int>> &matriz) {
    
    if (i == long_a || j == long_b) return;
    
    else if (word_a[i] == word_b[j]) {
        
        res.push_back(word_b[j]);
        reconstruye(i + 1, j + 1, res, word_a, long_a, word_b, long_b, matriz);
    }
    else if (matriz[i][j+1] == matriz[i][j]) {
        
        //res.push_back(word_b[j-1]);
        reconstruye(i, j+1, res, word_a, long_a, word_b, long_b, matriz);
    }
    else {
        
        //res.push_back(word_a[i-1]);
        reconstruye(i+1, j, res, word_a, long_a, word_b, long_b, matriz);
    }
}

bool resuelveCaso() {
   
    string word_a;
    string word_b;
    
    cin >> word_a;
   
   if (!cin)  // fin de la entrada
      return false;
    
    cin >> word_b;
    
    int long_a = (int) word_a.size();
    int long_b = (int) word_b.size();
    
    vector<vector<int>> matriz(long_a + 1, vector<int>(long_b + 1, -1));
    int maxi = 0;
    
    subcomun(0, 0, word_a, long_a, word_b, long_b, matriz, maxi);
    
    cout << maxi << endl;
    
    string res;
    
    reconstruye(0, 0, res, word_a, long_a, word_b, long_b, matriz);
    
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
