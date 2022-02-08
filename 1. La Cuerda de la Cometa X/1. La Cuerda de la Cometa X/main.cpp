//Nombre: Diego Alejandro Rodriguez Pereira.
//Usuario Domjudge: 270.

// Comentario general sobre la solución,
// explicando cómo se resuelve el problema

/*
    Matematico
 
    matematico(j) = longitud[i]                 si longitud[i] == j
    matematico(j) = 0                           si matematico(j - longitud[i] == 0
    matematico(j) = matematico(j - longitud[i]) si matematico(j - longitud[i] != 0
 
    0 <= i < num_cordeles
    longitud[i] <= j <= longitud_deseada
 
 
    Ingeniero
    
    ingeniero[j] = infinito                         si ingeniero[j - longitud[i]] + 1 >= ingeniero[j]
    ingeniero[j] = ingeniero[j - longitud[i]  + 1   en otro caso
 
    
    Economista
 
    economista[j] = precio[i]                               si longitud[i] == j
    economista[j] = infinito                                si longitud[i] != j && economista[j-longitud[i]] + precio[i] >= economista[j]
    economista[j] = economista[j-longitud[i]] + precio[i]   en otro caso
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <string.h>

using namespace std;

const long long int MAX_INT = 99999999;

void resolver(long long int n_cordeles, long long int long_deseada, vector<long long int>& v_longitud, vector<long long int>& v_precio) {
    
    vector<long long int> math = vector<long long int>(long_deseada + 1, 0);
    vector<long long int> inge = vector<long long int>(long_deseada + 1, MAX_INT);
    vector<long long int> eco = vector<long long int>(long_deseada + 1, MAX_INT);
    
    math[0] = 1;
    inge[0] = 0;
    eco[0] = 0;
    
    for (long long int i = 0; i < n_cordeles; i++) {
        
        for (long long int j = long_deseada; j - v_longitud[i] >= 0; j--) {
            
            //Matemático
            if (math[j - v_longitud[i]] != 0) {
                
                math[j] = math[j - v_longitud[i]] + math[j];
            }
            
            //Ingeniero
            if (inge[j - v_longitud[i]] != MAX_INT && inge[j - v_longitud[i]] + 1 < inge[j]) {
                
                inge[j] = inge[j - v_longitud[i]] + 1;
            }
            
            //Economista
            if (eco[j - v_longitud[i]] != MAX_INT && (v_precio[i] + eco[j - v_longitud[i]] < eco[j])) {
                
                eco[j] = v_precio[i] + eco[j - v_longitud[i]];
            }
        }
    }
    
    if (math[long_deseada] > 0) {
        
        cout << "SI " << math[long_deseada] << " " << inge[long_deseada] << " " << eco[long_deseada] << endl;
    }
    else {
        
        cout << "NO" << endl;
    }
}

bool resuelveCaso() {
   
    
    long long int n_cordeles;
    long long int long_deseada;
    
    cin >> n_cordeles;
    cin >> long_deseada;
    
    if (!cin) {
        return false;
    }
    
    vector<long long int> v_longitud = vector<long long int>(n_cordeles, 0);
    vector<long long int> v_precio = vector<long long int>(n_cordeles, 0);
    
    for (long long int i = 0; i < n_cordeles; i++) {
        
        cin >> v_longitud[i];
        cin >> v_precio[i];
    }
    
    resolver(n_cordeles, long_deseada, v_longitud, v_precio);

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
