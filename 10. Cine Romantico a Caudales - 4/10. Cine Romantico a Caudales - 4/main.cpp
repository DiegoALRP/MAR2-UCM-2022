
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
    
    /*hora += duracion/60*100;
    hora += duracion%60;
    
    return hora;*/
    
    duracion += 10;
    int m = hora%100;
    int h = hora - m;
    m += duracion;
    
    return h + m/60*100 + m%60;
}

/*
 *
 *  maraton(i,j) es el máximo de minutos que se puede obtener mirando
 *  peliculas, de la pelicula 1 a la pelicula i, despues de la pelicula j.
 *
 *  1 <= i <= num_peliculas
 *  0 <= j < num_peliculas
 *
 *  Caso base:
 *
 *      maraton(num_peliculas, j) = 0
 *
 *  Casos recursivos:
 *
 *      maraton(i, j) = maraton(i + 1, j)       si hora_fin(j) >= hora_inicio(i).
 *      maraton(i, j) = maximo(maraton(i + 1, j), maraton(i + 1, i) + duracion(i))
 */


int maraton(const vector<pelicula> &cartelera, vector<vector<int>> &matriz, int num_peliculas, int i, int j) {
    
    if (matriz[i][j] != -1) return matriz[i][j];
    if (i == num_peliculas) matriz[i][j] = 0;
    else {
        
        if (i > num_peliculas || j > num_peliculas) return 0;
        if (matriz[i][j] != -1) return matriz[i][j];
        
        pelicula peli = cartelera[j];
        int hora_actual = suma_duracion(peli.hora, peli.duracion);
        
        if (cartelera[i+1].hora < hora_actual) {
            
            matriz [i][j] = maraton(cartelera, matriz, num_peliculas, i + 1, j);
        }
        else {
            
            int sin_peli = maraton(cartelera, matriz, num_peliculas, i + 1, j);
            int con_peli = maraton(cartelera, matriz, num_peliculas, i + 1, i + 1) + cartelera[i+1].duracion;
            
            if (sin_peli > con_peli) {
                matriz[i][j] = sin_peli;
            }
            else {
                matriz[i][j] = con_peli;
            }
        }
    }
    
    return matriz[i][j];
}

bool resuelveCaso() {

    //leer entrada
    
    int num_peliculas;
    
    cin >> num_peliculas;
   
    if (num_peliculas == 0)  // fin de la entrada
      return false;
    
    vector<pelicula> cartelera = vector<pelicula>(num_peliculas + 1);
    char aux;
    int hora, minuto, duracion;
    
    for (int i = 1; i <= num_peliculas; i++) {
        
        cin >> hora >> aux >> minuto >> duracion;
        
        cartelera[i].hora = hora*100 + minuto;
        cartelera[i].duracion = duracion;
    }
    
    cartelera[0].hora = -10;
    cartelera[0].duracion = 0;
    
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
