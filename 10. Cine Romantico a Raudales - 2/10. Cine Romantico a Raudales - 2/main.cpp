
// Nombre y Apellidos
// Diego Alejandro
// Rodriguez Pereira

// Comentario general sobre la solución,
// explicando cómo se resuelve el problema

//pelis(i, j) = maximo(pelis(i + 1, j), pelis(i + 1, j + hora_fin(i)))

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

struct pelicula {
    
    int hora;
    int minutos;
    int duracion;
    
    bool operator > (const pelicula &peli) const {
        
        if (hora > peli.hora) {
            return false;
        }
        else if (hora == peli.hora && minutos > peli.minutos) {
            return false;
        }
        else {
            return true;
        }
    }
};


bool resuelveCaso() {

    //leer entrada
    
    int num_peliculas;
    
    cin >> num_peliculas;
   
    if (num_peliculas == 0)  // fin de la entrada
      return false;
    
    vector<pelicula> cartelera = vector<pelicula>(num_peliculas);
    char aux;
    
    for (int i = 0; i < num_peliculas; i++) {
        
        cin >> cartelera[i].hora >> aux >> cartelera[i].minutos >> cartelera[i].duracion;
    }
    
    sort(cartelera.begin(), cartelera.end(), greater<pelicula>());
    
    int bonita_la_vida;
    
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
