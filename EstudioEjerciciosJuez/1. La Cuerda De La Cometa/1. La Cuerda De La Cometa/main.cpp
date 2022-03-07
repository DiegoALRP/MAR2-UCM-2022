
// Nombre y Apellidos
// Diego Alejandro
// Rodriguez Pereira

// Comentario general sobre la solución,
// explicando cómo se resuelve el problema

/*
 * matematico
 *
 * mate(i, j): mate(i, j - long(i)] + 1
 */

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int matematico(int num_cordeles, int long_deseada, const vector<int> &v_longitud, const vector<int> &v_precio) {
    
    vector<vector<int>> matriz_mate(num_cordeles + 1, vector<int>(long_deseada + 1, 0));
    
    matriz_mate[0][0] = 1;
    for (int i = 1; i < num_cordeles + 1; i++) {
        matriz_mate[i][0] = 1;
        int long_actual = v_longitud[i - 1];
        for (int j = long_deseada; j - long_actual >= 0; j--) {
            
            if (matriz_mate[i-1][j - long_actual] != 0) {
                matriz_mate[i][j] = matriz_mate[i - 1][j - long_actual] + matriz_mate[i - 1][j];
            }
            /*
            if (j < long_deseada) {
                matriz_mate[i][j] = matriz_mate[i - 1][j];
            }
            else {
                matriz_mate[i][j] = matriz_mate[i - 1][j - long_actual] + matriz_mate[i][j];
            }*/
            
            
        }
    }
    return matriz_mate[num_cordeles][long_deseada];
}

bool resuelveCaso() {

    //leer entrada
    int num_cordeles;
    int longitud_deseada;
    
    cin >> num_cordeles >> longitud_deseada;
   
    if (!std::cin)  // fin de la entrada
      return false;
    
    vector<int> v_longitud = vector<int>(num_cordeles);
    vector<int> v_precio = vector<int>(longitud_deseada);
    for (int i = 0; i < num_cordeles; i++) {
        
        cin >> v_longitud[i];
        cin >> v_precio[i];
    }
    
    int res_mat = matematico(num_cordeles, longitud_deseada, v_longitud, v_precio);
    
    cout << res_mat << endl;

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
