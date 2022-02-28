
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

/*int maraton(const vector<pelicula> &cartelera, vector<int> &sol, int num_peliculas) {
    
    //int count = 0;
    for (int i = 0; i < num_peliculas; i++) {
        
        int hora = cartelera[i].hora;
        int duracion = cartelera[i].duracion;
        
        int j = suma_duracion(hora, duracion);
        for (;j < MAX_TIEMPO; j++) {
            sol[j] = max(sol[j], sol[hora] + duracion);
        }
    }
    
    //cout << count << endl;
    
    return sol.back();
}*/
int maraton(const vector<pelicula> &cartelera, vector<int> &sol, int num_peliculas, int i) {
    
    if (sol[i] != -1) return sol[i];
    if (i == num_peliculas) {
        sol[i] = 0;
        return sol[i];
    }
    
    int k = i + 1;
    while (k < num_peliculas && cartelera[k].hora < suma_duracion(cartelera[i].hora, cartelera[i].duracion)) {
        k++;
    }
    
    sol[i] = max(maraton(cartelera, sol, num_peliculas, i + 1),
                 maraton(cartelera, sol, num_peliculas, k) + cartelera[i].duracion);
    
    return sol[i];
}

bool resuelveCaso() {

    //leer entrada
    int num_peliculas;
    cin >> num_peliculas;
   
    if (num_peliculas == 0)  // fin de la entrada
      return false;
    
    vector<pelicula> cartelera = vector<pelicula>(num_peliculas);
    char aux;
    int hora, minuto, duracion;
    for (int i = 0; i < num_peliculas; i++) {
        
        cin >> hora >> aux >> minuto >> duracion;
        
        cartelera[i].hora = hora*100 + minuto;
        cartelera[i].duracion = duracion;
    }
    
    vector<int> sol = vector<int>(num_peliculas + 1, -1);
    
    sort(cartelera.begin(), cartelera.end(), less<pelicula>());
    
    int res = maraton(cartelera, sol, num_peliculas, 0);
    
    cout << res << endl;

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
