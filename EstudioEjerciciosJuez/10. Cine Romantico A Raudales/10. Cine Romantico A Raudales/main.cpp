
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

const int DESCANSO = 10;

struct pelicula {
    
    int hora;
    int duracion;
    
    bool operator < (const pelicula &peli) const {
        
        if (hora < peli.hora) {
            return true;
        }
        return false;
    }
};

int suma_duracion(int hora, int duracion) {
    
    duracion += DESCANSO;
    int m = hora%100;
    int h = hora - m;
    m += duracion;
    
    return h + m/60*100 + m%60;
}

int maraton(int i, int n, const vector<pelicula> &cartelera, vector<int> &sol) {
    
    if (sol[i] != -1) return sol[i];
    
    if (i == n) {
        sol[i] = 0;
        return sol[i];
    }
        
    int k = i+1;
    int hora_fin_i = suma_duracion(cartelera[i].hora, cartelera[i].duracion);
    while (k < n && cartelera[k].hora < hora_fin_i) {
        k++;
    }
    
    int a = maraton(k, n, cartelera, sol) + cartelera[i].duracion;
    int b = maraton(i+1, n, cartelera, sol);
    sol[i] = max(a, b);
    
    return sol[i];
}

bool resuelveCaso() {

    //leer entrada
    int n;
    cin >> n;
   
    if (n == 0)  // fin de la entrada
      return false;
    
    vector<pelicula> cartelera = vector<pelicula>(n);
    char aux;
    int hora, minuto, duracion;
    for (int i = 0; i < n; i++) {
        
        cin >> hora >> aux >> minuto >> duracion;
        
        cartelera[i].hora = hora*100 + minuto;
        cartelera[i].duracion = duracion;
    }
    
    vector<int> sol = vector<int>(n + 1, -1);
    
    sort(cartelera.begin(), cartelera.end(), less<pelicula>());

    cout << maraton(0, n, cartelera, sol) << endl;
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
