
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
};

/*int bolsillo(const vector<moneda> &v_moneda, vector<int> &sol, int precio_coche, int i, int j) {
    
    
    if ((i == 0 && j == 0) || j == 0) {
        sol[j] = 0;
        return 0;
    }
    if (i == 0) {
        sol[j] = infinito;
        return infinito;
    }
    //if (sol[j] != infinito) return sol[j];
    
    int valor = v_moneda[i-1].valor;
    int cantidad = v_moneda[i-1].cantidad;
    
    int a = bolsillo(v_moneda, sol, precio_coche, i - 1, j);
    
    int k = 1;
    while (k <= cantidad && j - valor*k >= 0) {
        
        int b = bolsillo(v_moneda, sol, precio_coche, i - 1, j - valor*k);
        if (b != infinito) {
            b += k;
        }
        sol[j] = min(a, b);
        k++;
    }
    
    return sol[j];
}*/

/*int bolsillo(const vector<moneda> &v_moneda, vector<vector<int>> &sol2, int precio_coche, int num_tipos_monedas) {
    
    sol2[0][0] = 0;
    
    for (int i = 1; i <= num_tipos_monedas; i++) {
        
        sol2[i][0] = 0;
        
        int valor = v_moneda[i-1].valor;
        int cantidad = v_moneda[i-1].cantidad;
        
        for (int j = precio_coche; j >= 0; j--) {
            
            if (valor > j) {
                sol2[i][j] = sol2[i-1][j];
            }
            for (int k = 1; k <= cantidad && k*valor <= j; k++) {
                
                int a = sol2[i-1][j];
                int b =sol2[i-1][j - k*valor] + k;
                
                sol2[i][j] = min(sol2[i-1][j], sol2[i-1][j - k*valor] + k);
            }
        }
    }
    
    return sol2[num_tipos_monedas][precio_coche];
}*/

int bolsillo(const vector<moneda> &v_moneda, vector<int> &sol3, int precio_coche, int num_tipos_monedas) {
    
    sol3[0] = 0;
    
    for (int i = 1; i <= num_tipos_monedas; i++) {
        
        //sol2[0] = 0;
        
        int valor = v_moneda[i-1].valor;
        int cantidad = v_moneda[i-1].cantidad;
        
        for (int j = precio_coche; j >= 0; j--) {
            
            if (valor > j) {
                sol3[j] = sol3[j];
            }
            for (int k = 1; k <= cantidad && k*valor <= j; k++) {
                
                int a = sol3[j];
                int b = sol3[j - k*valor];
                if (b != infinito) b += k;
                
                sol3[j] = min(a, b);
            }
        }
    }
    
    return sol3[precio_coche];
}

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
    
    //vector<int> sol = vector<int>(precio_coche + 1, infinito);
    //vector<vector<int>> sol2(num_tipos_monedas + 1, vector<int>(precio_coche + 1, infinito));
    vector<int> sol3 = vector<int>(precio_coche + 1, infinito);
    
    //int res = bolsillo(v_moneda, sol, precio_coche, num_tipos_monedas, precio_coche);
    //int res = bolsillo(v_moneda, sol2, precio_coche, num_tipos_monedas);
    int res = bolsillo(v_moneda, sol3, precio_coche, num_tipos_monedas);
    
    if (res != infinito) {
        cout << "SI " << res << endl;
    }
    else {
        cout << "NO" << endl;
    }
   
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
