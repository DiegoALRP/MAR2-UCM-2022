
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

/*void suma_duracion(int &hora, int duracion) {
    
    hora += duracion/60*100;
    hora += duracion%60;
}*/
int suma_duracion(int hora, int duracion) {
    
    duracion += 10;
    int m = hora%100;
    int h = hora - m;
    m += duracion;
    
    return h + m/60*100 + m%60;
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


int maraton(const vector<pelicula> &cartelera, vector<vector<int>> &matriz, int num_peliculas, int i, int hora_actual) {
    
    if (matriz[i][hora_actual] != 0) return matriz[i][hora_actual];
    if (matriz[i][hora_actual] == 0) {
        
        if (i == num_peliculas) matriz[i][hora_actual] = 0;
        
        else if (cartelera[i].hora <= hora_actual) {
            
            matriz[i][hora_actual] = maraton(cartelera, matriz, num_peliculas, i + 1, hora_actual);
        }
        else {
            
            int sin_pelicula_actual = maraton(cartelera, matriz, num_peliculas, i + 1, hora_actual);
            
            int hora_fin = cartelera[i].hora;
            int duracion = cartelera[i].duracion;
            hora_fin = suma_duracion(hora_fin, duracion);
            int con_pelicula_actual = maraton(cartelera, matriz, num_peliculas, i + 1, hora_fin) + duracion;
            
            if (sin_pelicula_actual > con_pelicula_actual) {
                matriz[i][hora_actual] = sin_pelicula_actual;
            }
            else {
                matriz[i][hora_actual] = con_pelicula_actual;
            }
        }
    }
    
    return matriz[i][hora_actual];
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
    
    //int hora_fin = cartelera.at(num_peliculas - 1).hora;
    //suma_duracion(hora_fin, cartelera.at(num_peliculas - 1).duracion);
    
    vector<vector<int>> matriz(num_peliculas + 1, vector<int> (2401, 0));
    
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
