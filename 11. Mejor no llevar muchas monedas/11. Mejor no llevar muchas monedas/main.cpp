
// Nombre y Apellidos
// Diego Alejandro
// Rodriguez Pereira

// Comentario general sobre la solución,
// explicando cómo se resuelve el problema

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

const int infinito = 99999;

struct moneda {
    
    int valor;
    int cantidad;
    
    bool operator > (const moneda &mone) const {
        
        if (valor > mone.valor) {
            return true;
        }
        else {
            return false;
        }
    }
};


bool resuelveCaso() {

    //leer entrada
    int num_tipos_monedas;
    cin >> num_tipos_monedas;
   
    if (!std::cin)  // fin de la entrada
      return false;

    vector<moneda> v_moneda = vector<moneda>(num_tipos_monedas);
    
    for (int i = 0; i < num_tipos_monedas; i++) cin >> v_moneda[i].valor;
    for (int i = 0; i < num_tipos_monedas; i++) cin >> v_moneda[i].cantidad;
    
    int precio_coche;
    cin >> precio_coche;
    
    vector<vector<int>> matriz(num_tipos_monedas + 1, vector<int>(precio_coche + 1, infinito));
    
    //bolsillo(v_moneda, num_tipos_monedas, matriz, precio_coche);
    
    cout << matriz[0][precio_coche] << endl;
    
    //cout << res << endl;
   
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
