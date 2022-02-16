
// Nombre y Apellidos
// Diego Alejandro
// Rodriguez Pereira

// Comentario general sobre la solución,
// explicando cómo se resuelve el problema

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

struct horaYminuto {
    
    int hora;
    int minuto;
};

void calculaHora(int duracion, horaYminuto horaFin) {
    
    while (duracion > 0) {
        
        if (duracion >= 60) {
            
            horaFin.hora += 1;
            duracion -= 60;
        }
        else {
            
            horaFin.minuto += duracion;
            duracion = 0;
        }
    }
}

int cine(int pelis, const vector<horaYminuto> &horaPelis, const vector<int> &duracion, int i, horaYminuto j) {
    
    horaYminuto horaFin = {0, 0};
    calculaHora(duracion[i], horaFin);
    
    if (horaFin.hora > j.hora || (horaFin.hora == j.hora && horaFin.minuto > ))
    
    return 0;
}

bool resuelveCaso() {

    //leer entrada
    int pelis;
    
    cin >> pelis;
   
    if (pelis == 0)  // fin de la entrada
      return false;

    vector<horaYminuto> horaPelis = vector<horaYminuto>(pelis, {0, 0});
    vector<int> duracion = vector<int>(pelis, 0);
    char aux;
    
    for (int i = 0; i < pelis; i++) {
        
        cin >> horaPelis[i].hora;
        cin >> aux;
        cin >> horaPelis[i].minuto;
        
        cin >> duracion[i];
    }
    
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
