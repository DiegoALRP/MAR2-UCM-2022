//Nombre: Diego Alejandro Rodriguez Pereira.
//Usuario Domjudge: 270.

// Comentario general sobre la solución,
// explicando cómo se resuelve el problema

#include <iostream>
#include <fstream>
#include <vector>
#include <string.h>

using namespace std;

const long long int MAX_INT = 1000000000;
// función que resuelve el problema
// comentario sobre el coste, O(f(N)), donde N es ...
/*Solucion resolver(Datos datos) {
}*/

void resolver(int n_cordeles, int long_deseada, vector<long long int> v_longitud, vector<long long int> v_precio) {
    
    vector<long long int> math = vector<long long int>(long_deseada + 1, 0);
    vector<long long int> inge = vector<long long int>(long_deseada + 1, MAX_INT);
    vector<long long int> eco = vector<long long int>(long_deseada + 1, MAX_INT);
    
    math[0] = 0;
    
    for (int i = 0; i < n_cordeles; i++) {
        
        math[v_longitud[i]]++;
        
        for (int j = long_deseada; j - v_longitud[i] >= 0; j--) {
            
            if (math[j - v_longitud[i]] != 0) {
                
                //math[j] = math[j - v_longitud[i]] + 1;
                math[j]++;
            }
            
            if (eco[j - v_longitud[i]] != MAX_INT && (v_precio[i] + eco[j - v_longitud[i]] < eco[j])) {
                
                eco[j] = v_precio[i] + eco[j - v_longitud[i]];
            }
            
            if (inge[j - v_longitud[i]] + 1 < inge[j]) {
                
                inge[j] = inge[j - v_longitud[i]] + 1;
            }
        }
        
        if (v_precio[i] < eco[v_longitud[i]]) {
            
            eco[v_longitud[i]] = v_precio[i];
        }
        
        inge[v_longitud[i]] = 1;
        //math[v_longitud[i]]++;
    }
    
    if (math[long_deseada] > 0) {
        
        cout << "SI " << math[long_deseada] << " " << inge[long_deseada] << " " << eco[long_deseada] << endl;
    }
    else {
        
        cout << "NO" << endl;
    }
    
    /*cout << "matematico: " << math[long_deseada] << endl;
    cout << "ingeniero : " << inge[long_deseada] << endl;
    cout << "economista: " << eco[long_deseada] << endl;*/
}

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
   
   // leer los datos de la entrada
    
    int n_cordeles;
    int long_deseada;
    
    cin >> n_cordeles;
    cin >> long_deseada;
    
    if (!cin) {
        return false;
    }
    
    vector<long long int> v_longitud = vector<long long int>(n_cordeles, 0);
    vector<long long int> v_precio = vector<long long int>(n_cordeles, 0);
    
    for (int i = 0; i < n_cordeles; i++) {
        
        cin >> v_longitud[i];
        cin >> v_precio[i];
    }
    
    resolver(n_cordeles, long_deseada, v_longitud, v_precio);
    //Solucion sol = resolver(datos);

    // escribir sol

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
