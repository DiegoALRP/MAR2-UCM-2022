
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

/*int bolsillo(const vector<moneda> &v_moneda, int num_tipos_monedas, vector<vector<int>> &matriz, int i, int j, int jj) {
    
    if (j < 0) return infinito;
    if (matriz[i][j] != infinito) return matriz[i][j];
    if (i == num_tipos_monedas) {
        matriz[i][j] = infinito;
    }
    else if (j == 0) {
        matriz[i][j] = 0;
    }
    else {
        
        int valor = v_moneda[i].valor;
        int cantidad = v_moneda[i].cantidad;
        
        if (cantidad + 1 == jj || valor > j) {
            matriz[i][j] = bolsillo(v_moneda, num_tipos_monedas, matriz, i+1, j, 0);
        }
        else {
            
            int a = bolsillo(v_moneda, num_tipos_monedas, matriz, i + 1, j, 0);
            int b = bolsillo(v_moneda, num_tipos_monedas, matriz, i, j - valor, jj + 1);
            
            if (b != infinito) b += 1;
            
            if (a < b) {
                matriz[i][j] = a;
            }
            else {
                matriz[i][j] = b;
            }
        }
    }
    
    return matriz[i][j];
}*/

void bolsillo(const vector<moneda> &v_moneda, int num_tipos_monedas, vector<vector<int>> &matriz, int precio_coche) {
    
    matriz[0][0] = 0;
    for (int i = num_tipos_monedas - 1; i >= 0; i--) {
        
        matriz[i][0] = 0;
        
        int valor = v_moneda[i].valor;
        int cantidad = v_moneda[i].cantidad;
        for (int j = 0; j <= precio_coche && j <= valor*cantidad; j++) {
            
            int a = matriz[i+1][j];
            int b = matriz[i][j - valor];
            
            if (a < b) {
                if (a == infinito) matriz[i][j] == infinito;
                else matriz[i][j] = a + 1;
            }
            else {
                if (b == infinito) matriz[i][j] = infinito;
                else matriz[i][j] = b + 1;
            }
            
            //matriz[i][valor*j] =
        }
    }
}


bool resuelveCaso() {

    //leer entrada
    int num_tipos_monedas;
    
    cin >> num_tipos_monedas;
   
    if (!std::cin)  // fin de la entrada
      return false;

    vector<moneda> v_moneda = vector<moneda>(num_tipos_monedas);
    
    for (int i = 0; i < num_tipos_monedas; i++) {
        
        cin >> v_moneda[i].valor;
    }
    
    for (int i = 0; i < num_tipos_monedas; i++) {
        
        cin >> v_moneda[i].cantidad;
    }
    
    sort(v_moneda.begin(), v_moneda.end(), greater<moneda>());
    
    int precio_coche;
    
    cin >> precio_coche;
    //escribir resultado
    
    vector<vector<int>> matriz(num_tipos_monedas + 1, vector<int>(precio_coche + 1, infinito));
    
    bolsillo(v_moneda, num_tipos_monedas, matriz, precio_coche);
    
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
