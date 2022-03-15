
// Nombre y Apellidos
// Diego Alejandro
// Rodriguez Pereira

// Comentario general sobre la solución,
// explicando cómo se resuelve el problema

#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

//Informacion de una cancion
struct cancion {
    
    double duracion; //Duracion de la cancion
    double puntuacion; //Puntuacion que le ha dado Pepe a la cancion
    
    bool operator < (const cancion &otro) const {
        return (otro.puntuacion/otro.duracion) < (puntuacion/duracion);
    }
};

struct Nodo {
    //vector<int> sol; //sol[i] va a contener un entero indicando en que cara se ha colocado la cancion i
    // siendo 1 la primera cara, y 2 la segunda cara. El 0 indica que no se ha colocado la cancion i en ninguna cara
    int cancion; //K, es el indice de la cancion actual
    double duracion_1ra_cinta; //Entero que indica cuanto se ha consumido de la 1era cinta
    double duracion_2da_cinta; //Entero que indica cuanto se ha consumido de la 2da cinta
    double puntuacion; //Puntuacion actual (real) de las canciones que se han metido
    double puntuacion_estimada; //Puntuacion estimada de las canciones que se podrian meter
    bool operator<(Nodo const &otro) const {
        return otro.puntuacion_estimada > puntuacion_estimada;
    }
};

//Calculo costa optimista
double cinta_voraz(const int &n, const int &duracion_cinta, const vector<cancion> &canciones, const Nodo &X) {
    
    double hueco = 2*duracion_cinta - X.duracion_1ra_cinta - X.duracion_2da_cinta;
    double estimacion = X.puntuacion;
    
    int i =  X.cancion + 1;
    while (i < n && canciones[i].duracion <= hueco) {
        hueco -= canciones[i].duracion;
        estimacion += canciones[i].puntuacion;
        i++;
    }
    
    if (i < n) {
        estimacion += (hueco/canciones[i].duracion) * canciones[i].puntuacion;
    }
    
    return estimacion;
}

//Calculo cota pesimista
double calculo_pesimista(const int &n, const int &duracion_cinta, const vector<cancion> &canciones, const Nodo &X) {
    
    double hueco1 = duracion_cinta - X.duracion_1ra_cinta;
    double hueco2 = duracion_cinta - X.duracion_2da_cinta;
    double estimacion = X.puntuacion;
    
    int i = X.cancion + 1;
    while (i < n && (canciones[i].duracion <= hueco1 || canciones[i].duracion <= hueco2)) {
        if (canciones[i].duracion <= hueco1) {
            hueco1 -= canciones[i].duracion;
            estimacion += canciones[i].puntuacion;
        }
        else if (canciones[i].duracion <= hueco2) {
            hueco2 -= canciones[i].duracion;
            estimacion += canciones[i].puntuacion;
        }
        i++;
    }
    
    return estimacion;
}

//Codigo del algoritmo de ramificacion y poda
//void cinta_rp(const int &n, const int &duracion_cinta, const vector<cancion> &canciones, const vector<int> &mejor_sol, double &mejor_puntuacion) {
void cinta_rp(const int &n, const int &duracion_cinta, const vector<cancion> &canciones, double &mejor_puntuacion) {
    
    Nodo Y;
    //Y.sol = vector<int>(n, 0);
    Y.cancion = -1;
    Y.duracion_1ra_cinta = 0;
    Y.duracion_2da_cinta = 0;
    Y.puntuacion = 0;
    Y.puntuacion_estimada = cinta_voraz(n, duracion_cinta, canciones, Y);
    priority_queue<Nodo> cola;
    cola.push(Y);
    mejor_puntuacion = calculo_pesimista(n, duracion_cinta, canciones, Y);
    
    while (!cola.empty() && cola.top().puntuacion_estimada >= mejor_puntuacion) {
        
        Y = cola.top();
        cola.pop();
        Nodo X(Y);
        X.cancion++;
        
        //Tres casos: Meterlo en la primera cinta, meterlo en la segunda cinta, o no meterlo
        
        //Caso en el que se mete la cancion en la primera cinta
        if (Y.duracion_1ra_cinta + canciones[X.cancion].duracion <= duracion_cinta) {
            //X.sol[X.cancion] = 1;
            X.duracion_1ra_cinta = Y.duracion_1ra_cinta + canciones[X.cancion].duracion;
            X.duracion_2da_cinta = Y.duracion_2da_cinta;
            X.puntuacion = Y.puntuacion + canciones[X.cancion].puntuacion;
            X.puntuacion_estimada = Y.puntuacion_estimada;
            
                if (X.cancion == n - 1) {
                    //mejor_sol = X.sol;
                    mejor_puntuacion = X.puntuacion;
                }
                else {
                    cola.push(X);
                }
        }
        
        //Caso en el que se mete la cancion en la segunda cinta
        if (Y.duracion_2da_cinta + canciones[X.cancion].duracion <= duracion_cinta) {
            //X.sol[X.cancion] = 2;
            X.duracion_1ra_cinta = Y.duracion_1ra_cinta;
            X.duracion_2da_cinta = Y.duracion_2da_cinta + canciones[X.cancion].duracion;
            X.puntuacion = Y.puntuacion + canciones[X.cancion].puntuacion;
            X.puntuacion_estimada = Y.puntuacion_estimada;
            
                if (X.cancion == n - 1) {
                    //mejor_sol = X.sol;
                    mejor_puntuacion = X.puntuacion;
                }
                else {
                    cola.push(X);
                    double pesimista = calculo_pesimista(n, duracion_cinta, canciones, X);
                    mejor_puntuacion = max(mejor_puntuacion, pesimista);
                }
        }
        
        //Caso en el que no se mete la cancion en ninguna de las dos cintas
        //X.sol[X.cancion] = 0;
        X.duracion_1ra_cinta = Y.duracion_1ra_cinta;
        X.duracion_2da_cinta = Y.duracion_2da_cinta;
        X.puntuacion = Y.puntuacion;
        //No estoy muy seguro de este
        //X.puntuacion_estimada = Y.puntuacion + cinta_voraz(n, duracion_cinta, canciones, X);
        X.puntuacion_estimada = cinta_voraz(n, duracion_cinta, canciones, X);
        if (X.puntuacion_estimada >= mejor_puntuacion) {
            if (X.cancion == n-1) {
                //mejor_sol = X.sol;
                mejor_puntuacion = X.puntuacion;
            }
            else {
                cola.push(X);
                double pesimista = calculo_pesimista(n, duracion_cinta, canciones, X);
                mejor_puntuacion = max(mejor_puntuacion, pesimista);
            }
        }
    }
}


bool resuelveCaso() {

    //leer entrada
    int n_canciones;
    cin >> n_canciones;
   
    if (n_canciones == 0)  // fin de la entrada
      return false;

    double duracion_cinta;
    cin >> duracion_cinta;
    
    vector<cancion> canciones = vector<cancion>(n_canciones);
    for (int i = 0; i < n_canciones; i++) {
        
        cin >> canciones[i].duracion;
        cin >> canciones[i].puntuacion;
    }
    
    sort(canciones.begin(), canciones.end(), less<cancion>());
    
    //vector<int> mejor_sol = vector<int>(n_canciones, 0);
    double mejor_puntuacion = 0;
    
    //cinta_rp(n_canciones, duracion_cinta, canciones, mejor_sol, mejor_puntuacion);
    cinta_rp(n_canciones, duracion_cinta, canciones, mejor_puntuacion);
    
    cout << mejor_puntuacion << endl;
    
    
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
