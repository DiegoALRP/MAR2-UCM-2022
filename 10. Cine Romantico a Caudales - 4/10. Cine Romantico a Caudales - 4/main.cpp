
// Nombre y Apellidos
// Diego Alejandro
// Rodriguez Pereira

// Comentario general sobre la solución,
// explicando cómo se resuelve el problema

//pelis(i, j) = maximo(pelis(i + 1, j), pelis(i + 1, j + hora_fin(i)))

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

const int DESCANSO = 10;

struct pelicula {
    
    int hora;
    int duracion;
    
    bool operator > (const pelicula &peli) const {
        
        if (hora > peli.hora) {
            return true;
        }
        else {
            return false;
        }
    }
    
    bool operator < (const pelicula &peli) const {
        
        if (hora > peli.hora) {
            return false;
        }
        else {
            return true;
        }
    }
};

int suma_duracion(int hora, int duracion) {
    
    hora += duracion/60*100;
    hora += duracion%60;
    
    return hora;
}

/*
 *
 *  maraton(i,j) es el máximo de minutos que se puede obtener mirando
 *  peliculas, de la pelicula 0 a la pelicula i - 1, antes de la hora j.
 *
 *  0 <= i < num_peliculas
 *  0 <= j <= 24 horas
 *
 *  Caso base:
 *
 *      maraton(num_peliculas, j) = 0
 *
 *  Casos recursivos:
 *
 *      maraton(i, j) = maraton(i + 1, j)       si j > hora_inicio(i).
 *      maraton(i, j) = maximo(maraton(i + 1, j), maraton(i + 1, hora_fin(i) + 10min) + duracion(i))
 */


int maraton(const vector<pelicula> &cartelera, vector<vector<int>> &matriz, int num_peliculas, int i, int pelicula_actual) {
    
    if (matriz[i][pelicula_actual] == -1) {
        
        if (i == num_peliculas) matriz[i][pelicula_actual] = 0;
        else {
        
            pelicula peli = cartelera[pelicula_actual];
            int hora_actual = peli.hora + peli.duracion + DESCANSO;
            
            if (cartelera[i].hora <= hora_actual) {
                
                matriz[i][pelicula_actual] = maraton(cartelera, matriz, num_peliculas, i + 1, pelicula_actual);
            }
            else {
                
                int sin_pelicula = maraton(cartelera, matriz, num_peliculas, i + 1, pelicula_actual);

                int duracion = cartelera[i].duracion;
                int con_pelicula = maraton(cartelera, matriz, num_peliculas, i + 1, i) + duracion;
                
                if (sin_pelicula > con_pelicula) {
                    matriz[i][pelicula_actual] = sin_pelicula;
                }
                else {
                    matriz[i][pelicula_actual] = con_pelicula;
                }
            }
        }
    }
    
    return matriz[i][pelicula_actual];
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
    
    sort(cartelera.begin(), cartelera.end(), less<pelicula>());
    
    vector<vector<int>> matriz(num_peliculas + 1, vector<int> (num_peliculas + 1, -1));
    
    int bonita_la_vida = maraton(cartelera, matriz, num_peliculas, 0, 0);
    
    cout << bonita_la_vida << endl;
    
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
